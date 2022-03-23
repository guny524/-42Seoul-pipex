/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:55:36 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/23 13:07:29 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pipex.h"

pid_t	forkfirst(char *argv, char *infile, int fds[2], t_envp_data *envp_data)
{
	pid_t	pid;
	int		infilefd;

	pid = fork();
	if (-1 == pid)
		fork_perror(argv, &envp_data->pathes);
	else if (pid)
		return (pid);
	infilefd = open(infile, O_RDONLY);
	open_perror(infilefd, "open infile", &envp_data->pathes);
	dup2_perror(infilefd, STDIN_FILENO, "dup2 infilefd", &envp_data->pathes);
	dup2_perror(fds[1], STDOUT_FILENO, "dup2 outfd", &envp_data->pathes);
	close(fds[0]);
	execve_perror(argv, envp_data);
	dprintf(2, "last never reach");//#
	return (-1); // never reach
}

pid_t	forklast(char *argv, int fds[2], char *outfile, t_envp_data *envp_data)
{
	pid_t	pid;
	int		outfilefd;

	pid = fork();
	if (-1 == pid)
		fork_perror(argv, &envp_data->pathes);
	else if (pid)
		return (pid);
	outfilefd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0000644);
	open_perror(outfilefd, "open outfile", &envp_data->pathes);
	dup2_perror(fds[0], STDIN_FILENO, "dup2 infd", &envp_data->pathes);
	dup2_perror(outfilefd, STDOUT_FILENO, "dup2 outfilefd", &envp_data->pathes);
	close(fds[1]);
	execve_perror(argv, envp_data);
	dprintf(2, "last never reach");//#
	return (-1); // never reach
}

char	*find_binary_path(char *cmd, char ***pathes, char ***free_args,
				int *join_free)
{
	int		cnt;
	char	*path;
	char	*str;

	*join_free = 0;
	if (0 == access(cmd, X_OK))
		return (cmd);
	cnt = -1;
	while ((*pathes)[++cnt])
	{
		path = ft_strjoin((*pathes)[cnt], "/");
		str = ft_strjoin(path, cmd);
		*join_free = 1;
		free(path);
		if (0 == access(str, X_OK))
			return (str);
		free(str);
	}
	perror("fail find command");
	split_free(free_args, -1);
	split_free(pathes, -1);
	exit(127); // 원래 exec에 실패하면 자식 프로세스가 부모 프로세스에게 127리턴
	// 그냥 안 되는 경로로 execv 시도해도 됨
}

char	**getpathes(char *const envp[])
{
	int		cnt;

	// cnt = -1;//#
	// dprintf(2, "getpathes: %s\n", *envp);//#
	// while (envp[++cnt])//#
	// 	dprintf(2, "getpathes: %s\n", envp[cnt]);//#
	if (NULL == envp || *envp == NULL)
	{
		write_perror(STDERR_FILENO, "env is NULL", 11, NULL);
		exit(EXIT_FAILURE);
	}
	cnt = -1;
	while (envp[++cnt])
		if (0 == ft_strncmp(envp[cnt], "PATH=", 5))
			return (split_perror(envp[cnt] + 5, ':', "fail split envp", NULL));
	return (NULL);
}

int	main(int argc, char *argv[], char *envp[])
{
	int			fds[2]; // 0: read, 1: write
	pid_t		first;
	pid_t		last;
	int			status;
	t_envp_data	envp_data;

	if (argc != 5)
	{
		write_perror(STDERR_FILENO, "usage : ./pipex infile cmd1 cmd2 outfile",
			40, NULL);
		return (EX_USAGE);
	}
	if (-1 == pipe(fds))
	{
		perror("fail pipe create");
		return (EX_OSERR);
	}
	envp_data = (t_envp_data){getpathes(envp), envp};
	first = forkfirst(argv[2], argv[1], fds, &envp_data);
	last = forklast(argv[3], fds, argv[4], &envp_data);
	close(fds[0]);
	close(fds[1]);
	waitpid(first, &status, 0);
	waitpid(last, &status, 0);
	split_free(&envp_data.pathes, -1);
	return (WEXITSTATUS(status));
}

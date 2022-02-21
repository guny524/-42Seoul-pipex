/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:55:36 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/20 21:28:04 by min-jo           ###   ########.fr       */
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

pid_t	forkfirst(char *argv, char *infile, int outfd, t_envp_data *envp_data)
{
	pid_t	pid;
	int		infilefd;

	pid = fork();
	if (-1 == pid)
		fork_perror(argv, &envp_data->pathes);
	else if (!pid)
	{
		close(outfd);
		return (pid);
	}
	infilefd = open_perror(infile, O_RDONLY, "open infile", &envp_data->pathes);
	dup2_perror(infilefd, STDIN_FILENO, "dup2 infilefd", &envp_data->pathes);
	dup2_perror(outfd, STDOUT_FILENO, "dup2 outfd", &envp_data->pathes);
	execve_perror(argv, envp_data);
	dprintf(2, "last never reach");//#
	return (-1); // never reach
}

pid_t	forklast(char *argv, int infd, char *outfile, t_envp_data *envp_data)
{
	pid_t	pid;
	int		outfilefd;

	pid = fork();
	if (-1 == pid)
		fork_perror(argv, &envp_data->pathes);
	else if (!pid)
	{
		close(infd);
		return (pid);
	}
	outfilefd = open_perror(outfile, O_WRONLY | O_CREAT, "open outfile",
			&envp_data->pathes);
	dup2_perror(infd, STDIN_FILENO, "dup2 infd", &envp_data->pathes);
	dup2_perror(outfilefd, STDOUT_FILENO, "dup2 outfilefd", &envp_data->pathes);
	execve_perror(argv, envp_data);
	dprintf(2, "last never reach");//#
	return (-1); // never reach
}

char	*find_binary_path(char *cmd, char ***pathes, char ***free_args)
{
	int		cnt;
	char	*path;
	char	*str;

	cnt = -1;
	while ((*pathes)[++cnt])
	{
		path = ft_strjoin((*pathes)[cnt], "/");
		str = ft_strjoin(path, cmd);
		free(path);
		if (0 == access(str, X_OK))
		{
			// dprintf(2, "path %d: %s\n", cnt, str);//#
			// int tmp = -1;//#
			// while ((*free_args)[++tmp])//#
				// dprintf(2, "args: %s\n", (*free_args)[tmp]);//#
			return (str);
		}
		free(str);
	}
	perror("fail find path");
	split_free(free_args, -1);
	split_free(pathes, -1);
	exit(EX_USAGE);
}

char	**getpathes(char *const envp[])
{
	int		cnt;

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
	int			state;
	t_envp_data	envp_data;

	if (argc != 5)
	{
		if (-1 == write(STDERR_FILENO,
				"usage : ./pipex infile cmd1 cmd2 outfile", 40))
			exit(EX_IOERR);
		return (EX_USAGE);
	}
	if (-1 == pipe(fds))
	{
		perror("fail pipe create");
		return (EX_OSERR);
	}
	envp_data = (t_envp_data){getpathes(envp), envp};
	first = forkfirst(argv[2], argv[1], fds[1], &envp_data);
	last = forklast(argv[3], fds[0], argv[4], &envp_data);
	waitpid(first, &state, 0);
	waitpid(last, &state, 0);
	split_free(&envp_data.pathes, -1);
	// return wpid == pid && WIFEXITED(status) ? WEXITSTATUS(status) : -1;
	return (state);
}

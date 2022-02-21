/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:55:36 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/20 19:14:46 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include "pipex.h"

void	dofork(int *pipes[2])
{
	pid_t	pid;

	pid = fork();
	if (-1 == pid)
	{
		perror("fail fork");
		exit(errno);
	}
	else if (!pid) // parent //#
	{
		close(fds[0]); // file descriptor unused in parent
		const char *words[] = {"pear", "peach", "apple"};
		size_t numwords = sizeof(words)/sizeof(words[0]);
		for (size_t i = 0; i < numwords; i++)
			dprintf(fds[1], "%s\n", words[i]);

		// send EOF so child can continue
		close(fds[1]);

		int status;
		pid_t wpid = waitpid(pid, &status, 0);
		return wpid == pid && WIFEXITED(status) ? WEXITSTATUS(status) : -1;
	}
	// child
	dup2(fds[0], STDIN_FILENO); // read -> stdin
	close(fds[0]); // stdin is copied
	close(fds[1]); // file descriptor unused in child
	char *argv[] = {(char *)"sort", NULL};   // create argument vector
	if (execvp(argv[0], argv) < 0)
		exit(0);  // run sort command (exit if something went wrong)
}

pid_t	forkprocess(const char *argv, int infd, int outfd)
{
	char	**args;

	args = ft_split(argv, ' ');
	if (NULL == args)
	{
		perror("fail split cmd");
		write(2, argv, split_len(argv, '\0'));
		exit(errno);
	}
}

pid_t	forkfirst(const char *argv, const char *intfile, int outfd)
{

}

pid_t	forklast()
{

}

int	main(int argc, char *argv[])
{
	int		fds[2]; // 0: read, 1: write
	int		cnt;

	if (argc != 5)
	{
		wirte(1, "usage : ./pipex infile cmd1 cmd2 outfile", 33);
		return (0);
	}
	cnt = -1;
	while (++cnt < argc - 4)
		if (-1 == pipe(fds))
		{
			perror("fail pipe create");
			exit(errno);
		}
	cnt = 2 - 1;
	while (++cnt <= argc - 2)
		forkprocess(argv[cnt], );
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perrors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 17:31:42 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/21 14:59:48 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <stdlib.h>
#include <sysexits.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "pipex.h"

void	fork_perror(char *argv, char ***free_pathes)
{
	perror("fork first cmd");
	if (-1 == write(STDERR_FILENO, argv, ft_strlen(argv)))
	{
		split_free(free_pathes, -1);
		exit(EX_IOERR);
	}
	split_free(free_pathes, -1);
	exit(EX_OSERR);
}

char	**split_perror(char const *s, char c, const char *errstr,
				char ***free_pathes)
{
	char	**str;

	str = ft_split(s, c);
	if (NULL == str)
	{
		perror(errstr);
		if (-1 == write(STDERR_FILENO, s, ft_strlen(s)))
		{
			if (free_pathes)
				split_free(free_pathes, -1);
			exit(EX_IOERR);
		}
		if (free_pathes)
			split_free(free_pathes, -1);
		exit(EXIT_FAILURE);
	}
	return (str);
}

void	dup2_perror(int fildes, int fildes2, const char *errstr,
				char ***free_pathes)
{
	int	ret;

	ret = dup2(fildes, fildes2);
	if (-1 == ret)
	{
		perror(errstr);
		split_free(free_pathes, -1);
		exit(EXIT_FAILURE);
	}
	close(fildes);
}

void	open_perror(int fd, const char *errstr, char ***free_pathes)
{
	if (-1 == fd)
	{
		perror(errstr);
		split_free(free_pathes, -1);
		exit(EX_NOINPUT);
	}
}

void	execve_perror(char *argv, t_envp_data *envp_data)
{
	char	**args;
	char	*path;

	args = split_perror(argv, ' ', "fail split cmd", &envp_data->pathes);
	path = find_binary_path(args[0], &envp_data->pathes, &args);
	// char	**envp = envp_data->envp;//#
	// int		cnt = -1;//#
	// while (envp[++cnt])//#
	// 	dprintf(2, "envp %d: %s\n", cnt, envp[cnt]);//#
	if (-1 == execve(path, args, envp_data->envp))
	{
		perror("fail execve");
		split_free(&args, -1);
		split_free(&envp_data->pathes, -1);
		free(path);
		exit(EX_OSERR);
	}
}

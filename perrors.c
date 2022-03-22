/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perrors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 17:31:42 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/22 21:39:56 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <stdlib.h>
#include <sysexits.h>
#include <stdio.h>
#include <unistd.h>
#include "pipex.h"

void	fork_perror(char *argv, char ***free_pathes)
{
	perror("fork first cmd");
	write_perror(STDERR_FILENO, argv, ft_strlen(argv), free_pathes);
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
		write_perror(STDERR_FILENO, s, ft_strlen(s), free_pathes);
		if (free_pathes)
			split_free(free_pathes, -1);
		exit(EXIT_FAILURE);
	}
	return (str);
}

char	**unquote_perror(char const *s, char c, const char *errstr,
				char ***free_pathes)
{
	char	**str;

	str = unquote_split(s, c);
	if (NULL == str)
	{
		perror(errstr);
		write_perror(STDERR_FILENO, s, ft_strlen(s), free_pathes);
		if (free_pathes)
			split_free(free_pathes, -1);
		exit(EXIT_FAILURE);
	}
	return (str);
}

void	execve_perror(char *argv, t_envp_data *envp_data)
{
	char	**args;
	char	*path;

	args = unquote_perror(argv, ' ', "fail split cmd", &envp_data->pathes);
	path = find_binary_path(args[0], &envp_data->pathes, &args);
	if (-1 == execve(path, args, envp_data->envp))
	{
		perror("fail execve");
		split_free(&args, -1);
		split_free(&envp_data->pathes, -1);
		free(path);
		exit(EX_OSERR);
	}
}

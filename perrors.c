/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perrors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 17:31:42 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/23 13:08:09 by min-jo           ###   ########.fr       */
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
	int	ret_errno;

	ret_errno = errno;
	perror("fork first cmd");
	write_perror(STDERR_FILENO, argv, ft_strlen(argv), free_pathes);
	split_free(free_pathes, -1);
	exit(ret_errno);
}

char	**split_perror(char const *s, char c, const char *errstr,
				char ***free_pathes)
{
	char	**str;
	int		ret_errno;

	str = ft_split(s, c);
	if (NULL == str)
	{
		ret_errno = errno;
		perror(errstr);
		write_perror(STDERR_FILENO, s, ft_strlen(s), free_pathes);
		if (free_pathes)
			split_free(free_pathes, -1);
		exit(ret_errno);
	}
	return (str);
}

char	**unquote_perror(char const *s, char c, const char *errstr,
				char ***free_pathes)
{
	char	**str;
	int		ret_errno;

	str = unquote_split(s, c);
	if (NULL == str)
	{
		ret_errno = errno;
		perror(errstr);
		write_perror(STDERR_FILENO, s, ft_strlen(s), free_pathes);
		if (free_pathes)
			split_free(free_pathes, -1);
		exit(ret_errno);
	}
	return (str);
}

void	execve_perror(char *argv, t_envp_data *envp_data)
{
	char	**args;
	char	*path;
	int		ret_errno;
	int		join_free;

	args = unquote_perror(argv, ' ', "fail split cmd", &envp_data->pathes);
	path = find_binary_path(args[0], &envp_data->pathes, &args, &join_free);
	if (-1 == execve(path, args, envp_data->envp))
	{
		ret_errno = errno;
		perror("fail execve");
		split_free(&args, -1);
		split_free(&envp_data->pathes, -1);
		if (join_free)
			free(path);
		exit(ret_errno);
	}
}

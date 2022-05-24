/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_perrors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 21:14:45 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/22 22:32:13 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <stdlib.h>
#include <sysexits.h>
#include <stdio.h>
#include "pipex.h"

void	open_perror(int fd, const char *errstr, char ***free_pathes)
{
	int	ret_errno;

	if (-1 == fd)
	{
		ret_errno = errno;
		perror(errstr);
		split_free(free_pathes, -1);
		exit(ret_errno);
	}
}

void	dup2_perror(int fildes, int fildes2, const char *errstr,
				char ***free_pathes)
{
	int	ret_errno;

	if (-1 == dup2(fildes, fildes2))
	{
		ret_errno = errno;
		perror(errstr);
		split_free(free_pathes, -1);
		exit(ret_errno);
	}
	close(fildes);
}

void	write_perror(int fildes, const void *buf, size_t nbyte,
				char ***free_pathes)
{
	int	ret_errno;

	if (-1 == write(fildes, buf, nbyte))
	{
		ret_errno = errno;
		perror("write error");
		if (free_pathes)
			split_free(free_pathes, -1);
		exit(ret_errno);
	}
}

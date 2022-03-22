/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_perrors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 21:14:45 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/22 21:36:50 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <stdlib.h>
#include <sysexits.h>
#include <stdio.h>
#include "pipex.h"

void	open_perror(int fd, const char *errstr, char ***free_pathes)
{
	if (-1 == fd)
	{
		perror(errstr);
		split_free(free_pathes, -1);
		exit(EX_NOINPUT);
	}
}

void	dup2_perror(int fildes, int fildes2, const char *errstr,
				char ***free_pathes)
{
	if (-1 == dup2(fildes, fildes2))
	{
		perror(errstr);
		split_free(free_pathes, -1);
		exit(EXIT_FAILURE);
	}
	close(fildes);
}

void	write_perror(int fildes, const void *buf, size_t nbyte,
				char ***free_pathes)
{
	if (-1 == write(fildes, buf, nbyte))
	{
		perror("write error");
		if (free_pathes)
			split_free(free_pathes, -1);
		exit(EX_IOERR);
	}
}

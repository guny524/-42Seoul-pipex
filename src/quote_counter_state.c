/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_counter_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:52:38 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/22 22:36:35 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sysexits.h>
#include "pipex.h"

t_state_quote	state_quote_counter_normal(const char *s, char c)
{
	if ('\'' == *s)
		return (STATE_QUOTE_SINGLE);
	else if ('"' == *s)
		return (STATE_QUOTE_DOUBLE);
	else if (c == *s)
		return (STATE_QUOTE_CHAR);
	else
		return (STATE_QUOTE_NORMAL);
}

t_state_quote	state_quote_counter_char(size_t *cnt, const char *s, char c)
{
	if ('\'' == *s)
		return (STATE_QUOTE_SINGLE);
	else if ('"' == *s)
		return (STATE_QUOTE_DOUBLE);
	else if (c == *s)
		return (STATE_QUOTE_CHAR);
	else
	{
		(*cnt)++;
		return (STATE_QUOTE_NORMAL);
	}
}

t_state_quote	state_quote_counter_single(size_t *cnt, const char *s)
{
	if ('\'' == *s)
	{
		(*cnt)++;
		return (STATE_QUOTE_NORMAL);
	}
	else
		return (STATE_QUOTE_SINGLE);
}

t_state_quote	state_quote_counter_double(size_t *cnt, const char *s)
{
	if ('"' == *s)
	{
		(*cnt)++;
		return (STATE_QUOTE_NORMAL);
	}
	else
		return (STATE_QUOTE_DOUBLE);
}

void	exit_quote_counter_err(t_state_quote state)
{
	int	ret_errno;

	if (STATE_QUOTE_SINGLE == state || STATE_QUOTE_DOUBLE == state)
	{
		if (-1 == write(STDERR_FILENO, "quote prase error", 17))
		{
			ret_errno = errno;
			perror("write error");
			exit(ret_errno);
		}
		exit(EX_USAGE);
	}
}

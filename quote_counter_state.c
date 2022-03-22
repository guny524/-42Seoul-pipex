/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_counter_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:52:38 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/22 18:02:02 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sysexits.h>
#include "pipex.h"

t_state_quote	state_quote_counter_normal(size_t *cnt, const char *s, char c)
{
	if ('\'' == *s)
		return (STATE_QUOTE_SINGLE);
	else if('"' == *s)
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
	else if('"' == *s)
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
		if ('\'' == *(s-1))
			return (STATE_QUOTE_SINGLE);
		(*cnt)++;
		return (STATE_QUOTE_NORMAL);
	}
	else if('"' == *s)//#
		return (STATE_QUOTE_DOUBLE);
	else if (c == *s)//#
		return (STATE_QUOTE_CHAR);
	else
		return (STATE_QUOTE_SINGLE);
}

t_state_quote	state_quote_counter_double(size_t *cnt, const char *s)
{
	if ('\'' == *s)//#
	{
		if ('\'' == *(s-1))
			return (STATE_QUOTE_SINGLE);
		(*cnt)++;
		return (STATE_QUOTE_NORMAL);
	}
	else if('"' == *s)
	{
		if ('"' == *(s-1))
			return (STATE_QUOTE_DOUBLE);
		(*cnt)++;
		return (STATE_QUOTE_NORMAL);
	}
	else if (c == *s)//#
		return (STATE_QUOTE_CHAR);
	else
		return (STATE_QUOTE_DOUBLE);
}

void	exit_quote_counter_err(t_state_quote state)
{
	if (STATE_QUOTE_SINGLE == state || STATE_QUOTE_DOUBLE == state)
	{
		if (-1 == write(STDERR_FILENO, "state quote error", 17))
		{
			perror("write error");
			exit(EX_IOERR);
		}
		exit(EX_USAGE);
	}
}

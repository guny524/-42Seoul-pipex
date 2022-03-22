/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:04:26 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/22 17:47:41 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "pipex.h"

static size_t	quote_len(const char *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s && *s != c)
	{
		s++;
		cnt++;
	}
	return (cnt);
}

static size_t	quote_counter(const char *s, char c)
{
	size_t			cnt;
	t_state_quote	state;

	cnt = 0;
	state = STATE_QUOTE_CHAR;
	while (*s)
	{
		if (STATE_QUOTE_NORMAL == state)
			state = state_quote_counter_normal(&cnt, s, c);
		else if (STATE_QUOTE_CHAR == state)
			state = state_quote_counter_char(&cnt, s, c);
		else if (STATE_QUOTE_SINGLE == state)
			state = state_quote_counter_single(&cnt, s);
		else if (STATE_QUOTE_DOUBLE == state)
			state = state_quote_counter_double(&cnt, s);
		s++;
	}
	exit_quote_counter_err(state);
	return (cnt);
}

char	**unquote_split(const char *s, char c)
{
	char	**ret;
	size_t	cnt;
	size_t	i;
	size_t	len;

	cnt = quote_counter(s, c);
	ret = malloc(sizeof(char *) * (cnt + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < cnt)
	{
		while (*s && *s == c)
			s++;
		len = quote_len(s, c);
		ret[i] = malloc(sizeof(char) * (len + 1));
		if (!ret[i])
			return (split_free(&ret, i));
		ft_strlcpy(ret[i], s, len + 1);
		s += len;
	}
	ret[i] = NULL;
	return (ret);
}

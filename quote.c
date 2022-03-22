/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:04:26 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/22 21:27:04 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "pipex.h"

static size_t	quote_counter(const char *s, char c)
{
	size_t			cnt;
	t_state_quote	state;

	cnt = 0;
	state = STATE_QUOTE_CHAR;
	while (*s)
	{
		if (STATE_QUOTE_NORMAL == state)
			state = state_quote_counter_normal(s, c);
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

static t_state_quote	get_state(const char *s)
{
	t_state_quote	state;

	if ('\'' == *s)
		state = STATE_QUOTE_SINGLE;
	else if ('"' == *s)
		state = STATE_QUOTE_DOUBLE;
	else
		state = STATE_QUOTE_NORMAL;
	return (state);
}

static const char	*quote_len_move(const char *s, char c)
{
	const t_state_quote	state = get_state(s);

	while (*s && ((STATE_QUOTE_NORMAL == state && *s == c)
			|| (STATE_QUOTE_SINGLE == state && *s == '\'')
			|| (STATE_QUOTE_DOUBLE == state && *s == '"')))
		s++;
	return (s);
}

static size_t	quote_len(const char **s, char c)
{
	size_t				cnt;
	const char			*str;
	const t_state_quote	state = get_state(*s);

	if (STATE_QUOTE_SINGLE == state || STATE_QUOTE_DOUBLE == state)
		(*s)++;
	str = *s;
	cnt = 0;
	while (*str && ((STATE_QUOTE_NORMAL == state && *str != c)
			|| (STATE_QUOTE_SINGLE == state && *str != '\'')
			|| (STATE_QUOTE_DOUBLE == state && *str != '"')))
	{
		cnt++;
		str++;
	}
	return (cnt);
}

char	**unquote_split(const char *s, char c)
{
	char			**ret;
	size_t			cnt;
	size_t			i;
	size_t			len;

	cnt = quote_counter(s, c);
	ret = malloc(sizeof(char *) * (cnt + 1));
	if (!ret)
		return (NULL);
	ret[cnt] = NULL;
	i = -1;
	while (++i < cnt)
	{
		s = quote_len_move(s, c);
		len = quote_len(&s, c);
		ret[i] = malloc(sizeof(char) * (len + 1));
		if (!ret[i])
			return (split_free(&ret, i));
		ft_strlcpy(ret[i], s, len + 1);
		s += len;
	}
	return (ret);
}

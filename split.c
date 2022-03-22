/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:25:00 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/22 21:45:00 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "pipex.h"

char	**split_free(char ***str, size_t n)
{
	if (NULL == *str)
		return (NULL);
	if (SIZE_MAX == n) // -1 == n
	{
		while ((*str)[++n])
		{
			free((*str)[n]);
			(*str)[n] = NULL;
		}
		free(*str);
		*str = NULL;
	}
	else
	{
		while (n >= 0)
		{
			free((*str)[--n]);
			(*str)[n] = NULL;
		}
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

static size_t	split_len(const char *s, char c)
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

static size_t	split_counter(const char *s, char c)
{
	size_t	cnt;
	int		c_flag;

	cnt = 0;
	c_flag = 1;
	while (*s)
	{
		if (c_flag && *s != c)
		{
			cnt++;
			c_flag = 0;
		}
		else if (*s == c)
			c_flag = 1;
		s++;
	}
	return (cnt);
}

char	**ft_split(const char *s, char c)
{
	char	**ret;
	size_t	cnt;
	size_t	i;
	size_t	len;

	cnt = split_counter(s, c);
	ret = malloc(sizeof(char *) * (cnt + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < cnt)
	{
		while (*s && *s == c)
			s++;
		len = split_len(s, c);
		ret[i] = malloc(sizeof(char) * (len + 1));
		if (!ret[i])
			return (split_free(&ret, i));
		ft_strlcpy(ret[i], s, len + 1);
		s += len;
	}
	ret[i] = NULL;
	return (ret);
}

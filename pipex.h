/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:53:43 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/22 21:41:39 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>

typedef struct s_envp_data
{
	char	**pathes;
	char	**envp;
}	t_envp_data;

typedef enum e_state_quote
{
	STATE_QUOTE_NORMAL,
	STATE_QUOTE_CHAR,
	STATE_QUOTE_SINGLE,
	STATE_QUOTE_DOUBLE,
}	t_state_quote;

/*
* pipex.c
*/
pid_t			forkfirst(char *argv, char *infile, int outfd,
					t_envp_data *envp_data);
pid_t			forklast(char *argv, int infd, char *outfile,
					t_envp_data *envp_data);
char			*find_binary_path(char *cmd, char ***pathes, char ***free_args);
char			**getpathes(char *const envp[]);
/*
* quote_counter_state.c
*/
t_state_quote	state_quote_counter_normal(const char *s, char c);
t_state_quote	state_quote_counter_char(size_t *cnt, const char *s, char c);
t_state_quote	state_quote_counter_single(size_t *cnt, const char *s);
t_state_quote	state_quote_counter_double(size_t *cnt, const char *s);
void			exit_quote_counter_err(t_state_quote state);
/*
* quote.c
*/
char			**unquote_split(const char *s, char c);
/*
* string.c
*/
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
char			*ft_strjoin(char const *s1, char const *s2);
/*
* split.c
*/
char			**split_free(char ***str, size_t n);
char			**ft_split(const char *s, char c);
/*
* perrors.c
*/
void			fork_perror(char *argv, char ***free_pathes);
char			**split_perror(char const *s, char c, const char *errstr,
					char ***free_pathes);
char			**unquote_perror(char const *s, char c, const char *errstr,
					char ***free_pathes);
void			execve_perror(char *argv, t_envp_data *envp_data);
/*
* io_perrors.c
*/
void			open_perror(int fd, const char *errstr, char ***free_pathes);
void			dup2_perror(int fildes, int fildes2, const char *errstr,
					char ***free_pathes);
void			write_perror(int fildes, const void *buf, size_t nbyte,
					char ***free_pathes);

#endif

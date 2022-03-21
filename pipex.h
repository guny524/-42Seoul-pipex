/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:53:43 by min-jo            #+#    #+#             */
/*   Updated: 2022/03/21 15:00:23 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_envp_data
{
	char	**pathes;
	char	**envp;
}	t_envp_data;

/*
* pipex.c
*/
pid_t	forkfirst(char *argv, char *infile, int outfd, t_envp_data *envp_data);
pid_t	forklast(char *argv, int infd, char *outfile, t_envp_data *envp_data);
char	*find_binary_path(char *cmd, char ***pathes, char ***free_args);
char	**getpathes(char *const envp[]);
/*
* string.c
*/
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(char const *s1, char const *s2);
/*
* split.c
*/
char	**split_free(char ***str, size_t n);
char	**ft_split(char const *s, char c);
/*
* perrors.c
*/
void	fork_perror(char *argv, char ***free_pathes);
char	**split_perror(char const *s, char c, const char *errstr,
			char ***free_pathes);
void	dup2_perror(int fildes, int fildes2, const char *errstr,
			char ***free_pathes);
void	open_perror(int fd, const char *errstr, char ***free_pathes);
void	execve_perror(char *argv, t_envp_data *envp_data);
#endif

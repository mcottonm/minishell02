/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:09:54 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/07 17:53:07 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_H
# define MSHELL_H

# include <errno.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h> 
# include <sys/wait.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

typedef struct		s_string
{
	char		*str;
	size_t		slen;
}					t_string;

typedef struct		d_list
{
	void			*content;
	struct d_list	*next;
	struct d_list	*prev;
}					d_list;

typedef struct		s_env
{
	char		*key;
	char		*vlm;
}					t_env;

typedef struct		s_srch
{
	char			*path;
	char			*tmp;
	char			*prog;
	char			*name;
}					t_srch;

void				after_prty(ssize_t rl[], t_string *nline, char **line, t_string *const buff);
bool				bin_fltr(char **avs, d_list *env_lst, int *e_stat);
char				**crt_menv(d_list *env_lst);
void				chld_prc(int pnum, int *fds, d_list *instr, d_list *env_lst);
void				cls_fds(int *fds, int num_cmd);
void				del_instr_s(void *instrs);
void				del_tk_lst(d_list *tk_lst);
char				*er_to_str(int e_stat);
int					error_check(char *line, int *e_stat);
void				err_exit(char *str);
char				*env_vlm(d_list *env_lst, const char *new);

d_list				*ft_dlstnew(void *content);
void				ft_dlstadd(d_list **lst, d_list *new);
void				ft_dlstdelone(d_list *lst, void (*del)(void*));
void				ft_dlstadd_back(d_list **lst, d_list *new);
void				ft_dlstadd_frnt(d_list **lst, d_list *new);
size_t				ft_dlst_sz(d_list *lst);

int					ft_erro(int *e_stat, int sim);
int					ft_strcmp(const char *str1, const char *str2);
int					ft_exectr(void *instr, d_list *env_lst, int *e_stat);
int					ft_exc_one(void *instr_in, d_list *env_lst, int *e_stat);
void				ft_export(d_list *env_lst, char **avs, int *e_stat);
void				ft_pwd(void);
void				ft_echo(char **av);
char 				*pwd_util(void);
void 				ft_cd(char **argv, d_list *env);

void				free_buff(t_string *buf);
char				*free_srch(t_srch *srch);
int					forker(d_list *instrs, d_list *env_lstm, int *stat);
void				free_env(void	*tmp);
int					get_next_line(int fd, char **line);
t_env				*loc_env(const char *new);
int					multiline(char **line, int *e_stat, d_list *env_lst);
void				handle_sigint_c(int sig);
void				handle_sigint_sl(int sig);
d_list				*init_env(int ac, char **av, char **env);
void				instr_and_frk(char *line, d_list *env_lst, int *e_stat);
void				put_fenv(d_list *env_lst);
char				*redir(d_list *rdrs);
void				set_env(d_list *env_lst, const char *new, bool visible);
d_list				*srch_hide_key(d_list *env_lst, const char *new);
char				*srch_prgm(char **avs, d_list *env_lst);
void				set_vlm(void **lst_cont, t_env *new_env);
d_list				*take_fenv(d_list *env_lst);
void				unset_env(d_list *env_lst, const char *new);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:09:54 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/08 19:07:57 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_H
# define MSHELL_H

# include <errno.h>
# include <stdbool.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
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

typedef struct		s_d_list
{
	void				*content;
	struct s_d_list		*next;
	struct s_d_list		*prev;
}					t_d_list;

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

void				after_prty(ssize_t rl[], t_string *nline,
					char **line, t_string *const buff);
bool				bin_fltr(char **avs, t_d_list *env_lst, int *e_stat);
char				**crt_menv(t_d_list *env_lst);
void				chld_prc(int pnum, int *fds,
					t_d_list *instr, t_d_list *env_lst);
void				cls_fds(int *fds, int num_cmd);
void				del_instr_s(void *instrs);
void				del_tk_lst(t_d_list *tk_lst);
void				ft_env(t_d_list *env_lst);
char				*er_to_str(int e_stat);
int					error_check(char *line, int *e_stat);
void				err_exit(char *str);
char				*env_vlm(t_d_list *env_lst, const char *new);

t_d_list			*ft_dlstnew(void *content);
void				ft_dlstadd(t_d_list **lst, t_d_list *new);
void				ft_dlstdelone(t_d_list *lst, void (*del)(void*));
void				ft_dlstadd_back(t_d_list **lst, t_d_list *new);
void				ft_dlstadd_frnt(t_d_list **lst, t_d_list *new);
size_t				ft_dlst_sz(t_d_list *lst);

int					ft_erro(int *e_stat, int sim);
int					ft_strcmp(const char *str1, const char *str2);
int					ft_exectr(void *instr, t_d_list *env_lst, int *e_stat);
int					ft_exc_one(void *instr_in, t_d_list *env_lst, int *e_stat);
void				ft_export(t_d_list *env_lst, char **avs, int *e_stat);
void				ft_pwd(void);
void				ft_echo(char **av);
char				*pwd_util(void);
void				ft_cd(char **argv, t_d_list *env);

void				free_buff(t_string *buf);
char				*free_srch(t_srch *srch);
int					forker(t_d_list *instrs, t_d_list *env_lstm, int *stat);
void				free_env(void	*tmp);
int					get_next_line(int fd, char **line);
t_env				*loc_env(const char *new);
int					multiline(char **line, int *e_stat, t_d_list *env_lst);
void				handle_sigint_c(int sig);
void				handle_sigint_sl(int sig);
t_d_list			*init_env(int ac, char **av, char **env);
void				instr_and_frk(char *line, t_d_list *env_lst, int *e_stat);
void				put_fenv(t_d_list *env_lst);
char				*redir(t_d_list *rdrs);
void				set_env(t_d_list *env_lst, const char *new, bool visible);
t_d_list			*srch_hide_key(t_d_list *env_lst, const char *new);
char				*srch_prgm(char **avs, t_d_list *env_lst);
void				set_vlm(void **lst_cont, t_env *new_env);
t_d_list			*take_fenv(t_d_list *env_lst);
void				unset_env(t_d_list *env_lst, const char *new);

#endif

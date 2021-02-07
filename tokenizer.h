/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcottonm <mcottonm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 14:46:28 by mcottonm          #+#    #+#             */
/*   Updated: 2021/02/07 14:22:57 by mcottonm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../mshell.h"
# define FSM_N 10

enum				e_stt
{
	NONE,
	W,
	SP,
	VAR,
	COMMA,
	PIPE,
	SQ,
	DQ,
	DVAR
};

enum				e_token
{
	TK_RDR_IN = 0b1,
	TK_RDR_OUT = 0b10,
	TK_RDR_OUT_AP = 0b100,
	TK_WORD = 0b1000,
	TK_SP = 0b10000,
	TK_COMMA = 0b100000,
	TK_PIPE = 0b1000000,
	TK_VAR = 0b10000000,
	TK_DVAR = 0b100000000,
	TK_FNAME = 0b1000000000,
	TK_RDRS = TK_RDR_IN | TK_RDR_OUT | TK_RDR_OUT_AP,
	CMD,
};

struct					s_token
{
	char				*str;
	enum e_token		t_stt;
};

struct					s_fsm_stt
{
	d_list				*tk_list;
	size_t				st;
	size_t				i;
	char				*in_str;
	enum e_stt			c_stt;
	bool				run;
};

struct					s_instrs
{
	char				**avs;
	enum e_token		type;
	d_list				*rdr;
};

typedef bool			(*t_fltr)(const struct s_fsm_stt *);
typedef void			(*t_hndl)(struct s_fsm_stt *);
typedef void			(*t_fnc)(struct s_fsm_stt *);

extern t_fltr			g_flts[];
extern t_hndl			g_hndls[];
extern t_fnc			g_fncs[];

void					del_token(void *a);
void					sp_del(d_list **tks_in);
void					add_n(struct s_fsm_stt *stt);
void					mini_tok(char *str, d_list **tks);
int						syntax_check(d_list *tks, int *e_stat);
void					tk_init(struct s_fsm_stt *stt, enum e_token tmp);
d_list					*stg_two(d_list **tks);
d_list					*tokenizer(char *str, int *e_stat);
void					instr_crt(d_list **tks, d_list *env_list, int *stat);
void					inc_fname(d_list *tks);

bool					flt_end(const struct s_fsm_stt *stt);
void					hndl_end(struct s_fsm_stt *stt);

bool					flt_sp(const struct s_fsm_stt *stt);
void					hndl_sp(struct s_fsm_stt *stt);
void					add_sp(struct s_fsm_stt *stt);

bool					flt_w(const struct s_fsm_stt *stt);
void					add_w(struct s_fsm_stt *stt);
void					hndl_w(struct s_fsm_stt *stt);

bool					flt_var(const struct s_fsm_stt *stt);
void					hndl_var(struct s_fsm_stt *stt);
void					add_var(struct s_fsm_stt *stt);

bool					flt_var_end(const struct s_fsm_stt *stt);
void					hndl_var_end(struct s_fsm_stt *stt);

bool					flt_com(const struct s_fsm_stt *stt);
void					hndl_com(struct s_fsm_stt *stt);
void					add_com(struct s_fsm_stt *stt);

bool					flt_p(const struct s_fsm_stt *stt);
void					add_p(struct s_fsm_stt *stt);
void					hndl_p(struct s_fsm_stt *stt);

bool					flt_sq(const struct s_fsm_stt *stt);
void					hndl_sq(struct s_fsm_stt *stt);

bool					flt_dq(const struct s_fsm_stt *stt);
void					hndl_dq(struct s_fsm_stt *stt);

bool					flt_rdr(const struct s_fsm_stt *stt);
void					hndl_rdr(struct s_fsm_stt *stt);

#endif
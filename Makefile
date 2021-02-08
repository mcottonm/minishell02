# **************************************************************************** #
# GENERIC_VARIABLES

OBJ_DIR = build

# **************************************************************************** #
# COMPILER_OPTIONS

C_COMPILER = clang
C_STANDART = -std=c99
C_CFLAGS =  $(CFLAGS) $(CPPFLAGS) -Wall -Wextra -Werror
C_LFLAGS =  $(CFLAGS) $(CPPFLAGS) -Wall -Wextra -Werror

# **************************************************************************** #
# D_LIST TARGET DESCRIPTION

D_LIST_NAME = d_list
D_LIST_PATH = d_list
D_LIST_FILE = d_list/libd_list.a
D_LIST_SRCS = d_list_add.c d_lists.c
D_LIST_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(D_LIST_SRCS))
D_LIST_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(D_LIST_SRCS))
D_LIST_LIBS = 
D_LIST_INCS = -I libft -I .

# **************************************************************************** #
# FT TARGET DESCRIPTION

FT_NAME = ft
FT_PATH = libft
FT_FILE = libft/libft.a
FT_SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c
FT_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(FT_SRCS))
FT_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(FT_SRCS))
FT_LIBS = 
FT_INCS = -I libft

# **************************************************************************** #
# ENV_U_ERR TARGET DESCRIPTION

ENV_U_ERR_NAME = env_u_err
ENV_U_ERR_PATH = env_u_err
ENV_U_ERR_FILE = env_u_err/libenv_u_err.a
ENV_U_ERR_SRCS = deleter.c env_aux.c env_cntr.c err_handler.c file_joy.c
ENV_U_ERR_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(ENV_U_ERR_SRCS))
ENV_U_ERR_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(ENV_U_ERR_SRCS))
ENV_U_ERR_LIBS = 
ENV_U_ERR_INCS = -I libft -I errors -I env_u_err

# **************************************************************************** #
# TOK TARGET DESCRIPTION

TOK_NAME = tok
TOK_PATH = tok
TOK_FILE = tok/libtok.a
TOK_SRCS = instr_mkr.c mini_tok.c stg_two.c syntax_check.c tok_arr.c tok_com.c tok_end.c tok_pipe.c tok_q.c tok_rdr.c tok_sp.c tok_var.c tok_word.c tokenizer.c
TOK_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(TOK_SRCS))
TOK_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(TOK_SRCS))
TOK_LIBS = 
TOK_INCS = -I libft -I .

# **************************************************************************** #
# SH TARGET DESCRIPTION

SH_NAME = sh
SH_PATH = .
SH_FILE = ./libsh.a
SH_SRCS = d_lists.c
SH_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(SH_SRCS))
SH_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(SH_SRCS))
SH_LIBS = 
SH_INCS = -I libft -I .

# **************************************************************************** #
# EXECUTER TARGET DESCRIPTION

EXECUTER_NAME = executer
EXECUTER_PATH = executer
EXECUTER_FILE = executer/libexecuter.a
EXECUTER_SRCS = bins.c cd.c echo.c explorer.c exs.c fds_intr.c forker.c ft_export.c get_next_line.c maux.c mshell.c mult.c pwd.c
EXECUTER_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(EXECUTER_SRCS))
EXECUTER_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(EXECUTER_SRCS))
EXECUTER_LIBS = 
EXECUTER_INCS = -I libft -I tok

# **************************************************************************** #
# MINISHELL TARGET DESCRIPTION

MINISHELL_NAME = minishell
MINISHELL_PATH = .
MINISHELL_FILE = ./minishell
MINISHELL_SRCS = mshell.c
MINISHELL_OBJS = $(patsubst %, $(OBJ_DIR)/%.o, $(MINISHELL_SRCS))
MINISHELL_DEPS = $(patsubst %, $(OBJ_DIR)/%.d, $(MINISHELL_SRCS))
MINISHELL_LIBS = -l d_list -L d_list -l ft -L libft -l env_u_err -L env_u_err -l tok -L tok -l sh -L . -l executer -L executer
MINISHELL_INCS = -I libft -I .

# **************************************************************************** #
# GENERIC RULES

.PHONY: all re clean fclean
.DEFAULT_GOAL = all

all: $(D_LIST_FILE) $(FT_FILE) $(ENV_U_ERR_FILE) $(TOK_FILE) $(SH_FILE) $(EXECUTER_FILE) $(MINISHELL_FILE)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(D_LIST_FILE) $(FT_FILE) $(ENV_U_ERR_FILE) $(TOK_FILE) $(SH_FILE) $(EXECUTER_FILE) $(MINISHELL_FILE)

re: fclean all

$(D_LIST_FILE): $(D_LIST_OBJS)
	@ar rc $(D_LIST_FILE) $(D_LIST_OBJS)
	@ranlib $(D_LIST_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(D_LIST_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(D_LIST_INCS) -o $@ -c $< -MMD

$(FT_FILE): $(FT_OBJS)
	@ar rc $(FT_FILE) $(FT_OBJS)
	@ranlib $(FT_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(FT_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(FT_INCS) -o $@ -c $< -MMD

$(ENV_U_ERR_FILE): $(ENV_U_ERR_OBJS)
	@ar rc $(ENV_U_ERR_FILE) $(ENV_U_ERR_OBJS)
	@ranlib $(ENV_U_ERR_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(ENV_U_ERR_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(ENV_U_ERR_INCS) -o $@ -c $< -MMD

$(TOK_FILE): $(TOK_OBJS)
	@ar rc $(TOK_FILE) $(TOK_OBJS)
	@ranlib $(TOK_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(TOK_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(TOK_INCS) -o $@ -c $< -MMD

$(SH_FILE): $(SH_OBJS)
	@ar rc $(SH_FILE) $(SH_OBJS)
	@ranlib $(SH_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(SH_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(SH_INCS) -o $@ -c $< -MMD

$(EXECUTER_FILE): $(EXECUTER_OBJS)
	@ar rc $(EXECUTER_FILE) $(EXECUTER_OBJS)
	@ranlib $(EXECUTER_FILE)
	@printf 'Finished	\033[1;36m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(EXECUTER_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(EXECUTER_INCS) -o $@ -c $< -MMD

$(MINISHELL_FILE): $(D_LIST_FILE) $(FT_FILE) $(ENV_U_ERR_FILE) $(TOK_FILE) $(SH_FILE) $(EXECUTER_FILE) $(MINISHELL_OBJS)
	@$(C_COMPILER) $(C_LFLAGS) $(C_STANDART) -o $(MINISHELL_FILE) $(MINISHELL_OBJS)  $(MINISHELL_LIBS)
	@printf 'Finished	\033[1;32m\033[7m$@ \033[0m\n\n'

$(OBJ_DIR)/%.c.o: $(MINISHELL_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf 'Compiling	\033[1;33m$<\033[0m ...\n'
	@$(C_COMPILER) $(C_CFLAGS) $(C_STANDART) $(MINISHELL_INCS) -o $@ -c $< -MMD

-include $(D_LIST_DEPS) $(FT_DEPS) $(ENV_U_ERR_DEPS) $(TOK_DEPS) $(SH_DEPS) $(EXECUTER_DEPS) $(MINISHELL_DEPS)

from package import generate_makefile

# LIBRARIES

LIBFT = {
	"name": "ft",
	"out": "libft",
	"type": "lib",
	"path": "libft",
	"sources": ["*.c"],
	"includes": ["libft"]
}

ENV_VAR = {
    "name": "env_u_err",
    "out": "env_u_err",
    "type": "lib",
    "path": "env_u_err",
    "sources": ["*.c"],
    "includes": ["libft", "errors", "env_u_err"]
}

EXECR = {
    "name": "executer",
    "out": "executer",
    "type": "lib",
    "path": "executer",
    "sources": ["*.c"],
    "includes": ["libft", "tok"]
}

TOK = {
    "name": "tok",
    "out": "tok",
    "type": "lib",
    "path": "tok",
    "sources": ["*.c"],
    "includes": ["libft", "."]
}

SH = {
    "name": "sh",
    "out": ".",
    "type": "lib",
    "path": ".",
    "sources": ["d_lists.c"],
    "includes": ["libft", "."]
}

# EXECUTABLES

MIS = {
    "name": "minishell",
    "out": ".",
    "type": "prog",
    "sources": ["mshell.c"],
    "includes": ["libft", "."],
    "peerdirs": [LIBFT, ENV_VAR, TOK, SH, EXECR],
}

COMPILERS = {
    "c": {
        "flags": "-Wall -Wextra -Werror -fsanitize=address",
        "file_extension": "c",
        "std": "-std=c99",
        "binary": "clang",
    }
}

generate_makefile(MIS, COMPILERS)
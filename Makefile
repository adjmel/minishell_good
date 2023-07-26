NAME = minishell

CC = cc
RM = rm -rf
INC = -I inc -I ~/goinfre/homebrew/opt/readline/include/readline/
CFLAGS = -Wall -Wextra -Werror $(INC)
READLINE = -lreadline -L ~/goinfre/homebrew/opt/readline/lib/

NONE = '\033[0m'
GREEN = '\033[32m'
GRAY = '\033[2;37m'
ITALIC = '\033[3m'

BUILTINS_DIR = builtins
BUILTINS = $(addprefix $(BUILTINS_DIR)/, builtins_utils.c re_cd.c re_echo.c re_env.c re_exit.c re_export.c re_pwd.c re_unset.c)

LIBFT_DIR = libft
LIBFT = $(addprefix $(LIBFT_DIR)/, ft_strlen.c ft_strdup.c ft_freearr.c ft_tabsize.c ft_strcmp.c ft_subarr.c ft_strcjoin.c ft_split.c ft_strstr.c ft_tabdup.c ft_substr.c ft_itoa.c ft_strchr.c ft_strjoin.c ft_atoi.c ft_bzero.c ft_strrchr.c fd_printf.c ft_getenv.c)

PARSE_DIR = src/parsing
PARSE = $(addprefix $(PARSE_DIR)/, parsing.c syntax_error.c lexer.c concate.c parser.c lst_addback.c newnode.c absolute_path.c expand.c parentheses_check.c init_list.c init_rd.c wildcard.c readdir.c pattern_match.c)

EXEC_DIR = src/execution
EXEC = $(addprefix $(EXEC_DIR)/, supervisor.c exec_command.c exec_builtin.c exec_heredoc.c init_data.c supervisor_utils.c exec_helpers.c)

SRCS_DIR = src
SRCS = $(addprefix $(SRCS_DIR)/, minishell.c clear.c)

OBJS = $(SRCS:.c=.o) $(LIBFT:.c=.o) $(PARSE:.c=.o) $(EXEC:.c=.o) $(BUILTINS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo $(ITALIC)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@stty -echoctl
	@$(CC) $(CFLAGS) $(OBJS) $(READLINE) -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)

clean:
	@echo $(ITALIC)$(GRAY) "     - Removing object files..." $(NONE)
	@$(RM) $(OBJS)

fclean: clean
	@echo $(ITALIC)$(GRAY) "     - Removing $(NAME)..." $(NONE)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

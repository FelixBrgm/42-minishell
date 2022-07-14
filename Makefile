AR := ar rcs
NAME = minishell
CC = cc
RM = rm -rf
# CFLAGS = -Wall -Wextra -Werror
CFLAGS = -iquote /Users/$(USER)/goinfre/.brew/opt/readline/include/readline/


SRC := src/
INPUT := input/
CHILDREN := children/
BUILTIN := builtin/
UTILS := utils/


# INPUT
INPUTCFILES := input_read.c input_parse_test.c dredir_in.c dredir_out.c redir_in.c redir_out.c split_mod.c \
				input_add_spaces.c set_vars.c input_rem_quotes.c input_expand_rem_redir.c set_files.c set_cmds.c
INPUTCFILES := $(addprefix $(INPUT), $(INPUTCFILES))
INPUTCFILES := $(addprefix $(SRC), $(INPUTCFILES))

# CHILDREN
CHILDRENCFILES := children_exec.c child_exec.c limiter_exec.c child_where.c children_free.c child_exec_utils.c children_exec_utils.c
CHILDRENCFILES := $(addprefix $(CHILDREN), $(CHILDRENCFILES))
CHILDRENCFILES := $(addprefix $(SRC), $(CHILDRENCFILES))

# BUILTIN
BUILTINCFILES := builtin_exec.c builtin_is_cmd.c builtin_echo.c builtin_cd.c builtin_pwd.c builtin_export.c builtin_env.c builtin_unset.c builtin_exit.c
BUILTINCFILES := $(addprefix $(BUILTIN), $(BUILTINCFILES))
BUILTINCFILES := $(addprefix $(SRC), $(BUILTINCFILES))

# UTILS
UTILSCFILES := utils_env.c utils_dllist.c utils_llist.c open_files.c
UTILSCFILES := $(addprefix $(UTILS), $(UTILSCFILES))
UTILSCFILES := $(addprefix $(SRC), $(UTILSCFILES))

# SPEC
CFILES := global_free.c set_to_default.c
CFILES := $(addprefix $(SRC), $(CFILES))

# ALL
CFILES := $(CFILES) $(INPUTCFILES) $(CHILDRENCFILES) $(BUILTINCFILES) $(UTILSCFILES) minishell.c
OFILES := $(CFILES:.c=.o)

# CFILES := $(CFILES) $(INPUTCFILES) $(UTILSCFILES) minishell.c
# OFILES := $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	make -C libs
	$(CC) $(OFILES) libs/libs.a -fsanitize=address -g -L/Users/$(USER)/goinfre/.brew/opt/readline/lib -iquote /Users/$(USER)/goinfre/.brew/opt/readline/include/readline/ -lreadline -o $(NAME) 

clean: 
	$(RM) $(OFILES)
	make clean -C libs

fclean: clean
	$(RM) $(NAME)
	make fclean -C libs

re: fclean all


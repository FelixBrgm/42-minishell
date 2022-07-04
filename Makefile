AR := ar rcs
NAME = minishell
CC = cc
RM = rm -rf
# CFLAGS = -Wall -Wextra -Werror


SRC := src/
INPUT := input/
CHILDREN := children/
BUILTIN := builtin/


# INPUT
INPUTCFILES := input_read.c input_parse.c
INPUTCFILES := $(addprefix $(INPUT), $(INPUTCFILES))
INPUTCFILES := $(addprefix $(SRC), $(INPUTCFILES))

# CHILDREN
CHILDRENCFILES := children_exec.c child_exec.c limiter_exec.c children_free.c
CHILDRENCFILES := $(addprefix $(CHILDREN), $(CHILDRENCFILES))
CHILDRENCFILES := $(addprefix $(SRC), $(CHILDRENCFILES))

# BUILTIN
BUILTINCFILES := builtin_exec.c builtin_is_cmd.c builtin_echo.c builtin_cd.c
BUILTINCFILES := $(addprefix $(BUILTIN), $(BUILTINCFILES))
BUILTINCFILES := $(addprefix $(SRC), $(BUILTINCFILES))

# SPEC
CFILES := global_free.c set_to_default.c
CFILES := $(addprefix $(SRC), $(CFILES))

# ALL
CFILES := $(CFILES) $(INPUTCFILES) $(CHILDRENCFILES) $(BUILTINCFILES) minishell.c
OFILES := $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	make -C libs
	$(CC) $(OFILES) libs/libs.a -L/Users/$(USER)/goinfre/.brew/opt/readline/lib -iquote /Users/$(USER)/goinfre/.brew/opt/readline/include/readline/ -lreadline -o $(NAME) 

clean: 
	$(RM) $(OFILES)
	make clean -C libs

fclean: clean
	$(RM) $(NAME)
	make fclean -C libs

re: fclean all


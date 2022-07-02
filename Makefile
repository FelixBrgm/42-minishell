AR := ar rcs
NAME = minishell
CC = cc
RM = rm -rf
# CFLAGS = -Wall -Wextra -Werror


SRC := src/
INPUT := input/
CHILDREN := children/


# INPUT
INPUTCFILES := input_read.c input_parse.c
INPUTCFILES := $(addprefix $(INPUT), $(INPUTCFILES))
INPUTCFILES := $(addprefix $(SRC), $(INPUTCFILES))

# CHILDREN
CHILDRENCFILES := children_exec.c children_free.c
CHILDRENCFILES := $(addprefix $(CHILDREN), $(CHILDRENCFILES))
CHILDRENCFILES := $(addprefix $(SRC), $(CHILDRENCFILES))


CFILES := global_free.c set_to_default.c
CFILES := $(addprefix $(SRC), $(CFILES))

# ALL
CFILES := $(CFILES) $(INPUTCFILES) $(CHILDRENCFILES) minishell.c
OFILES := $(CFILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(OFILES) -L/Users/fbruggem/goinfre/.brew/opt/readline/lib -I/Users/fbruggem/goinfre/.brew/opt/readline/include/readline -lreadline -o $(NAME) 

clean: 
	$(RM) $(OFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all


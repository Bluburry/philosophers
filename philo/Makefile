NAME	= philo

# flags
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g -pthread -fsanitize=thread
RM		= rm -rf
AR		= ar -rcs

# folders
INC		= include
OUTPUT	= out
SRC		= src
REQ		= $(addprefix $(SRC)/, utils) $(addprefix $(SRC)/, dinner_handle) \
	$(addprefix $(SRC)/, philo_stack)
_FLDRS	= $(SRC) $(REQ)

VPATH	= $(_FLDRS)

# files
MAIN	= $(addprefix $(SRC)/, philos.c)
UTILS	= philo_utils dinner_utils validate_utils
STACK	= stack_philosophers destroy_philosophers 
DINNER	= philo_dinner dinner_handler lonely_philo

_FILES	= $(UTILS) $(STACK) $(DINNER)
OBJS	= $(_FILES:%=%.o)
TARGET	= $(addprefix $(OUTPUT)/, $(OBJS))


all : $(NAME)

$(NAME) : $(OUTPUT) $(TARGET)
	$(CC) $(CFLAGS) $(MAIN) $(TARGET) -o $(NAME) -I $(INC)

$(OUTPUT)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT) :
	mkdir -p $(OUTPUT)


clean : 
	$(RM) $(OUTPUT)
	$(RM) $(OUTPUT_SAN)

fclean : 
	$(RM) $(OUTPUT)
	$(RM) $(NAME)

re : fclean all


.SILENT :

.PHONY : all, clean, fclean, re, sanitized

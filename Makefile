OBJS_DIR		=	.objs
SRCS_DIR		=	src
HEADER_DIR		=	includes

LIB				=	$(HEADER_DIR)/philosophers.h

SRC			=	$(SRCS_DIR)/main.c \
				$(SRCS_DIR)/init.c \
				$(SRCS_DIR)/init_utils.c \
				$(SRCS_DIR)/launch_threads.c \
				$(SRCS_DIR)/dinner.c \
				$(SRCS_DIR)/dinner_utils.c \
				$(SRCS_DIR)/checkers.c \
				$(SRCS_DIR)/utils.c \
				$(SRCS_DIR)/ft_atoi.c

OBJ			=	$(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRC))

NAME	=	philo
CC		=	cc
FLAGS	=	-Wall -Werror -Wextra -I $(HEADER_DIR)

$(OBJS_DIR)/%.o:		$(SRCS_DIR)/%.c $(LIB)
						mkdir -p $(@D)
						$(CC) $(FLAGS) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJ) $(LIB)
			$(CC) $(OBJ) $(FLAGS) -o $(NAME)

clean:
		rm -f ${OBJ}
		rm -f philo

fclean:	clean
		rm -f ${NAME}

re:	fclean all

.PHONY:	all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/02 11:22:48 by jcanteau          #+#    #+#              #
#    Updated: 2019/11/07 11:27:33 by jcanteau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

INC_NAME += wolf3d.h
# INC_NAME += keys.h
# INC_NAME += colors.h

SRC_NAME += main.c
SRC_NAME += mlx_start_up.c

OBJ_NAME = $(SRC_NAME:.c=.o)

LIB_NAME = libft.a

INC_PATH = ./includes/
SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
LIB_PATH = ./libft/

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
HEAD = $(addprefix $(INC_PATH), $(INC_NAME))
LIB = $(addprefix $(LIB_PATH), $(LIB_NAME))

FRAMEWORK = -framework OpenGL -framework AppKit
MLXFLAG = -I /usr/local/include -L /usr/local/lib -lmlx
CFLAGS = -Wall -Wextra -Werror

$(CC) = gcc

###############################################################################

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/.
	$(CC) $(CFLAGS) $(MLXFLAG) $(OBJ) $(FRAMEWORK) $(LIB) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEAD)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $< 

clean:
	make clean -C $(LIB_PATH)
	$(RM) -rf $(OBJ_PATH)

fclean: clean debug_clean
	$(RM) $(LIB)
	$(RM) $(NAME) $(NAME).ubuntu

re: fclean all

debug:
	make -C $(LIB_PATH)
	$(CC) -g3 -fsanitize=address,undefined $(CFLAGS) $(SRC) $(LIB) $(MLXFLAG) $(FRAMEWORK)

debug_clean:
	$(RM) -rf a.out a.out.DSYM
	
norm:
	norminette $(SRC) $(HEAD) $(LIB_PATH)

ubuntu: $(OBJ)
	make -C $(LIB_PATH)
	$(CC) $(CFLAGS) $(MLXFLAG) $(OBJ) $(LIB) -o $(NAME) -lmlx -lXext -lX11 -lm

.PHONY: clean fclean re all debug debug_clean norm ubuntu
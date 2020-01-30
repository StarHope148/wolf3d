# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcanteau <jcanteau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/02 11:22:48 by jcanteau          #+#    #+#              #
#    Updated: 2020/01/30 17:16:19 by jcanteau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

INC_NAME += wolf3d.h
INC_NAME += colors.h

SRC_NAME += main.c
SRC_NAME += wolf3d.c
SRC_NAME += sdl_start_up.c
SRC_NAME += key_hook.c
SRC_NAME += image.c


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

#FRAMEWORK = -framework OpenGL -framework AppKit
#MLXFLAG = -I /usr/local/include -L /usr/local/lib -lmlx
SDL2 = -I SDL2/include -L SDL2/lib -l SDL2-2.0.0
CFLAGS = -Wall -Wextra -Werror

$(CC) = gcc

###############################################################################

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/.
	$(CC) $(CFLAGS) $(SDL2) $(OBJ) $(LIB) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEAD)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -o $@ -c $< 

clean:
	make clean -C $(LIB_PATH)
	$(RM) -rf $(OBJ_PATH)

fclean: clean debug_clean
	$(RM) $(LIB)
	$(RM) $(NAME) $(NAME).ubuntu

re: fclean all

debug:
	make -C $(LIB_PATH)
	$(CC) -g3 -fsanitize=address,undefined $(CFLAGS) -I $(INC_PATH) $(SRC) $(LIB) $(SDL2)

debug_clean:
	$(RM) -rf a.out a.out.DSYM
	
norm:
	norminette $(SRC) $(HEAD) $(LIB_PATH)

ubuntu: $(OBJ)
	make -C $(LIB_PATH)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME) `sdl2-config --cflags --libs` -lm

.PHONY: clean fclean re all debug debug_clean norm ubuntu
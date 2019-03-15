# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: penzo <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/13 19:58:18 by penzo             #+#    #+#              #
#    Updated: 2019/03/15 21:11:12 by penzo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	21sh

CC			:=	gcc
CFLAGS		:=	-Wextra -Wall -Werror
FSA_FLAGS	:=	-pedantic -g3 -O1 -fsanitize=address
VAL_FLAGS	:=	-g

SRC_PATH	:=	srcs
OBJ_PATH	:=	objs
INC_PATH	:=	includes

SRC_NAME	:=	main.c tmp.c
INCL_NAME	:=	#TODO
OBJ_NAME	:=	$(SRC_NAME:.c=.o)

SRC			:=	$(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ			:=	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

INCL		:=	-Iincludes/ -Ilibft
LIB_PATH	:=	-Llibft
LIB_NAME	:=	-lft
LIB			:=	$(LIB_PATH) $(LIB_NAME)

.PHONY: all, clean, fclean, re, norm, fsa, val, rmh, adh

all: $(NAME)

libft/libft.a:
	$(MAKE) -C libft

fsa: $(OBJ) libft/libft.a
	$(CC) $(CFLAGS) $(FSA_FLAGS) $(LIB) $^ -o $(NAME)
	./$(NAME)

val: $(OBJ) libft/libft.a
	$(CC) $(CFLAGS) $(VAL_FLAGS) $(LIB) $^ -o $(NAME)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all \
		--show-reachable=no ./$(NAME)

rmh:
	./script/42header_c_rm.sh $(SRC)

adh: rmh
	vim -ns script/42header_add.keys $(SRC)

$(NAME): $(OBJ) libft/libft.a
	$(CC) $(LIB) $^ -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c Makefile
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(INCL) -o $@ -c $<

clean:
	$(MAKE) clean -C libft
	rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	$(MAKE) fclean -C libft
	rm -rfv $(NAME).dSYM
	rm -fv $(NAME)

re: fclean all

d: all
	./$(NAME)

norm: adh
	norminette $(SRC)
	norminette $(INC_PATH)/*.h #be careful wildcards

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: penzo <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/13 19:58:18 by penzo             #+#    #+#              #
#    Updated: 2019/03/21 16:55:39 by penzo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	21sh
OPT			:=	

CC			:=	gcc
CFLAGS		:=	-Wextra -Wall -Werror
#FSA_FLAGS	:=	-pedantic -g3 -O1 -fsanitize=address
FSA_FLAGS	:=	-g -fsanitize=address
VAL_FLAGS	:=	-g

SRC_PATH	:=	srcs
OBJ_PATH	:=	objs
INC_PATH	:=	includes

SRC_NAME	:=	main.c init_env.c errors.c environ_utils.c shlvl.c \
	environ_set.c prompt.c cmd_lst_utils.c handle_input.c free.c \
	my_strsplit.c lexer.c test_pipe.c
INCL_NAME	:=	tosh.h
OBJ_NAME	:=	$(SRC_NAME:.c=.o)

SRC			:=	$(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ			:=	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

INCL		:=	-Iincludes/ -Ilibft
LIB_PATH	:=	-Llibft
LIB_NAME	:=	-lft
LIB			:=	$(LIB_PATH) $(LIB_NAME)

.PHONY: all, clean, fclean, re, norm, fsa, val, rmh, adh, tags

all: $(NAME)

libft/libft.a:
	$(MAKE) -C libft

#fsa: $(OBJ) libft/libft.a
#	$(CC) $(CFLAGS) $(FSA_FLAGS) $(LIB) $^ -o $(NAME)
#	$(OPT) ./$(NAME)
fsa: $(SRC)
	$(CC) $(CFLAGS) $(FSA_FLAGS) $(INCL) $(LIB) $^ -o $(NAME)
	$(OPT) ./$(NAME)

#val: $(OBJ) libft/libft.a
#	$(CC) $(CFLAGS) $(VAL_FLAGS) $(LIB) $^ -o $(NAME)
#	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all \
#		--show-reachable=no $(OPT) ./$(NAME)
val: $(SRC) libft/libft.a
	$(CC) $(CFLAGS) $(VAL_FLAGS) $(INCL) $(LIB) $^ -o $(NAME)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all \
		--show-reachable=no $(OPT) ./$(NAME)

rmh:
	./script/42header_c_rm.sh $(SRC)

adh: rmh
	vim -ns script/42header_add.keys $(SRC)

$(NAME): $(OBJ) libft/libft.a
	$(CC) $(CFLAGS) $(LIB) $^ -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c Makefile
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	$(CC) $(CFLAGS) $(INCL) -o $@ -c $<

tag:
	ctags -R .

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
	$(OPT) ./$(NAME)

norm: adh
	norminette $(SRC)
	norminette $(INC_PATH)/*.h #be careful wildcards

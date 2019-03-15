# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: penzo <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/30 15:37:46 by penzo             #+#    #+#              #
#    Updated: 2019/03/12 14:25:14 by penzo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a
CC=gcc
CFLAGS=-Werror -Wextra -Wall
CFILES=ft_tolower.c \
	   ft_toupper.c \
	   ft_isprint.c \
	   ft_isascii.c \
	   ft_isalnum.c \
	   ft_isdigit.c \
	   ft_isalpha.c \
	   ft_strlen.c \
	   ft_strdup.c \
	   ft_strndup.c \
	   ft_strcpy.c \
	   ft_strncpy.c \
	   ft_strcat.c \
	   ft_strncat.c \
	   ft_strlcat.c \
	   ft_strnew.c \
	   ft_strdel.c \
	   ft_strclr.c \
	   ft_strequ.c \
	   ft_putchar.c \
	   ft_putstr.c \
	   ft_putendl.c \
	   ft_putnbr.c \
	   ft_putchar_fd.c \
	   ft_putstr_fd.c \
	   ft_putnbr_fd.c \
	   ft_putendl_fd.c \
	   ft_itoa.c \
	   ft_atoi.c \
	   ft_swap.c \
	   ft_strsplit.c \
	   ft_strrev.c \
	   ft_strtrim.c \
	   ft_strjoin.c \
	   ft_strsub.c \
	   ft_strnequ.c \
	   ft_memalloc.c \
	   ft_memdel.c \
	   ft_striter.c \
	   ft_striteri.c \
	   ft_strmap.c \
	   ft_strmapi.c \
	   ft_strchr.c \
	   ft_strrchr.c \
	   ft_strcmp.c \
	   ft_strncmp.c \
	   ft_strstr.c \
	   ft_strnstr.c \
	   ft_memset.c \
	   ft_bzero.c \
	   ft_memcpy.c \
	   ft_memccpy.c \
	   ft_memmove.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_lstnew.c \
	   ft_lstlen.c \
	   ft_lstdelone.c \
	   ft_lstdel.c \
	   ft_lstadd.c \
	   ft_lstappend.c \
	   ft_lstiter.c \
	   ft_lstmap.c \
	   ft_put_nultab.c \
	   ft_is_c_in_str.c \
	   gnl/get_next_line.c \
	   get_ntab_len.c \
	   ft_strcmp_until_c.c \

OFILES=${CFILES:.c=.o}
DEPS=libft.h
LIBS	:= -I . 

$(NAME): $(OFILES)
	ar rc $(NAME) $(OFILES)
	ranlib $(NAME)

%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS) $(LIBS)

all: $(NAME)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: auguyon <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/17 17:43:49 by auguyon           #+#    #+#              #
#    Updated: 2019/07/17 17:43:56 by auguyon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	auguyon.filler

SRCS	=	sources/aux.c sources/filler.c sources/minimization.c

CC		=	gcc

INCL	=	-I libft/inc/ -I include/ \

INCL_NORM	=	libft/inc/ include/

FLAGS	=	-Wall -Wextra -Werror

OBJS	=	$(SRCS:.c=.o)

LIB		=	libft/libft.a

RM		=	rm -rf

.SILENT	:

.PHONY	: 	all clean fclean re

#Colors
_BLACK=\x1b[30m
_RED=\x1b[31m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_BLUE=\x1b[34m
_PURPLE=\x1b[35m
_CYAN=\x1b[36m
_WHITE=\x1b[37m
_END=\x1b[0m

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			make -C libft/
			echo "$(_RED)Compiling libft... $(_GREEN)Done$(_END)"
			$(CC) -o $(NAME) $(OBJS) $(LIB) $(FWORK)

$(OBJS)	: 	%.o: %.c  Makefile include/filler_visual.h
			$(CC) $(FLAGS) $(INCL) -c $< -o $@

clean	:
			make clean -C libft/
			make clean -C bonus/
			$(RM) $(OBJS)
			echo "$(_RED)Cleaning obj... $(_GREEN)Done$(_END)"

fclean	:	clean
			$(RM) $(NAME)
			make fclean -C libft/
			make fclean -C bonus/
			echo "$(_RED)Cleaning all... $(_GREEN)Done$(_END)"

re		:	fclean all

recl	:	re
			make clean

norm	:	fclean
			echo "$(_RED)Starting norminette...$(_END)"
			norminette $(SRCS) $(INCL_NORM) | grep -B 1 '^Error' 2> /dev/null && echo "$(_RED)Norm KO :(" || echo "$(_GREEN)Norm OK ! :)$(_END)";

bonus	:
			make -C Bonus/
			$(CC) -o Generator generator.c ../libft/libft.a
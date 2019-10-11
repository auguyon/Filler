# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: auguyon <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/17 17:43:49 by auguyon           #+#    #+#              #
#    Updated: 2019/07/17 17:43:56 by auguyon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	visual_filler

SRCS	=	srcs/draw.c srcs/draw_2.c srcs/draw_form.c srcs/visual_filler.c \
			Get_Next_line/get_next_line.c \

CC		=	gcc

INCL	=	-I ../libft/inc/ -I include/ \
			-I ./frameworks/SDL2.framework/Headers \
			-I ./frameworks/SDL2_ttf.framework/Headers \
			-I ./frameworks/SDL2_image.framework/Headers \
			-I ./frameworks/SDL2_mixer.framework/Headers

INCL_NORM	=	../libft/inc/ include/

FLAGS	=	-Wall -Wextra -Werror

OBJS	=	$(SRCS:.c=.o)

FWORK	=	-lpthread -F ./frameworks/ -framework SDL2 -framework SDL2_image -framework SDL2_ttf \
			-framework SDL2_mixer -rpath ./frameworks/

LIB		=	../libft/libft.a

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
			$(CC) -o $(NAME) $(OBJS) $(LIB) $(FWORK)

$(OBJS)	: 	%.o: %.c  Makefile include/filler_visual.h
			$(CC) $(FLAGS) $(INCL) -c $< -o $@

clean	:
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

recl	:	re
			make clean

norm	:	fclean
			echo "$(_RED)Starting norminette...$(_END)"
			norminette $(SRCS) $(INCL_NORM) | grep -B 1 '^Error' 2> /dev/null && echo "$(_RED)Norm KO :(" || echo "$(_GREEN)Norm OK ! :)$(_END)";
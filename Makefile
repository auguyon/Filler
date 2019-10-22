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

NAME_VISU	=	visual_filler

NAME_GEN	=	generator

SRCS	=	sources/aux.c sources/filler.c sources/minimization.c

SRCS_VISU	=	visu/draw.c visu/draw_2.c visu/draw_form.c visu/visual_filler.c

SRC_GEN	=	Bonus/maps_generator.c

CC		=	gcc

INCL	=	-I libft/inc/ -I includes/ \

INCL_VISU	=	-I libft/inc/ -I includes/ \
				-I ./frameworks/SDL2.framework/Headers \
				-I ./frameworks/SDL2_ttf.framework/Headers \
				-I ./frameworks/SDL2_image.framework/Headers \
				-I ./frameworks/SDL2_mixer.framework/Headers

INCL_NORM	=	libft/inc/ include/

FLAGS	=	-Wall -Wextra -Werror

OBJS	=	$(SRCS:.c=.o)

OBJS_VISU	=	$(SRCS_VISU:.c=.o)

OBJ_GEN	=	$(SRC_GEN:.c=.o)

FWORK	=	-lpthread -F ./frameworks/ -framework SDL2 -framework SDL2_image -framework SDL2_ttf \
			-framework SDL2_mixer -rpath ./frameworks/

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
			$(CC) -o $(NAME) $(OBJS) $(LIB)

$(OBJS)	: 	%.o: %.c Makefile includes/filler.h
			$(CC) $(FLAGS) $(INCL) -c $< -o $@

clean	:
			make clean -C libft/
			$(RM) $(OBJS) $(OBJS_VISU) $(OBJ_GEN)
			echo "$(_RED)Cleaning obj... $(_GREEN)Done$(_END)"

fclean	:	clean
			$(RM) $(NAME) $(NAME_VISU) $(NAME_GEN)
			make fclean -C libft/
			echo "$(_RED)Cleaning all... $(_GREEN)Done$(_END)"

re		:	fclean all

recl	:	re
			make clean

norm	:	fclean
			echo "$(_RED)Starting norminette...$(_END)"
			norminette $(SRCS) $(INCL_NORM) | grep -B 1 '^Error' 2> /dev/null && echo "$(_RED)Norm KO :(" || echo "$(_GREEN)Norm OK ! :)$(_END)";

visu	:	all
			$(CC) -o $(NAME_VISU) $(FLAGS) $(SRCS_VISU) $(LIB) $(INCL_VISU) $(FWORK)

bonus	:	visu
			echo "$(_RED)Compiling bonus... $(_GREEN)Done$(_END)"
			$(CC) -o $(NAME_GEN) $(FLAGS) $(SRC_GEN) $(LIB)

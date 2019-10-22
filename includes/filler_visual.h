/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_visual.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:35:00 by auguyon           #+#    #+#             */
/*   Updated: 2019/03/16 17:19:23 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_VISUAL_H
# define FILLER_VISUAL_H

# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <SDL_mixer.h>
# include <math.h>
# include "../libft/inc/libft.h"

# define WEIGHT_WIN		1400
# define HEIGHT_WIN		1200
# define BOARD_X		1300
# define BOARD_Y		1100

# define BLACK			0
# define BLUE			210
# define LIGHT_BLUE		39423
# define RED			12451840
# define LIGHT_RED		16718362

# define GREEN			65280
# define PURPLE			16711935
# define WHITE			16777215
# define GREY			6908265

typedef struct			s_grid
{
	int					x;
	int					y;
	int					x_max;
	int					y_max;
	int					space_hori;
	int					space_verti;
	int					square;
	int					square_center;
	int					x1;
	int					x2;
	int					y1;
	int					y2;
	int					x1_t;
	int					x2_t;
	int					y1_t;
	int					y2_t;
}						t_grid;

typedef struct			s_board
{
	char				**grid;
	char				*player_one;
	char				*player_two;
	char				*score_one;
	char				*score_two;
	int					x;
	int					y;
	int					col;
	int					col_tmp;
	int					line;
	int					line_tmp;
	int					i;
	int					j;
	int					time;
}						t_board;

typedef struct			s_win
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	SDL_Surface			*surface;
	SDL_Surface			*p_one;
	SDL_Surface			*p_two;
	SDL_Surface			*p_one_f;
	SDL_Surface			*p_two_f;
	SDL_Surface			*score;
	SDL_Surface			*score_one;
	SDL_Surface			*score_two;
	SDL_Surface			*vs;
	SDL_Surface			*win;
	SDL_Event			event;
	TTF_Font			*font;
	TTF_Font			*font2;
	int					weight;
	int					height;
}						t_win;

typedef struct			s_circle
{
	int32_t				x;
	int32_t				y;
	int32_t				tx;
	int32_t				ty;
	int32_t				error;
}						t_circle;

void					draw(t_win *win, t_grid *grid, t_board *board);
void					put_pixel_to_surface(SDL_Surface *srfc, int x,
							int y, Uint32 color);
void					draw_circle(t_win *win, int32_t cx, int32_t centrey,
							int32_t radius);
void					draw_line(t_grid *grid, t_win *win, int i, int j);
void					color_square(t_win *win, t_grid *grid, t_board *board);
void					clean(t_win *win, t_board *board);
int						board_recuperation(t_board *board);
int						score_recuperation(t_board *board, char *line);
void					write_to_surface(t_win *win, t_board *board,
							t_grid *grid, int code);

#endif

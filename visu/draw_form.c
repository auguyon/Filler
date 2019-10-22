/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_form.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:35:00 by auguyon           #+#    #+#             */
/*   Updated: 2019/03/16 17:19:23 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler_visual.h"

void		put_pixel_to_surface(SDL_Surface *srfc, int x, int y, Uint32 color)
{
	Uint32	*pixels;

	pixels = srfc->pixels;
	if (x >= 0 && y >= 0 && x < srfc->w && y < srfc->h)
		pixels[y * srfc->w + x] = color;
}

void		color_square(t_win *win, t_grid *grid, t_board *b)
{
	int x;
	int y;
	int color;

	if (b->grid[b->i][b->j] == 'X' || b->grid[b->i][b->j] == 'x')
		color = b->grid[b->i][b->j] == 'X' ? BLUE : LIGHT_BLUE;
	else if (b->grid[b->i][b->j] == 'O' || b->grid[b->i][b->j] == 'o')
		color = b->grid[b->i][b->j] == 'O' ? RED : LIGHT_RED;
	x = grid->x1 + (grid->square * b->j) + 1;
	while (x < (grid->x2 + (grid->square * b->j) - 1))
	{
		y = grid->y1 + (grid->square * b->i);
		while (y < (grid->y2 + (grid->square * b->i) - 1))
		{
			put_pixel_to_surface(win->surface, x, y, color);
			y++;
		}
		x++;
	}
}

static void	draw_circle_2(t_circle *s, SDL_Surface *sr, int32_t cx, int32_t cy)
{
	put_pixel_to_surface(sr, cx + s->x, cy - s->y, 0);
	put_pixel_to_surface(sr, cx + s->x, cy + s->y, 0);
	put_pixel_to_surface(sr, cx - s->x, cy - s->y, 0);
	put_pixel_to_surface(sr, cx - s->x, cy + s->y, 0);
	put_pixel_to_surface(sr, cx + s->y, cy - s->x, 0);
	put_pixel_to_surface(sr, cx + s->y, cy + s->x, 0);
	put_pixel_to_surface(sr, cx - s->y, cy - s->x, 0);
	put_pixel_to_surface(sr, cx - s->y, cy + s->x, 0);
}

void		draw_circle(t_win *win, int32_t cx, int32_t centrey, int32_t radius)
{
	const int32_t	diameter = (radius * 2);
	t_circle		s;

	s.x = (radius - 1);
	s.y = 0;
	s.tx = 1;
	s.ty = 1;
	s.error = (s.tx - diameter);
	while (s.x >= s.y)
	{
		draw_circle_2(&s, win->surface, cx, centrey);
		if (s.error <= 0)
		{
			s.y++;
			s.error += s.ty;
			s.ty += 2;
		}
		if (s.error > 0)
		{
			s.x--;
			s.tx += 2;
			s.error += (s.tx - diameter);
		}
	}
}

void		draw_line(t_grid *g, t_win *win, int i, int j)
{
	int	x;
	int	y;

	g->x1_t = g->x1 + (g->square * j) + (g->square / 12);
	g->x2_t = g->x2 + (g->square * j) - (g->square / 10);
	g->y1_t = g->y1 + (g->square * i) + (g->square / 10);
	g->y2_t = g->y2 + (g->square * i) - (g->square / 12);
	if (g->x1_t <= g->x2_t && (g->x2_t - g->x1_t) >= abs(g->y2_t - g->y1_t))
	{
		x = g->x1_t - 1;
		while (x <= g->x2_t && (g->x2_t - g->x1_t) != 0 && ++x)
			put_pixel_to_surface(win->surface, x, g->y2_t + (g->y1_t - g->y2_t)
				* (x - g->x1_t) / (g->x2_t - g->x1_t), 100);
	}
	if (g->y1_t <= g->y2_t && (g->y2_t - g->y1_t) >= abs(g->x2_t - g->x1_t))
	{
		y = g->y2_t + 1;
		while (y >= g->y1_t && (g->y2_t - g->y1_t) != 0 && --y)
			put_pixel_to_surface(win->surface, g->x1_t + ((g->x2_t - g->x1_t)
				* (y - g->y1_t)) / (g->y2_t - g->y1_t), y, 100);
	}
}

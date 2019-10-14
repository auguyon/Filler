/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:35:00 by auguyon           #+#    #+#             */
/*   Updated: 2019/03/16 17:19:23 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler_visual.h"

void		clean(t_win *win, t_board *board)
{
	SDL_FreeSurface(win->surface);
	SDL_FreeSurface(win->p_one);
	SDL_FreeSurface(win->p_two);
	SDL_FreeSurface(win->p_one_f);
	SDL_FreeSurface(win->p_two_f);
	SDL_FreeSurface(win->score);
	if (win->score_one)
		SDL_FreeSurface(win->score_one);
	if (win->score_two)
		SDL_FreeSurface(win->score_two);
	SDL_FreeSurface(win->vs);
	SDL_FreeSurface(win->win);
	SDL_DestroyRenderer(win->renderer);
	SDL_DestroyWindow(win->window);
	TTF_CloseFont(win->font);
	TTF_CloseFont(win->font2);
	SDL_Quit();
	TTF_Quit();
	free(board->player_one);
	free(board->player_two);
	if (board->player_one)
		free(board->score_one);
	if (board->score_two)
		free(board->score_two);
}

static void	fill_grid(t_board *b, t_grid *grid, t_win *win)
{
	b->i = 0;
	while (b->grid[b->i] && !(b->j = 0))
	{
		while (b->grid[b->i][b->j])
		{
			if (b->grid[b->i][b->j] == 'X' || b->grid[b->i][b->j] == 'x')
			{
				color_square(win, grid, b);
				draw_line(grid, win, b->i, b->j);
			}
			else if (b->grid[b->i][b->j] == 'O' || b->grid[b->i][b->j] == 'o')
			{
				color_square(win, grid, b);
				draw_circle(win, (grid->space_hori + grid->square_center +
				(grid->square * b->j)), (grid->space_verti + grid->square_center
					+ (grid->square * b->i)), grid->square / 3);
				draw_circle(win, (grid->space_hori + grid->square_center +
				(grid->square * b->j)), (grid->space_verti + grid->square_center
					+ (grid->square * b->i)), (grid->square / 3) - 1);
			}
			b->j++;
		}
		b->i++;
	}
}

static void	grid_creation(t_board *board, t_grid *grid, t_win *win, int x)
{
	int y;

	x = grid->space_hori;
	board->col_tmp = grid->space_hori;
	while (x <= (win->weight - grid->space_hori))
	{
		y = grid->space_verti;
		board->line_tmp = grid->space_verti;
		while (y <= (win->height - grid->space_verti))
		{
			if (x == board->col_tmp || x == board->col_tmp - 1)
				put_pixel_to_surface(win->surface, x, y, BLACK);
			else if (y == board->line_tmp || y == board->line_tmp - 1)
			{
				put_pixel_to_surface(win->surface, x, y, BLACK);
				board->line_tmp += board->line;
			}
			else
				put_pixel_to_surface(win->surface, x, y, GREY);
			y++;
		}
		if (x == board->col_tmp)
			board->col_tmp += board->col;
		x++;
	}
}

static void	print_to_screen(t_win *win)
{
	SDL_Rect	dst2;

	dst2.x = 0;
	dst2.y = 0;
	SDL_BlitSurface(win->surface, NULL, win->surface, &dst2);
	win->texture = SDL_CreateTextureFromSurface(win->renderer, win->surface);
	SDL_SetRenderTarget(win->renderer, NULL);
	SDL_RenderCopy(win->renderer, win->texture, NULL, &dst2);
	SDL_RenderPresent(win->renderer);
	SDL_DestroyTexture(win->texture);
	SDL_PollEvent(&win->event);
}

void		draw(t_win *win, t_grid *grid, t_board *board)
{
	SDL_Rect	dst2;
	int			i;
	int			j;

	dst2.x = 0;
	dst2.y = 0;
	i = 1;
	while (42 && !(j = 0))
	{
		SDL_Delay(board->time);
		i = (i > 0 ? board_recuperation(board) : 0);
		grid_creation(board, grid, win, 0);
		fill_grid(board, grid, win);
		write_to_surface(win, board, grid, i);
		print_to_screen(win);
		if (i > 0)
			while (board->grid[j])
				free(board->grid[j++]);
		if (win->event.type == SDL_QUIT ||
			win->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			break ;
	}
	while (board->grid[j])
		free(board->grid[j++]);
}

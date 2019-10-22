/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_filler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:35:00 by auguyon           #+#    #+#             */
/*   Updated: 2019/03/16 17:19:23 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler_visual.h"

static void	grid_calculation(t_board *board, t_grid *grid, t_win *win)
{
	board->col = grid->y_max / board->y;
	board->line = grid->x_max / board->x;
	if (board->col > board->line)
		board->col = board->line;
	else
		board->line = board->col;
	grid->x = board->col * board->x;
	grid->y = board->line * board->y;
	grid->space_hori = ((win->weight - grid->y) / 2);
	grid->space_verti = ((win->height - grid->x) / 2);
	grid->square = board->col;
	grid->square_center = grid->square / 2;
	grid->x1 = grid->space_hori;
	grid->x2 = grid->space_hori + grid->square;
	grid->y1 = grid->space_verti;
	grid->y2 = grid->space_verti + grid->square;
}

static void	init_win(t_win *win, t_board *board, t_grid *grid)
{
	if (board->x > board->y)
	{
		win->weight = HEIGHT_WIN;
		win->height = WEIGHT_WIN;
		grid->x_max = BOARD_Y;
		grid->y_max = BOARD_X;
	}
	else
	{
		win->weight = WEIGHT_WIN;
		win->height = HEIGHT_WIN;
		grid->x_max = BOARD_X;
		grid->y_max = BOARD_Y;
	}
	win->window = SDL_CreateWindow("Filler Visual", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, win->weight, win->height, SDL_WINDOW_SHOWN);
	win->renderer = SDL_CreateRenderer(win->window, -1,
		SDL_RENDERER_ACCELERATED);
	win->surface = SDL_CreateRGBSurface(0, win->weight, win->height,
		32, 0, 0, 0, 0);
}

static void	get_player_name(t_board *board, int i, char *s, char *line)
{
	while (get_next_line(0, &line) && line[0] != '$')
		free(line);
	s = ft_strstr(line, ".filler");
	while (*(s - 1) != '/' && ++i)
		s--;
	if (!(board->player_one = (char*)malloc(sizeof(char) * i)))
		exit(0);
	i = 0;
	while (*s != '.')
		board->player_one[i++] = *s++;
	board->player_one[i] = '\0';
	free(line);
	while (!(i = 0) && get_next_line(0, &line) && line[0] != '$')
		free(line);
	s = ft_strstr(line, ".filler");
	while (*(s - 1) != '/' && ++i)
		s--;
	if (!(board->player_two = (char*)malloc(sizeof(char) * i)))
		exit(0);
	i = 0;
	while (*s != '.')
		board->player_two[i++] = *s++;
	board->player_two[i] = '\0';
	free(line);
}

static void	info_board(t_board *board)
{
	char	*line;
	int		i;

	i = 0;
	get_player_name(board, 0, NULL, NULL);
	while (get_next_line(0, &line) && line[0] != 'P')
		free(line);
	while (line[i] != ' ')
		i++;
	board->x = ft_atoi(line + (i++ + 1));
	while (line[i] != ' ')
		i++;
	board->y = ft_atoi(line + (i + 1));
	free(line);
	board->score_one = NULL;
	board->time = 0;
	board->time = board->time == 0 &&
		(board->x < 30 || board->y < 30) ? 120 : 0;
	board->time = board->time == 0 && ((board->x > 30 && board->x < 50)
		|| (board->y > 30 && board->y < 50)) ? 80 : board->time;
	board->time = board->time == 0 &&
		(board->x > 50 || board->x > 50) ? 40 : board->time;
}

int			main(int ac, char **av)
{
	t_grid		*grid;
	t_win		*win;
	t_board		*board;

	(void)ac;
	(void)av;
	if (!(grid = (t_grid*)malloc(sizeof(t_grid)))
		|| !(win = (t_win*)malloc(sizeof(t_win)))
		|| !(board = (t_board*)malloc(sizeof(t_board))))
		exit(0);
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	info_board(board);
	if (!(board->grid = (char**)malloc(sizeof(char*) * board->x + 2)))
		exit(0);
	init_win(win, board, grid);
	grid_calculation(board, grid, win);
	draw(win, grid, board);
	clean(win, board);
	free(board->grid);
	free(grid);
	free(win);
	free(board);
	return (0);
}

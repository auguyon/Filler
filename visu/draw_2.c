/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:35:00 by auguyon           #+#    #+#             */
/*   Updated: 2019/03/16 17:19:23 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler_visual.h"

int			score_recuperation(t_board *board, char *line)
{
	int i;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	board->score_one = ft_itoa(ft_atoi(line + i));
	free(line);
	if (board->score_one[0] == '0' && board->score_one[1] == '\0')
	{
		free(board->score_one);
		board->score_one = ft_strdup("Error");
	}
	get_next_line(0, &line);
	board->score_two = ft_itoa(ft_atoi(line + i));
	if (board->score_two[0] == '0' && board->score_two[1] == '\0')
	{
		free(board->score_two);
		board->score_two = ft_strdup("Error");
	}
	free(line);
	return (0);
}

int			board_recuperation(t_board *board)
{
	char	*line;
	int		i;

	i = 0;
	while (get_next_line(0, &line) && !ft_isdigit(line[0]) && line[0] != '=')
		free(line);
	board->grid[i++] = ft_strdup(line + 4);
	free(line);
	while (get_next_line(0, &line) && ft_isdigit(line[0]))
	{
		board->grid[i++] = ft_strdup(line + 4);
		free(line);
	}
	free(line);
	board->grid[i] = NULL;
	while (get_next_line(0, &line) && line[0] != '<')
		free(line);
	free(line);
	if (get_next_line(0, &line) && line[0] != '=')
		free(line);
	if (line[0] == '=')
		return (score_recuperation(board, line));
	return (1);
}

static void	init_font_n_name(t_win *win, t_board *board)
{
	static SDL_Color	blue = {0, 184, 230, 0};
	static SDL_Color	red = {220, 26, 26, 0};
	static SDL_Color	white = {255, 255, 255, 0};

	if (!win->font)
	{
		win->font = TTF_OpenFont("/Users/auguyon/font.ttf", 55);
		win->font2 = TTF_OpenFont("/Users/auguyon/font.ttf", 80);
		win->p_one = TTF_RenderText_Blended(win->font, board->player_one, red);
		win->vs = TTF_RenderText_Blended(win->font, "VS", white);
		win->p_two = TTF_RenderText_Blended(win->font, board->player_two, blue);
		win->win = TTF_RenderText_Blended(win->font2, "Winner is :", white);
		win->p_one_f = TTF_RenderText_Blended(win->font,
			board->player_one, white);
		win->p_two_f = TTF_RenderText_Blended(win->font,
			board->player_two, white);
		win->score = TTF_RenderText_Blended(win->font, "Scores :", white);
	}
	if (board->score_one && !win->score_one)
	{
		win->score_one = TTF_RenderText_Blended(win->font,
			board->score_one, red);
		win->score_two = TTF_RenderText_Blended(win->font,
			board->score_two, blue);
	}
}

static void	write_to_surface_2(t_win *win, t_grid *grid)
{
	SDL_Rect		pos;

	pos.y = win->height - 80;
	pos.x = 20;
	SDL_BlitSurface(win->score, NULL, win->surface, &pos);
	pos.x = grid->space_verti + 200;
	SDL_BlitSurface(win->score_one, NULL, win->surface, &pos);
	pos.x = win->weight - grid->space_verti - 400;
	SDL_BlitSurface(win->score_two, NULL, win->surface, &pos);
}

void		write_to_surface(t_win *win, t_board *board, t_grid *grid, int code)
{
	SDL_Rect		pos;

	init_font_n_name(win, board);
	pos.x = (win->weight / 2) - 500;
	pos.y = 30;
	SDL_BlitSurface(win->p_one, NULL, win->surface, &pos);
	pos.x = (win->weight / 2);
	SDL_BlitSurface(win->vs, NULL, win->surface, &pos);
	pos.x = (win->weight / 2) + 300;
	SDL_BlitSurface(win->p_two, NULL, win->surface, &pos);
	if (code == 0)
	{
		pos.y = (win->height / 2) - 100;
		pos.x = (win->weight / 2) - 200;
		SDL_BlitSurface(win->win, NULL, win->surface, &pos);
		pos.y = (win->height / 2);
		pos.x = (win->weight / 2) - 150;
		if (ft_atoi(board->score_one) > ft_atoi(board->score_two))
			SDL_BlitSurface(win->p_one_f, NULL, win->surface, &pos);
		else
			SDL_BlitSurface(win->p_two_f, NULL, win->surface, &pos);
		write_to_surface_2(win, grid);
	}
}

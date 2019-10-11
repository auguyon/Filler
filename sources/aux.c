/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:35:00 by auguyon           #+#    #+#             */
/*   Updated: 2019/03/16 17:19:23 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "filler.h"
#include "../libft/libft.h"

void	initialize(char *line, t_tab *piece, t_tab *map)
{
	int i;

	read(0, line, 34);
	map->c = line[10] == '1' ? 'O' : 'X';
	piece->c = line[10] == '1' ? 'X' : 'O';
	read(0, line, 8);
	ft_memset(line, 0, 50);
	i = 0;
	while (read(0, line + i, 1) && ft_isdigit(line[i]))
		i++;
	map->x = ft_atoi(line);
	ft_memset(line, 0, 50);
	i = 0;
	while (read(0, line + i, 1) && ft_isdigit(line[i]))
		i++;
	map->y = ft_atoi(line);
}

void	reset_map(t_tab *map)
{
	int i;

	i = 0;
	while (i < map->x)
		ft_memset(map->tab[i++], 0, map->y + 1);
}

void	reset_piece(t_tab *piece, t_tab *map)
{
	int i;

	i = 0;
	while (i < map->x)
		ft_memset(piece->tab[i++], 0, map->y + 1);
}

void	prt_pos(int best_x, int best_y)
{
	ft_putnbr(best_x);
	write(1, " ", 1);
	ft_putnbr(best_y);
	write(1, "\n", 1);
}

void	free_all(char *line, t_tab *piece, t_tab *map)
{
	int i;

	free(line);
	i = 0;
	while (i < map->x)
	{
		free(piece->tab[i]);
		free(map->tab[i++]);
	}
	free(piece->tab);
	free(piece);
	free(map->tab);
	free(map);
}

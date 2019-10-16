/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:35:00 by auguyon           #+#    #+#             */
/*   Updated: 2019/10/13 17:24:38 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdio.h>

void	initialize(t_piece *piece, t_map *map, char *line, int ac)
{
	int i;

	i = 0;
	if (ac != 1 || read(0, line, 33) == -1 || (line[0] != '$'
		&& line[1] != '$' && line[2] != '$'))
		return (free_all(line, piece, map, 1));
	printf("{%s}\n", line);
	map->c = line[10] == '1' ? 'O' : 'X';
	piece->c = line[10] == '1' ? 'X' : 'O';
	read(0, line, 8);
	ft_bzero(line, 50);
	while (read(0, line + i, 1) && ft_isdigit(line[i]))
		i++;
	map->x = ft_atoi(line);
	ft_bzero(line, 50);
	i = 0;
	while (read(0, line + i, 1) && ft_isdigit(line[i]))
		i++;
	map->y = ft_atoi(line);
	ft_bzero(line, 50);
}

void	reset(t_piece *piece, t_map *map)
{
	int i;

	i = 0;
	while (i < map->x)
		ft_bzero(map->map[i++], map->y + 1);
	i = 0;
	while (i < map->x)
		ft_bzero(piece->piece[i++], map->y + 1);
}

void	prt_pos(int best_x, int best_y)
{
	ft_putnbr(best_x);
	write(1, " ", 1);
	ft_putnbr(best_y);
	write(1, "\n", 1);
}

void	free_all(char *line, t_piece *piece, t_map *map, short code)
{
	int i;

	i = 0;
	free(line);
	if (code == 1)
	{
		free(piece);
		free(map);
		write(1, "Error\n", 6);
		exit(0);
	}
	while (i < map->x)
	{
		free(piece->piece[i]);
		free(map->map[i]);
		i++;
	}
	free(piece->piece);
	free(piece);
	free(map->map);
	free(map);
}

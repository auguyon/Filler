/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 14:51:14 by ftrujill          #+#    #+#             */
/*   Updated: 2019/10/03 19:55:28 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	prt_pos(int best_x, int best_y)
{
	ft_putnbr(best_x);
	write(1, " ", 1);
	ft_putnbr(best_y);
	write(1, "\n", 1);
}

void	size_piece(t_piece *piece)
{
	int i;
	int j;

	i = 0;
	piece->x_max = 0;
	piece->x_min = piece->x - 1;
	piece->y_max = 0;
	piece->y_min = piece->y - 1;
	while (i < piece->x)
	{
		j = 0;
		while (j < piece->y)
		{
			if (piece->piece[i][j] == '*')
			{
				piece->x_min = ft_min_int(piece->x_min, i);
				piece->x_max = ft_max_int(piece->x_max, i);
				piece->y_min = ft_min_int(piece->y_min, j);
				piece->y_max = ft_max_int(piece->y_max, j);
			}
			j++;
		}
		i++;
	}
}

int		valid_pos(t_map *map, t_piece *piece, int x, int y)
{
	int i;
	int j;
	int r;

	if (!(x + piece->x_min >= 0 && x + piece->x_max < map->x
		&& y + piece->y_min >= 0 && y + piece->y_max < map->y))
		return (0);
	r = 0;
	i = piece->x_min - 1;
	while (++i <= piece->x_max)
	{
		j = piece->y_min - 1;
		while (++j <= piece->y_max)
		{
			if (piece->piece[i][j] != '.')
			{
				if (piece->piece[i][j] == '*' && map->map[x + i][y + j] == map->c)
					r++;
				if (r > 1 || (piece->piece[i][j] == '*' &&
					map->map[x + i][y + j] == piece->c))
					return (0);
			}
		}
	}
	return (r);
}

int		ngbs(t_map *map, int i, int j)
{
	int x;
	int y;
	int nb;

	nb = 0;
	x = (i > 0 ? i - 1 : 0);
	while (x < map->x && x <= i + 1)
	{
		y = (j > 0 ? j - 1 : 0);
		while (y < map->y && y <= j + 1)
		{
			if (map->map[x][y] == '.')
				nb++;
			y++;
		}
		x++;
	}
	return (nb);
}

int		distance(t_map *map, t_piece *piece, int x, int y)
{
	int i;
	int j;
	int min;
	int nb;

	i = 0;
	nb = 0;
	min = 0;
	while (i < map->x)
	{
		j = 0;
		while (j < map->y)
		{
			nb = ngbs(map, i, j);
			if (map->map[i][j] == piece->c && nb > 0)
				min += nb * (ft_abs(x - i) + ft_abs(y - j));
			j++;
		}
		i++;
	}
	return (min);
}

int		filler(t_piece *piece, t_map *map, int best_x, int best_y)
{
	int x;
	int y;
	int min;

	size_piece(piece);
	min = -1;
	x = -map->x;
	while (++x < map->x)
	{
		y = -map->y;
		while (++y < map->y)
		{
			if (valid_pos(map, piece, x, y))
			{
				if (min < 0 || distance(map, piece, x, y) <= min)
				{
					best_x = x;
					best_y = y;
					min = distance(map, piece, x, y);
				}
			}
		}
	}
	prt_pos(best_x, best_y);
	return (best_x != -map->x ? 1 : 0);
}

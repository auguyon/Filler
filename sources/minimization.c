/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:35:00 by auguyon           #+#    #+#             */
/*   Updated: 2019/10/13 17:07:50 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	min_piece(t_piece *piece)
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
				piece->x_min = ft_min(piece->x_min, i);
				piece->x_max = ft_max(piece->x_max, i);
				piece->y_min = ft_min(piece->y_min, j);
				piece->y_max = ft_max(piece->y_max, j);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	valid_pos(t_map *map, t_piece *p, int x, int y)
{
	int i;
	int j;
	int r;

	if (!(x + p->x_min >= 0 && x + p->x_max < map->x
		&& y + p->y_min >= 0 && y + p->y_max < map->y))
		return (0);
	r = 0;
	i = p->x_min - 1;
	while (++i <= p->x_max)
	{
		j = p->y_min - 1;
		while (++j <= p->y_max)
		{
			if (p->piece[i][j] != '.')
			{
				if (p->piece[i][j] == '*' && map->map[x + i][y + j] == map->c)
					r++;
				if (r > 1 || (p->piece[i][j] == '*' &&
					map->map[x + i][y + j] == p->c))
					return (0);
			}
		}
	}
	return (r);
}

static int	ngbs(t_map *map, int i, int j)
{
	int x;
	int y;
	int nb;

	nb = 0;
	x = i > 0 ? i - 1 : 0;
	while (x < map->x && x <= i + 1)
	{
		y = j > 0 ? j - 1 : 0;
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

static int	distance(t_map *map, t_piece *piece, int x, int y)
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

int			write_pos(t_map *map, t_piece *piece, int best_x, int best_y)
{
	int x;
	int y;
	int min;

	min_piece(piece);
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

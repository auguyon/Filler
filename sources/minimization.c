/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:35:00 by auguyon           #+#    #+#             */
/*   Updated: 2019/03/16 17:19:23 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "../libft/libft.h"

void	min_piece(t_tab *piece)
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
			if (piece->tab[i][j] == '*')
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

int		valid_pos(t_tab *map, t_tab *piece, int x, int y)
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
			if (piece->tab[i][j] != '.')
			{
				if (piece->tab[i][j] == '*' && map->tab[x + i][y + j] == map->c)
					r++;
				if (r > 1 || (piece->tab[i][j] == '*' &&
					map->tab[x + i][y + j] == piece->c))
					return (0);
			}
		}
	}
	return (r);
}

int		ngbs(t_tab *map, int i, int j)
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
			if (map->tab[x][y] == '.')
				nb++;
			y++;
		}
		x++;
	}
	return (nb);
}

int		distance(t_tab *map, t_tab *piece, int x, int y)
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
			if (map->tab[i][j] == piece->c && nb > 0)
				min += nb * (ft_abs_int(x - i) + ft_abs_int(y - j));
			j++;
		}
		i++;
	}
	return (min);
}

int		write_pos(t_tab *map, t_tab *piece, int best_x, int best_y)
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

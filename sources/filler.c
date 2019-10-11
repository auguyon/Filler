/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:35:00 by auguyon           #+#    #+#             */
/*   Updated: 2019/03/16 17:19:23 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include "../libft/libft.h"

int		copy_piece_2(t_tab *piece)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	while (++i < piece->x)
	{
		j = 0;
		while (read(0, &c, 1) && j < piece->y)
			if (c == '.' || c == '*')
				piece->tab[i][j++] = c;
		piece->tab[i][j] = '\n';
	}
	return (1);
}

int		copy_piece(char *line, t_tab *piece)
{
	int i;

	ft_memset(line, 0, 50);
	read(0, line, 1);
	while (!ft_isdigit(*line))
		read(0, line, 1);
	i = 1;
	while (read(0, line + i, 1) && ft_isdigit(line[i]))
		i++;
	piece->x = ft_atoi(line);
	ft_memset(line, 0, 50);
	read(0, line, 1);
	while (!ft_isdigit(*line))
		read(0, line, 1);
	i = 1;
	while (read(0, line + i, 1) && ft_isdigit(line[i]))
		i++;
	piece->y = ft_atoi(line);
	return (copy_piece_2(piece));
}

int		copy_map(t_tab *map)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < map->x)
	{
		j = 0;
		while (read(0, &c, 1) && j < map->y)
		{
			if (c == '.' || c == 'O' || c == 'X')
			{
				map->tab[i][j] = c;
				j++;
			}
		}
		map->tab[i][j] = '\n';
		i++;
	}
	return (1);
}

int		filler(char *line, t_tab *piece, t_tab *map)
{
	int		i;
	char	c;

	copy_piece(line, piece);
	c = write_pos(map, piece, -map->x, -map->y);
	while (c)
	{
		i = -1;
		while (++i < 2)
		{
			read(0, line, 1);
			while (*line != '\n')
				read(0, line, 1);
		}
		ft_memset(line, 0, 50);
		reset_map(map);
		copy_map(map);
		reset_piece(piece, map);
		copy_piece(line, piece);
		c = write_pos(map, piece, -map->x, -map->y);
	}
	free_all(line, piece, map);
	return (0);
}

int		main(void)
{
	t_tab	*map;
	t_tab	*piece;
	char	*line;
	int		i;

	if (!(map = (t_tab*)malloc(sizeof(t_tab))) ||
		!(piece = (t_tab*)malloc(sizeof(t_tab))) ||
		!(line = (char*)ft_memalloc(50)))
		return (0);
	initialize(line, piece, map);
	if (!(map->tab = (char**)malloc(sizeof(char*) * (map->x + 1))) ||
		!(piece->tab = (char**)malloc(sizeof(char*) * (map->x + 1))))
		return (0);
	i = -1;
	while (++i < map->x)
		if (!(map->tab[i] = (char*)ft_memalloc(map->y + 1)) ||
			!(piece->tab[i] = (char*)ft_memalloc(map->y + 1)))
			return (0);
	ft_memset(line, 0, 50);
	read(0, line, map->y + 6);
	reset_map(map);
	copy_map(map);
	reset_piece(piece, map);
	return (filler(line, piece, map));
}

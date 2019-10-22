/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:35:00 by auguyon           #+#    #+#             */
/*   Updated: 2019/10/13 17:06:39 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	copy_piece_2(t_piece *piece)
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
				piece->piece[i][j++] = c;
		piece->piece[i][j] = '\n';
	}
}

static void	copy_piece(char *line, t_piece *piece)
{
	int i;

	read(0, line, 1);
	while (!ft_isdigit(*line))
		read(0, line, 1);
	i = 1;
	while (read(0, line + i, 1) && ft_isdigit(line[i]))
		i++;
	piece->x = ft_atoi(line);
	ft_bzero(line, 50);
	read(0, line, 1);
	while (!ft_isdigit(*line))
		read(0, line, 1);
	i = 1;
	while (read(0, line + i, 1) && ft_isdigit(line[i]))
		i++;
	piece->y = ft_atoi(line);
	copy_piece_2(piece);
}

static void	copy_map(t_map *map)
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
				map->map[i][j] = c;
				j++;
			}
		}
		map->map[i][j] = '\n';
		i++;
	}
}

static void	filler(char *line, t_piece *piece, t_map *map)
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
		ft_bzero(line, 50);
		reset(piece, map);
		copy_map(map);
		copy_piece(line, piece);
		c = write_pos(map, piece, -map->x, -map->y);
	}
}

int			main(int ac, char **av)
{
	t_map	*map;
	t_piece	*piece;
	char	*line;
	int		i;

	i = -1;
	(void)av;
	if (!(map = (t_map*)malloc(sizeof(t_map)))
		|| !(piece = (t_piece*)malloc(sizeof(t_piece)))
			|| !(line = (char*)ft_memalloc(50)))
		exit(0);
	initialize(piece, map, line, ac);
	if (!(map->map = (char**)malloc(sizeof(char*) * (map->x + 1)))
		|| !(piece->piece = (char**)malloc(sizeof(char*) * (map->x + 1))))
		exit(0);
	while (++i < map->x)
		if (!(map->map[i] = (char*)ft_memalloc(map->y + 1))
			|| !(piece->piece[i] = (char*)ft_memalloc(map->y + 1)))
			exit(0);
	read(0, line, map->y + 6);
	reset(piece, map);
	copy_map(map);
	filler(line, piece, map);
	free_all(line, piece, map, 0);
	return (1);
}

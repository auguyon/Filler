/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:49:49 by auguyon           #+#    #+#             */
/*   Updated: 2019/10/04 19:36:45 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdio.h>

void	fd_to_tab(int fd, t_map *map)
{
	char *line;
    int i;

	i = 0;
	if (!(map->map = (char**)malloc(sizeof(char*) * (map->x + 3))))
		exit(0);
	while(get_next_line(fd, &line))
	{
		if ((line[0] == 'P' && line[1] == 'l') || line[0] == ' ')
			free(line);
		else
		{
			map->map[i] = ft_strdup(line);
			free(line);
			i++;
		}
	}
	map->map[i] = NULL;
}

int		find_format(t_piece *piece, t_map *map)
{
	int i;
	int j;
	int max;

	i = map->x;
	j = 5;
	while (map->map[i])
	{
		if (ft_strstr(map->map[i], "Piece"))
		{
			piece->x = ft_atoi(map->map[i] + j);
			while (map->map[i][j] != ':')
				j++;
			max = j;
			j--;
			while(ft_isdigit(map->map[i][j]))
				j--;
			piece->y = ft_atoi(map->map[i] + j);
			free(map->map[i]);
			map->map[i] = NULL;
			break;
		}
		i++;
	}
	return (i + 1);
}

void	copy_piece(t_piece *piece, t_map *map)
{
	int i;
	int j;

	j = 0;
	i = find_format(piece, map);
	if (!(piece->piece = (char**)malloc(sizeof(char*) * (piece->x + 1))))
		exit(0);
	while (j < piece->x)
	{
		piece->piece[j++] = ft_strdup(map->map[i]);
		free(map->map[i]);
		i++;
	}
	piece->piece[j] = NULL;
}

void	free_map(t_piece *piece, t_map *map)
{
	int i;

	i = 0;
	while (map->map[i])
		free(map->map[i++]);
	free(map->map[i]);
	i = 0;
	while (piece->piece[i])
		free(piece->piece[i++]);
	free(piece->piece[i]);
}

void	initialize(t_piece *piece, t_map *map)
{
	int i;

	i = 8;
	map->c = (map->info[0][10] == '1' ? 'O' : 'X');
	piece->c = (map->c == 'X' ? 'O' : 'X');
	map->x = ft_atoi(map->info[3] + 8);
	while (ft_isdigit(map->info[3][i]))
		i++;
	map->y = ft_atoi(map->info[3] + (i + 1));
}

char	**take_info(int fd)
{
	char *line;
	char **tmp;
    int i;

	i = 0;
	if (!(tmp = (char**)malloc(sizeof(*tmp) * 5)))
		exit(0);
	while(i < 4 && get_next_line(fd, &line))
	{
		tmp[i++] = ft_strdup(line);
		free(line);
	}
	tmp[4] = NULL;
	return (tmp);
}

int		main(int ac, char **av)
{
	t_map	*map;
	t_piece	*piece;
	int 	fd;
	int 	r;

	r = 1;
	if (!(map = (t_map*)malloc(sizeof(t_map))) || !(piece = (t_piece*)malloc(sizeof(t_piece))))
		exit(0);
	fd = open(av[1], O_RDONLY);
	// fd = 0;
	map->info = take_info(fd);
	initialize(piece, map);
	while (r)
	{
		fd_to_tab(fd, map); // remplacer fd par zero
		copy_piece(piece, map);
		r = filler(piece, map, 0, 0);
		free_map(piece, map);
	}
	free(map);
	free(piece);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_generator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:35:00 by auguyon           #+#    #+#             */
/*   Updated: 2019/03/16 17:19:23 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "../libft/inc/libft.h"

int		print_usage(void)
{
	printf("The generator takes none or exactly three arguments as input "
		"corresponding to the length (4 to 50), width (4 to 100) and name of "
		"the map. If the numeric values do not belong to this range they are "
		"automatically adjusted.\n");
	return (0);
}

int		rand_range(int lower, int upper)
{
	return (lower > upper ? 0 : (rand() % (upper - lower + 1) + lower));
}

void	random_positions(int x, int y, int p[4])
{
	p[0] = rand_range(1, x);
	p[1] = rand_range(1, y);
	p[2] = rand_range(1, x);
	p[3] = p[1];
	while (p[3] == p[1])
		p[3] = rand_range(1, y);
}

void	create_map(int x, int y, const char *name)
{
	int p[4];
	int i;
	int j;
	int fd;

	if ((fd = creat(name, 00444)) < 0)
		return ;
	random_positions(x, y, p);
	i = 0;
	while (i++ < x)
	{
		j = 0;
		while (j++ < y)
		{
			if (i == p[0] && j == p[1])
				write(fd, "O", 1);
			else if (i == p[2] && j == p[3])
				write(fd, "X", 1);
			else
				write(fd, ".", 1);
		}
		write(fd, "\n", 1);
	}
	close(fd);
}

int		main(int argc, char **argv)
{
	int	x;
	int	y;

	srand(time(0));
	if (argc == 1)
	{
		create_map(rand_range(4, 50), rand_range(4, 100), "map");
		return (0);
	}
	if (argc != 4)
		return (print_usage());
	x = ft_min(ft_atoi(argv[1]), 50);
	y = ft_min(ft_atoi(argv[2]), 100);
	create_map(ft_max(4, x), ft_max(4, y), argv[3]);
	return (1);
}

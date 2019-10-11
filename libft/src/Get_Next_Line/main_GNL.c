/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_GNL.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:15:41 by auguyon           #+#    #+#             */
/*   Updated: 2019/10/02 18:29:24 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
char	**fd_to_tab(int fd)
{
	char *line;
    char **tmp;
	char **tab;
    int i;

	i = 0;
	if (!(tmp = (char**)malloc(sizeof(*tmp) * 100000)))
		exit(0);
	while(get_next_line(fd, &line))
		tmp[i++] = line;
	tmp[i] = NULL;
	if (!(tab = (char**)malloc(sizeof(*tab) * i)))
		exit(0);
	i = 0;
	while (tmp[i])
	{
		tab[i] = tmp[i];
		i++;
	}
	tab[i] = NULL;
	free(tmp);
	return (tab);
}

int		main(int ac, char **av)
{
    int fd;
	char **tab;

	(void)ac;
	fd = open(av[1], O_RDONLY);
	tab = ft_to_tab(fd);
	fd = 0;
	while (tab[fd])
		printf("%s\n", tab[fd++]);
	return (0);
}
*/

int	main(int argc, char ** argv)
{
	int fd;
	char *line;

	(void)argc;
	fd = open(argv[1], O_RDONLY);
	while(get_next_line(fd, &line))
	{
		ft_putendl(line);
		free(line);
	}
	return (0);
}

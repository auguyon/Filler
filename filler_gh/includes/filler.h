/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftrujill <ftrujill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 22:27:42 by ftrujill          #+#    #+#             */
/*   Updated: 2019/07/14 20:56:59 by ftrujill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/inc/libft.h"

typedef struct	s_piece
{
	char		c;
	int			x;
	int			y;
	int			x_min;
	int			x_max;
	int			y_min;
	int			y_max;
	char		**piece;
}				t_piece;

typedef struct	s_map
{
	char		c;
	int			x;
	int			y;
	char		**map;
}				t_map;

void			initialize(t_piece *piece, t_map *map, char *line, int ac);
void			reset(t_piece *piece, t_map *map);
int				write_pos(t_map *map, t_piece *piece, int best_x, int best_y);
void			prt_pos(int best_x, int best_y);
void			free_all(char *line, t_piece *piece, t_map *map, short code);

#endif

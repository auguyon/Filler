/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 22:27:42 by ftrujill          #+#    #+#             */
/*   Updated: 2019/10/04 16:19:21 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>

# include "Get_Next_line/get_next_line.h"

typedef struct	s_map
{
	char		**map;
	char		**info;
	int			x;
	int			y;
	char		c;
}				t_map;

typedef struct	s_piece
{
	char		**piece;
	int			x_min;
	int			x_max;
	int			y_min;
	int			y_max;
	int 		x;
	int 		y;
	char		c;
}				t_piece;

void			initialize(t_piece *piece, t_map *map);
void			reset_map(t_map *map);
void			reset_piece(t_piece *piece, t_map *map);
int				write_pos(t_map *map, t_piece *piece, int best_x, int best_y);
void			prt_pos(int best_x, int best_y);
void			free_all(t_piece *piece, t_map *map);
int				filler(t_piece *piece, t_map *map, int best_x, int best_y);

#endif

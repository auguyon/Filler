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

typedef struct	s_tab
{
	char		c;
	int			x;
	int			y;
	int			x_min;
	int			x_max;
	int			y_min;
	int			y_max;
	char		**tab;
}				t_tab;

void			initialize(char *line, t_tab *piece, t_tab *map);
void			reset_map(t_tab *map);
void			reset_piece(t_tab *piece, t_tab *map);
int				write_pos(t_tab *map, t_tab *piece, int best_x, int best_y);
void			prt_pos(int best_x, int best_y);
void			free_all(char *line, t_tab *piece, t_tab *map);

#endif

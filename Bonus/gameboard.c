/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameboard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <auguyon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 17:35:00 by auguyon           #+#    #+#             */
/*   Updated: 2019/03/16 17:19:23 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ncurses.h>
#include "libft/libft.h"

void    create_board(int l, int w, WINDOW **board)
{
    int i;
    int j;

    i = 0;
    while (i < l * w)
    {
        board[i] = newwin(3, 6, (LINES - l * 3) / 2 + 3 * (i / w),
            (COLS - 6 * w) / 2 + 6 * (i % w));
        box(board[i], 0, 0);
        wrefresh(board[i]);
        i++;
    }
}

void    filler_on_board(int l, int w, WINDOW **board)
{
    int     i;
    int     j;
    char    *line;

    while(get_next_line(0, &line))
    {
        if (!ft_isdigit(*line))
            free(line);
        else
        {
            i = 0;
            while (i < l)
            {
                j = 0;
                while (line[j + 4])
                {
                    if (line[j + 4] == 'o' || line[j + 4] == 'O')
                    {       
                        init_pair(3, COLOR_RED, COLOR_BLACK);
                        wattron(board[i * w + j], COLOR_PAIR(3));
                        box(board[i * w + j], 0, 0);
                        mvwprintw(board[i * w + j], 1, 1, "  O ");
                        wattroff(board[i * w + j], COLOR_PAIR(3));
                    }
                    else if (line[j + 4] == 'x' || line[j + 4] == 'X')
                    {                               
                        init_pair(2, COLOR_BLUE, COLOR_BLACK);
                        wattron(board[i * w + j], COLOR_PAIR(2));
                        box(board[i * w + j], 0, 0);
                        mvwprintw(board[i * w + j], 1, 1, "  X ");
                        wattroff(board[i * w + j], COLOR_PAIR(2));
                    }
                    wrefresh(board[i * w + j]);
                    j++;
                }
                i++;
                free(line);
                get_next_line(0, &line);
                if (!line || !*line)
                    break;
            }
            free(line);
        }
    }
}

int     main(int argc, char **argv)
{
    int     i;
    int     l;
    int     w;
    char    *line;
    WINDOW  **board;
    char c;

    initscr();
    noecho();
    cbreak();
    refresh();
    start_color();
    scrollok(stdscr,TRUE);
    while(get_next_line(0, &line) && *line != 'P')
        free(line);
    i = 0;
    while (line[i] != ' ')
        i++;
    l = ft_atoi(line + i++ + 1);
        while (line[i] != ' ')
        i++;
    w = ft_atoi(line + i + 1);
    free(line);
    board = (WINDOW**)malloc(sizeof(WINDOW*) * w * l);
    create_board(l, w, board);
    filler_on_board(l, w, board);
    sleep(5);
    endwin();
    free(board);
    return(0);
}


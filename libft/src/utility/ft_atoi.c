/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 15:28:46 by auguyon           #+#    #+#             */
/*   Updated: 2019/01/21 10:37:45 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	int		n;
	int		r;

	n = 0;
	r = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
		n = 1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		r = r * 10 + (*str - '0');
		str++;
	}
	if (r == 0)
		r = 1;
	return (n == 1 ? -r : r);
}

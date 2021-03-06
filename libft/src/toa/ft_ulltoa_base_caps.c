/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base_caps.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auguyon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 20:45:28 by auguyon           #+#    #+#             */
/*   Updated: 2019/07/04 20:45:31 by auguyon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toa.h"
#include <stdlib.h>

char	*ft_ulltoa_base_caps(unsigned long long n, unsigned int base)
{
	unsigned int		i;
	unsigned long long	nb;
	char				*str;

	nb = n;
	i = 1;
	while ((nb = (nb / base)) > 0)
		i++;
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	while (i > 0)
	{
		nb = (n % base);
		str[--i] = nb > 9 ? nb + 55 : nb + 48;
		n /= base;
	}
	return (str);
}

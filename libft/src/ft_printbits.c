/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printbits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 19:51:45 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/22 20:48:41 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		printbits(void *array, size_t size)
{
	uint8_t	*a;
	char	buf[9];
	size_t	i;

	buf[8] = ' ';
	i = 0;
	while (i++ < size)
	{
		a = (uint8_t *)array++;
		buf[0] = (char)((*a >> 7) & 0x1) ? '1' : '0';
		buf[1] = (char)((*a >> 6) & 0x1) ? '1' : '0';
		buf[2] = (char)((*a >> 5) & 0x1) ? '1' : '0';
		buf[3] = (char)((*a >> 4) & 0x1) ? '1' : '0';
		buf[4] = (char)((*a >> 3) & 0x1) ? '1' : '0';
		buf[5] = (char)((*a >> 2) & 0x1) ? '1' : '0';
		buf[6] = (char)((*a >> 1) & 0x1) ? '1' : '0';
		buf[7] = (char)((*a >> 0) & 0x1) ? '1' : '0';
		write(1, buf, 9);
		if (i - 1 && (i - 1) % 8 == 0)
			write(1, "\n", 1);
	}
	write(1, "\n", 1);
}

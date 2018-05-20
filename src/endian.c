/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 12:55:14 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/20 12:55:19 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	swap_endian32(uint32_t a)
{
	t_32bitunion	u;

	u.v = a;
	return (((uint32_t)(u.p8[0]) << 24) |
			((uint32_t)(u.p8[1]) << 16) |
			((uint32_t)(u.p8[2]) << 8) |
			((uint32_t)(u.p8[3])));
}

uint64_t	swap_endian64(uint64_t a)
{
	t_64bitunion	u;

	u.v = a;
	return (((uint64_t)(u.p8[0]) << 56) |
			((uint64_t)(u.p8[1]) << 48) |
			((uint64_t)(u.p8[2]) << 40) |
			((uint64_t)(u.p8[3]) << 32) |
			((uint64_t)(u.p8[4]) << 24) |
			((uint64_t)(u.p8[5]) << 16) |
			((uint64_t)(u.p8[6]) << 8) |
			((uint64_t)(u.p8[7])));
}

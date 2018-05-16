/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_md5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:05:28 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/16 15:05:39 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	Handles the main initializing function calls
*/

void			init_md5(t_md5 *md5)
{
	md5->a = 0x67452301;
	md5->b = 0xefcdab89;
	md5->c = 0x98badcfe;
	md5->d = 0x10325476;
	init_md5_s_table(md5);
	init_md5_k_table1(md5);
	init_md5_k_table2(md5);
	init_md5_k_table3(md5);
}

/*
**	Cascading syntax results from following the 'norm' of writing 'good' code :P
*/

void			init_md5_s_table(t_md5 *md5)
{
	int	i;

	i = 0;
	while (i < 16)
		if ((md5->s[i++] = 7))
			if ((md5->s[i++] = 12))
				if ((md5->s[i++] = 17))
					md5->s[i++] = 22;
	while (i < 32)
		if ((md5->s[i++] = 5))
			if ((md5->s[i++] = 9))
				if ((md5->s[i++] = 15))
					md5->s[i++] = 20;
	while (i < 48)
		if ((md5->s[i++] = 4))
			if ((md5->s[i++] = 11))
				if ((md5->s[i++] = 16))
					md5->s[i++] = 23;
	while (i < 64)
		if ((md5->s[i++] = 6))
			if ((md5->s[i++] = 10))
				if ((md5->s[i++] = 15))
					md5->s[i++] = 21;
}

void			init_md5_k_table1(t_md5 *md5)
{
	md5->k[0] = 0xd76aa478;
	md5->k[1] = 0xe8c7b756;
	md5->k[2] = 0x242070db;
	md5->k[3] = 0xc1bdceee;
	md5->k[4] = 0xf57c0faf;
	md5->k[5] = 0x4787c62a;
	md5->k[6] = 0xa8304613;
	md5->k[7] = 0xfd469501;
	md5->k[8] = 0x698098d8;
	md5->k[9] = 0x8b44f7af;
	md5->k[10] = 0xffff5bb1;
	md5->k[11] = 0x895cd7be;
	md5->k[12] = 0x6b901122;
	md5->k[13] = 0xfd987193;
	md5->k[14] = 0xa679438e;
	md5->k[15] = 0x49b40821;
	md5->k[16] = 0xf61e2562;
	md5->k[17] = 0xc040b340;
	md5->k[18] = 0x265e5a51;
	md5->k[19] = 0xe9b6c7aa;
	md5->k[20] = 0xd62f105d;
	md5->k[21] = 0x02441453;
}

void			init_md5_k_table2(t_md5 *md5)
{
	md5->k[22] = 0xd8a1e681;
	md5->k[23] = 0xe7d3fbc8;
	md5->k[24] = 0x21e1cde6;
	md5->k[25] = 0xc33707d6;
	md5->k[26] = 0xf4d50d87;
	md5->k[27] = 0x455a14ed;
	md5->k[28] = 0xa9e3e905;
	md5->k[29] = 0xfcefa3f8;
	md5->k[30] = 0x676f02d9;
	md5->k[31] = 0x8d2a4c8a;
	md5->k[32] = 0xfffa3942;
	md5->k[33] = 0x8771f681;
	md5->k[34] = 0x6d9d6122;
	md5->k[35] = 0xfde5380c;
	md5->k[36] = 0xa4beea44;
	md5->k[37] = 0x4bdecfa9;
	md5->k[38] = 0xf6bb4b60;
	md5->k[39] = 0xbebfbc70;
	md5->k[40] = 0x289b7ec6;
	md5->k[41] = 0xeaa127fa;
	md5->k[42] = 0xd4ef3085;
	md5->k[43] = 0x04881d05;
}

void			init_md5_k_table3(t_md5 *md5)
{
	md5->k[44] = 0xd9d4d039;
	md5->k[45] = 0xe6db99e5;
	md5->k[46] = 0x1fa27cf8;
	md5->k[47] = 0xc4ac5665;
	md5->k[48] = 0xf4292244;
	md5->k[49] = 0x432aff97;
	md5->k[50] = 0xab9423a7;
	md5->k[51] = 0xfc93a039;
	md5->k[52] = 0x655b59c3;
	md5->k[53] = 0x8f0ccc92;
	md5->k[54] = 0xffeff47d;
	md5->k[55] = 0x85845dd1;
	md5->k[56] = 0x6fa87e4f;
	md5->k[57] = 0xfe2ce6e0;
	md5->k[58] = 0xa3014314;
	md5->k[59] = 0x4e0811a1;
	md5->k[60] = 0xf7537e82;
	md5->k[61] = 0xbd3af235;
	md5->k[62] = 0x2ad7d2bb;
	md5->k[63] = 0xeb86d391;
}

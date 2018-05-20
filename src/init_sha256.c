/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sha256.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 18:11:53 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/19 18:11:54 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			init_sha256(t_sha256 *sha)
{
	sha->h0 = TBE(0x6a09e667);
	sha->h1 = TBE(0xbb67ae85);
	sha->h2 = TBE(0x3c6ef372);
	sha->h3 = TBE(0xa54ff53a);
	sha->h4 = TBE(0x510e527f);
	sha->h5 = TBE(0x9b05688c);
	sha->h6 = TBE(0x1f83d9ab);
	sha->h7 = TBE(0x5be0cd19);
	init_sha256_k_table1(sha);
	init_sha256_k_table2(sha);
	init_sha256_k_table3(sha);
}

void			init_sha256_k_table1(t_sha256 *sha)
{
	sha->k[0] = TBE(0x428a2f98);
	sha->k[1] = TBE(0x71374491);
	sha->k[2] = TBE(0xb5c0fbcf);
	sha->k[3] = TBE(0xe9b5dba5);
	sha->k[4] = TBE(0x3956c25b);
	sha->k[5] = TBE(0x59f111f1);
	sha->k[6] = TBE(0x923f82a4);
	sha->k[7] = TBE(0xab1c5ed5);
	sha->k[8] = TBE(0xd807aa98);
	sha->k[9] = TBE(0x12835b01);
	sha->k[10] = TBE(0x243185be);
	sha->k[11] = TBE(0x550c7dc3);
	sha->k[12] = TBE(0x72be5d74);
	sha->k[13] = TBE(0x80deb1fe);
	sha->k[14] = TBE(0x9bdc06a7);
	sha->k[15] = TBE(0xc19bf174);
	sha->k[16] = TBE(0xe49b69c1);
	sha->k[17] = TBE(0xefbe4786);
	sha->k[18] = TBE(0x0fc19dc6);
	sha->k[19] = TBE(0x240ca1cc);
	sha->k[20] = TBE(0x2de92c6f);
	sha->k[21] = TBE(0x4a7484aa);
}
void			init_sha256_k_table2(t_sha256 *sha)
{
	sha->k[22] = TBE(0x5cb0a9dc);
	sha->k[23] = TBE(0x76f988da);
	sha->k[24] = TBE(0x983e5152);
	sha->k[25] = TBE(0xa831c66d);
	sha->k[26] = TBE(0xb00327c8);
	sha->k[27] = TBE(0xbf597fc7);
	sha->k[28] = TBE(0xc6e00bf3);
	sha->k[29] = TBE(0xd5a79147);
	sha->k[30] = TBE(0x06ca6351);
	sha->k[31] = TBE(0x14292967);
	sha->k[32] = TBE(0x27b70a85);
	sha->k[33] = TBE(0x2e1b2138);
	sha->k[34] = TBE(0x4d2c6dfc);
	sha->k[35] = TBE(0x53380d13);
	sha->k[36] = TBE(0x650a7354);
	sha->k[37] = TBE(0x766a0abb);
	sha->k[38] = TBE(0x81c2c92e);
	sha->k[39] = TBE(0x92722c85);
	sha->k[40] = TBE(0xa2bfe8a1);
	sha->k[41] = TBE(0xa81a664b);
	sha->k[42] = TBE(0xc24b8b70);
	sha->k[43] = TBE(0xc76c51a3);
}

void			init_sha256_k_table3(t_sha256 *sha)
{
	sha->k[44] = TBE(0xd192e819);
	sha->k[45] = TBE(0xd6990624);
	sha->k[46] = TBE(0xf40e3585);
	sha->k[47] = TBE(0x106aa070);
	sha->k[48] = TBE(0x19a4c116);
	sha->k[49] = TBE(0x1e376c08);
	sha->k[50] = TBE(0x2748774c);
	sha->k[51] = TBE(0x34b0bcb5);
	sha->k[52] = TBE(0x391c0cb3);
	sha->k[53] = TBE(0x4ed8aa4a);
	sha->k[54] = TBE(0x5b9cca4f);
	sha->k[55] = TBE(0x682e6ff3);
	sha->k[56] = TBE(0x748f82ee);
	sha->k[57] = TBE(0x78a5636f);
	sha->k[58] = TBE(0x84c87814);
	sha->k[59] = TBE(0x8cc70208);
	sha->k[60] = TBE(0x90befffa);
	sha->k[61] = TBE(0xa4506ceb);
	sha->k[62] = TBE(0xbef9a3f7);
	sha->k[63] = TBE(0xc67178f2);
}

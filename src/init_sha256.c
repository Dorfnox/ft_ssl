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

void	init_sha256(t_sha256 *sha)
{
	sha->h0 = 0x6a09e667;
	sha->h1 = 0xbb67ae85;
	sha->h2 = 0x3c6ef372;
	sha->h3 = 0xa54ff53a;
	sha->h4 = 0x510e527f;
	sha->h5 = 0x9b05688c;
	sha->h6 = 0x1f83d9ab;
	sha->h7 = 0x5be0cd19;
	init_sha256_k_table1(sha);
	init_sha256_k_table2(sha);
	init_sha256_k_table3(sha);
}

void	init_sha256_k_table1(t_sha256 *sha)
{
	sha->k[0] = 0x428a2f98;
	sha->k[1] = 0x71374491;
	sha->k[2] = 0xb5c0fbcf;
	sha->k[3] = 0xe9b5dba5;
	sha->k[4] = 0x3956c25b;
	sha->k[5] = 0x59f111f1;
	sha->k[6] = 0x923f82a4;
	sha->k[7] = 0xab1c5ed5;
	sha->k[8] = 0xd807aa98;
	sha->k[9] = 0x12835b01;
	sha->k[10] = 0x243185be;
	sha->k[11] = 0x550c7dc3;
	sha->k[12] = 0x72be5d74;
	sha->k[13] = 0x80deb1fe;
	sha->k[14] = 0x9bdc06a7;
	sha->k[15] = 0xc19bf174;
	sha->k[16] = 0xe49b69c1;
	sha->k[17] = 0xefbe4786;
	sha->k[18] = 0x0fc19dc6;
	sha->k[19] = 0x240ca1cc;
	sha->k[20] = 0x2de92c6f;
	sha->k[21] = 0x4a7484aa;
}

void	init_sha256_k_table2(t_sha256 *sha)
{
	sha->k[22] = 0x5cb0a9dc;
	sha->k[23] = 0x76f988da;
	sha->k[24] = 0x983e5152;
	sha->k[25] = 0xa831c66d;
	sha->k[26] = 0xb00327c8;
	sha->k[27] = 0xbf597fc7;
	sha->k[28] = 0xc6e00bf3;
	sha->k[29] = 0xd5a79147;
	sha->k[30] = 0x06ca6351;
	sha->k[31] = 0x14292967;
	sha->k[32] = 0x27b70a85;
	sha->k[33] = 0x2e1b2138;
	sha->k[34] = 0x4d2c6dfc;
	sha->k[35] = 0x53380d13;
	sha->k[36] = 0x650a7354;
	sha->k[37] = 0x766a0abb;
	sha->k[38] = 0x81c2c92e;
	sha->k[39] = 0x92722c85;
	sha->k[40] = 0xa2bfe8a1;
	sha->k[41] = 0xa81a664b;
	sha->k[42] = 0xc24b8b70;
	sha->k[43] = 0xc76c51a3;
}

void	init_sha256_k_table3(t_sha256 *sha)
{
	sha->k[44] = 0xd192e819;
	sha->k[45] = 0xd6990624;
	sha->k[46] = 0xf40e3585;
	sha->k[47] = 0x106aa070;
	sha->k[48] = 0x19a4c116;
	sha->k[49] = 0x1e376c08;
	sha->k[50] = 0x2748774c;
	sha->k[51] = 0x34b0bcb5;
	sha->k[52] = 0x391c0cb3;
	sha->k[53] = 0x4ed8aa4a;
	sha->k[54] = 0x5b9cca4f;
	sha->k[55] = 0x682e6ff3;
	sha->k[56] = 0x748f82ee;
	sha->k[57] = 0x78a5636f;
	sha->k[58] = 0x84c87814;
	sha->k[59] = 0x8cc70208;
	sha->k[60] = 0x90befffa;
	sha->k[61] = 0xa4506ceb;
	sha->k[62] = 0xbef9a3f7;
	sha->k[63] = 0xc67178f2;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 16:30:58 by bpierce           #+#    #+#             */
/*   Updated: 2018/08/30 16:31:29 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	Main execution loop for des-cbc encryption (code-block chaining)
**	The main difference to ecb is that the IV plays a role. it is XOR'd with
**	each block - the result of this is then saved into iv for the next round.
*/

char		*execute_des_cbc(t_ssl *ssl, char *input, t_io_len *l)
{
	t_des		des;
	char		*output;

	init_des(&des);
	init_des_key(ssl, &des, &input, l);
	init_des_subkeys(&des, ssl->f.d);
	l->out_len = 0;
	if (ssl->f.d)
		output = des_cbc_dec(ssl, &des, input, l);
	else
		output = des_cbc_enc(ssl, &des, input, l);
	clean_des(&des);
	return (output);
}

/*
**	Main ENCRYPTION loop
*/

char		*des_cbc_enc(t_ssl *ssl, t_des *des, char *input, t_io_len *l)
{
	char		*output;
	uint64_t	message;
	uint64_t	encryption;
	uint64_t	iv;
	size_t		original_len;

	original_len = l->in_len;
	output = des_enc_out(ssl, &l->in_len);
	iv = hex_str_to_64bit_be(ssl->user_iv);
	while (l->out_len < l->in_len)
	{
		message = des_ecb_str_to_64bit(&input, &original_len) ^ iv;
		encryption = process_des_ecb(des, message);
		iv = encryption;
		insert_64bit_into_string(&output[l->out_len], encryption);
		l->out_len += 8;
	}
	output -= ssl->user_password ? 16 : 0;
	l->out_len += ssl->user_password ? 16 : 0;
	return (output);
}

/*
**	main DECRYPTION loop
*/

char		*des_cbc_dec(t_ssl *ssl, t_des *des, char *input, t_io_len *l)
{
	char		*output;
	uint64_t	iv;
	uint64_t	message;
	uint64_t	decryption;
	size_t		original_len;

	original_len = l->in_len;
	output = des_dec_out(ssl, &input, &l->in_len);
	iv = hex_str_to_64bit_be(ssl->user_iv);
	while (l->out_len < l->in_len)
	{
		message = des_ecb_str_to_64bit_dec(&input, &original_len);
		decryption = process_des_ecb(des, message) ^ iv;
		iv = message;
		insert_64bit_into_string(&output[l->out_len], decryption);
		l->out_len += 8;
	}
	return (output);
}

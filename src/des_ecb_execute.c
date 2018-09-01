/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 13:35:52 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/23 13:35:57 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	Main execution loop for des-ecb encryption (electronic cookbook)
**	Runs either the dec (decrypt) or enc (encrypt) des functions
*/

char	*execute_des_ecb(t_ssl *ssl, char *input, t_io_len *l)
{
	t_des		des;
	char		*output;

	init_des(&des);
	init_des_key(ssl, &des, &input, l);
	init_des_subkeys(&des, ssl->f.d);
	l->out_len = 0;
	if (ssl->f.d)
		output = des_ecb_dec(ssl, &des, input, l);
	else
		output = des_ecb_enc(ssl, &des, input, l);
	clean_des(&des);
	return (output);
}

/*
**	ENCRYPT
**	---------------------------------------------------------------------------
*/

char	*des_ecb_enc(t_ssl *ssl, t_des *des, char *in, t_io_len *l)
{
	char		*output;
	uint64_t	message;
	uint64_t	encryption;
	size_t		original_len;

	original_len = l->in_len;
	output = des_enc_out(ssl, &l->in_len);
	while (l->out_len < l->in_len)
	{
		message = des_ecb_str_to_64bit(&in, &original_len);
		encryption = process_des_ecb(des, message);
		insert_64bit_into_string(&output[l->out_len], encryption);
		l->out_len += 8;
	}
	output -= ssl->user_password ? 16 : 0;
	l->out_len += ssl->user_password ? 16 : 0;
	return (output);
}

/*
**	Allocates enough space for the:
**	- Salted__ (8 bytes)
**	- salt (usually 8 bytes)
**	- input len
**	- An extra 8 bytes in case the input length is a modulus of 8
*/

char	*des_enc_out(t_ssl *ssl, size_t *in_len)
{
	char		*output;
	int			len;
	uint64_t	salt;

	len = 8 + (PBKDF_SALT_SIZE / 2) + (*in_len) + 8;
	MAL_ERR((output = ft_strnew(len)), "Creating des output buffer");
	if (ssl->user_password)
	{
		salt = hex_str_to_64bit_le(ssl->user_salt);
		ft_memcpy(output, "Salted__", 8);
		ft_memcpy(&output[8], &salt, PBKDF_SALT_SIZE / 2);
		output += 16;
	}
	*in_len += (*in_len % 8) == 0 ? 8 : 0;
	return (output);
}

/*
**	DECRYPT
**	---------------------------------------------------------------------------
*/

char	*des_ecb_dec(t_ssl *ssl, t_des *des, char *in, t_io_len *l)
{
	char		*output;
	uint64_t	message;
	uint64_t	encryption;
	size_t		original_len;

	original_len = l->in_len;
	output = des_dec_out(ssl, &in, &l->in_len);
	while (l->out_len < l->in_len)
	{
		message = des_ecb_str_to_64bit_dec(&in, &original_len);
		encryption = process_des_ecb(des, message);
		insert_64bit_into_string(&output[l->out_len], encryption);
		l->out_len += 8;
	}
	return (output);
}

/*
**	Decryption output allocates just enough space as given in the input
**	If a password was given, then the salt has already been aquired from
**	the input - so move the input.
*/

char	*des_dec_out(t_ssl *ssl, char **in, size_t *in_len)
{
	char		*output;

	if (ssl->user_password)
	{
		*in_len -= 16;
		*in += 16;
	}
	MAL_ERR((output = ft_strnew(*in_len)), "Creating des output buffer");
	return (output);
}

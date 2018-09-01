/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 16:17:28 by bpierce           #+#    #+#             */
/*   Updated: 2018/06/07 19:29:11 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	Sets the key and iv (inside pbkdf) using the given password and salt.
**	First, combines pass and salt into 'input'.
**	Like openssl, it uses an MD5 hash with a pass of 1 Iteration!!!
**	It cuts the first 16 characters to be the key,
**	and the second 16 characters to be the iv.
**	That behaviour is mimicked here.
**
**	The output is set within the t_pbkdf struct given
*/

void		pbkdf2(t_pbkdf *p)
{
	char		*output;
	size_t		i;
	char		*input;
	t_io_len	len;

	len.in_len = p->pass_len + p->salt_len;
	MAL_ERR((input = ft_strnew(len.in_len)), "pbkdf2 input");
	ft_memcpy(input, p->password, p->pass_len);
	ft_memcpy(&input[p->pass_len], &p->salt, p->salt_len);
	i = -1;
	while (++i < p->num_of_iterations)
	{
		output = p->algo(NULL, input, &len);
		free(input);
		input = output;
		len.in_len = len.out_len;
	}
	p->key = ft_strndup(output, len.in_len / 2);
	p->iv = ft_strndup(&output[len.in_len / 2], len.in_len / 2);
	MAL_ERR(p->key && p->iv, "Failed to duplicate the key or iv");
	ft_strtoupper(&p->key);
	ft_strtoupper(&p->iv);
	free(output);
}

/*
**	A helper function that gets the salt either from user input
**	or if in decrypt mode:
**	grabs it from the input,
**	frees the old salt, // IGNORING FOR NOW!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
**	moves input,
**	and reduces the input length.
*/

uint64_t	acquire_salt(t_ssl *ssl, char **input, t_io_len *l)
{
	char		*check;
	uint64_t	salt;
	int			i;

	if (ssl->f.e)
		return (hex_str_to_64bit_le(ssl->user_salt));
	i = -1;
	check = "Salted__";
	if (l->in_len < 16)
		error_out("bad magic number\n");
	while (++i < (PBKDF_SALT_SIZE / 2))
		if ((*input)[i] != check[i])
			error_out("bad magic number\n");
	ft_memcpy(&salt, &((*input)[8]), PBKDF_SALT_SIZE / 2);
	return (salt);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:57:13 by bpierce           #+#    #+#             */
/*   Updated: 2018/03/30 20:57:13 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	Executes cipher functions
**	Output length will get set WITHIN the enc_func
**	Handles the -a base64 encoding/decoding
*/

void		execute_cipher(t_ssl *ssl)
{
	char		*input;
	char		*output;
	char		*b64_output;
	t_io_len	len;

	if (!(input = ssl->f.i ? input_from_file(ssl) : input_from_stdin(ssl)))
		return ;
	len.in_len = ssl->input_len;
	if (ssl->f.a && ssl->f.d)
	{
		b64_output = execute_base64(ssl, input, &len);
		len.in_len = len.out_len;
		free(input);
		input = b64_output;
	}
	output = ssl->enc_func(ssl, input, &len);
	if (ssl->f.a && ssl->f.e)
	{
		len.in_len = len.out_len;
		b64_output = execute_base64(ssl, output, &len);
		free(output);
		output = b64_output;
	}
	write_cipher(ssl, input, output, &len);
	clean_cipher(ssl);
}

/*
**	Writes to appropriate output and frees stuff
*/

void		write_cipher(t_ssl *ssl, char *in, char *out, t_io_len *len)
{
	if (!ssl->f.o)
		write(1, out, len->out_len);
	else
		writetofile(ssl->out_file, (uint8_t *)out, len->out_len);
	free(in);
	free(out);
}

void		clean_cipher(t_ssl *ssl)
{
	ft_strdel(&ssl->user_password);
	ft_strdel(&ssl->user_salt);
	ft_strdel(&ssl->user_key);
	ft_strdel(&ssl->user_iv);
}

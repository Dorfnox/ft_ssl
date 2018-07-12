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
**	executes message digest functions
*/

void		execute_cipher(t_ssl *ssl)
{
	char		*input;
	char		*output;
	t_io_len	len;

	input = ssl->f.i ? input_from_file(ssl) : input_from_stdin(ssl);
	if (!input)
		return ;
	len.in_len = ssl->input_len;
	output = ssl->enc_func(ssl, input, &len);
	if (!ssl->f.o)
		write(1, output, len.out_len);
	else
		writetofile(ssl->out_file, output, len.out_len);
	free(input);
	free(output);
	clean_cipher(ssl);
}

void		clean_cipher(t_ssl *ssl)
{
	ft_strdel(&ssl->user_password);
	ft_strdel(&ssl->user_salt);
	ft_strdel(&ssl->user_key);
	ft_strdel(&ssl->user_iv);
}

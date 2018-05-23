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
	char	*input;
	char	*output;

	input = ssl->f.i ? input_from_file(ssl) : input_from_stdin(ssl);
	if (!input)
		return ;
	output = ssl->enc_func(ssl, input);
	output_to_file_or_stdout(ssl, input, output);
	free(input);
	free(output);
	free(ssl->k.user_key);
}

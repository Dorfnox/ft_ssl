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
**	main function that handles whether to read from stdin, or from file
*/

void				execute_all(t_ssl *ssl)
{
	if (ssl->input_files)
		execute_from_input_files(ssl);
	else
		execute_from_stdin(ssl);
}

/*
**	A while loop iterates through each file, and calls the crypto algorithm
**	on that file's contents
*/

void				execute_from_input_files(t_ssl *ssl)
{
	char	*input;
	int		i;

	i = -1;
	while (ssl->input_files[++i])
	{
		input = getfilecontents(ssl->input_files[i]);
		if (!input)
		{
			write(1, NO_SUCH_FD_ERROR, ft_strlen(NO_SUCH_FD_ERROR));
			continue ;
		}
		ssl->filename = ssl->input_files[i];
		execute_general(ssl, input);
	}
}

/*
**	Reads from the standard input, and calls the crypto algorithm
**	on the input
*/

void				execute_from_stdin(t_ssl *ssl)
{
	char	*input;
	char	*buffer;
	int		i;

	buffer = ft_str256(0);
	input = ft_strnew(0);
	while ((i = read(0, buffer, 255)))
	{
		buffer[i] = 0;
		input = ft_strfjoin(&input, buffer);
	}
	execute_general(ssl, input);
}

/*
**	A General Function that helps with executing the input
*/

void				execute_general(t_ssl *ssl, char *input)
{
	char	*output;

	DB(input); // delete
	output = ssl->execute_func(ssl, input);
	display_output(ssl, output);
	free(input);
}

/*
**	Handles displaying the output to the terminal, or more in the future
*/

void				display_output(t_ssl *ssl, char *output)
{
	(void)ssl;
	write(1, output, ft_strlen(output));
	write(1, "\n", 1);
}


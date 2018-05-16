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
		ssl->filename = ssl->input_files[i];
		ssl->input_len = getfilecontents(ssl->filename, &input);
		if (!input)
		{
			write(1, NO_SUCH_FD_ERROR, ft_strlen(NO_SUCH_FD_ERROR));
			continue ;
		}
		execute_general(ssl, &input);
	}
}

/*
**	Reads from the standard input, and calls the crypto algorithm
**	on the input.
**
*/

void				execute_from_stdin(t_ssl *ssl)
{
	char	*input;
	char	*buffer[256];
	int		i;

	input = ft_strnew(0);
	while ((i = read(0, buffer, 255)))
	{
		if (i == -1)
			if (ssl_error("read error", "failed to read from stdin", 1))
				return ;
		buffer[i] = 0;
		if (!(input = ft_strfjoin(&input, (char *)buffer)))
			if (ssl_error("ft_strfjoin error", "execute_from_stdin fail", 1))
				return ;
		ssl->input_len += i;
	}
	execute_general(ssl, &input);
}

/*
**	A General Function that helps with executing the input
*/

void				execute_general(t_ssl *ssl, char **input)
{
	char	*output;

	DB(*input); // delete
	output = ssl->execute_func(ssl, input);
	display_output(ssl, output);
	ft_strdel(input);
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


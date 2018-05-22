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

void		execute_message_digest(t_ssl *ssl)
{
	if ((!ssl->input_files && !ssl->given_strings && ssl->f.p == 0) ||
		ssl->f.p == 1)
	{
		execute_general(ssl, input_from_stdin(ssl), STDIN_OUTPUT);
	}
	if (ssl->given_strings)
	{
		execute_given_strings(ssl);
	}
	if (ssl->input_files)
	{
		execute_input_files(ssl);
	}
}

/*
**	Loops through given strings, and calls execute_general for each string
*/

void		execute_given_strings(t_ssl *ssl)
{
	char	*contents;
	int		i;

	i = -1;
	while (ssl->given_strings[++i])
	{
		ssl->given_string = ssl->given_strings[i];
		contents = input_from_given_string(ssl);
		execute_general(ssl, contents, GIVEN_STRING_OUTPUT);
	}
}

/*
**	Loops through input files, and calls execute_general for each file content
*/

void		execute_input_files(t_ssl *ssl)
{
	char	*contents;
	int		i;

	i = -1;
	while (ssl->input_files[++i])
	{
		ssl->in_file = ssl->input_files[i];
		contents = input_from_file(ssl);
		execute_general(ssl, contents, FILENAME_OUTPUT);
	}
}

/*
**	A general Function that helps with executing the crypto algorithms
*/

void		execute_general(t_ssl *ssl, char *input, int display_type)
{
	char	*output;

	if (!input)
		return ;
	output = ssl->enc_func(ssl, input);
	if (display_type == STDIN_OUTPUT)
		output_stdin(ssl, input, output);
	else if (display_type == GIVEN_STRING_OUTPUT)
		output_given_string(ssl, input, output);
	else if (display_type == FILENAME_OUTPUT)
		output_filename(ssl, input, output);
	free(input);
	free(output);
}

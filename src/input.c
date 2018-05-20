/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:55:40 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/19 15:55:47 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	Reads from the standard input, and calls the crypto algorithm
**	on the input.
**
*/

char				*input_from_stdin(t_ssl *ssl)
{
	char	*input;
	char	*buffer[256];
	int		i;

	input = ft_strnew(0);
	ssl->input_len = 0;
	while ((i = read(0, buffer, 255)))
	{
		if (i == -1)
		{
			ssl_error("read error", "failed to read from stdin", 1);
			free(input);
			return (NULL);
		}
		buffer[i] = 0;
		if (!(input = ft_strfjoin(&input, (char *)buffer)))
		{
			ssl_error("ft_strfjoin error", "input_from_stdin fail", 1);
			free(input);
			return (NULL);
		}
		ssl->input_len += i;
	}
	return (input);
}

/*
**	Collects the files contents, sets input_len and returns the input
*/

char				*input_from_file(t_ssl *ssl)
{
	char	*input;

	ssl->input_len = getfilecontents(ssl->filename, &input);
	if (!input)
	{
		ft_pflite("%s: %s: %s: %s\n", "ft_ssl", ssl->cmd_name_lower, ssl->filename,
			"no such file or directory");
		return (NULL);
	}
	return (input);
}

/*
**	Performs a basic strdup and stores the length of the string
*/

char				*input_from_given_string(t_ssl *ssl)
{
	char	*input;
	int		i;

	i = -1;
	while (ssl->given_string[++i])
		;
	ssl->input_len = i;
	if (!(input = malloc(sizeof(char) * (ssl->input_len + 1))))
		return (NULL);
	while (i-- > 0)
		input[i] = ssl->given_string[i];
	input[ssl->input_len] = 0;
	return (input);
}
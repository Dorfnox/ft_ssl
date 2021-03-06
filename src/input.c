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
*/

char		*input_from_stdin(t_ssl *ssl)
{
	char	*input;
	char	*new_input;
	char	buffer[1024];
	int		ret;

	input = ft_strnew(0);
	ssl->input_len = 0;
	while ((ret = read(0, buffer, 1023)))
	{
		if (ret == -1)
		{
			ssl_error("read error", "failed to read from stdin", 1);
			free(input);
			return (NULL);
		}
		ssl->input_len += ret;
		MAL_ERR((new_input = ft_strnew(ssl->input_len)), "Gathering input");
		ft_memcpy(new_input, input, ssl->input_len - ret);
		ft_memcpy(&new_input[ssl->input_len - ret], buffer, ret);
		free(input);
		input = new_input;
	}
	return (input);
}

/*
**	Collects the files contents, sets input_len and returns the input
*/

char		*input_from_file(t_ssl *ssl)
{
	uint8_t	*input;

	ssl->input_len = getfilecontents(ssl->in_file, &input);
	if (!input)
	{
		ft_pflite("%s: %s: %s: %s\n",
			"ft_ssl",
			ssl->cmd_name_lower, ssl->in_file,
			"no such file or directory");
		return (NULL);
	}
	return ((char *)input);
}

/*
**	Performs a basic strdup and stores the length of the string
*/

char		*input_from_given_string(t_ssl *ssl)
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

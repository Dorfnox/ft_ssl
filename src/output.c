/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_output.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:14:17 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/19 15:14:24 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	Handles displaying the output to the terminal
**	Mostly for the Message Digest commands
*/

void	output_stdin(t_ssl *ssl, char *input, char *output)
{
	int len;

	if (ssl->f.p)
	{
		len = ft_strlen(input);
		write(1, input, len);
		if (len > 0 && input[len - 1] != '\n')
			write(1, "\n", 1);
	}
	write(1, output, ft_strlen(output));
	write(1, "\n", 1);
}

void	output_given_string(t_ssl *ssl, char *input, char *output)
{
	if (ssl->f.q)
		write(1, output, ft_strlen(output));
	else if (ssl->f.r)
		ft_pflite("%s \"%s\"", output, input);
	else
		ft_pflite("%s (\"%s\") = %s", ssl->cmd_name_upper, input, output);
	write(1, "\n", 1);
}

void	output_filename(t_ssl *ssl, char *input, char *output)
{
	(void)input;
	if (ssl->f.q)
		write(1, output, ft_strlen(output));
	else if (ssl->f.r)
		ft_pflite("%s %s", output, ssl->in_file);
	else
		ft_pflite("%s (%s) = %s", ssl->cmd_name_upper, ssl->in_file, output);
	write(1, "\n", 1);
}

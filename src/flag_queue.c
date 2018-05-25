/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 15:55:40 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/22 15:57:16 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	Flag handler moves av to the flag AFTER the last valid flag,
**	therefore, any extra flag handling can be done outside of the handler.
*/

unsigned int	flag_handler(t_ssl *ssl, char ***av)
{
	unsigned int	(*flag_function)(t_ssl *, char ***);

	if (isemptyq(ssl->flag_queue) || !av || !*av || !**av)
		return (1);
	while (**av)
	{
		flag_function = search_flag_queue(ssl->flag_queue->first, **av);
		if (!flag_function && CE_('-', ***av))
		{
			ssl->flag_error = FLAG_ERR2(**av);
			return (0);
		}
		else if (!flag_function || !flag_function(ssl, av))
			return (0);
		++(*av);
	}
	return (1);
}

/*
**	Connects the given flag with a function pointer to return from the
**	flag queue.
*/

void			*search_flag_queue(t_node *n, char *flag)
{
	if (SE_(flag, "-p"))
		return (search_for_flag(n, p_flag));
	else if (SE_(flag, "-q"))
		return (search_for_flag(n, q_flag));
	else if (SE_(flag, "-r"))
		return (search_for_flag(n, r_flag));
	else if (SE_(flag, "-s"))
		return (search_for_flag(n, s_flag));
	else if (SE_(flag, "-i"))
		return (search_for_flag(n, i_flag));
	else if (SE_(flag, "-o"))
		return (search_for_flag(n, o_flag));
	else if (SE_(flag, "-d"))
		return (search_for_flag(n, d_flag));
	else if (SE_(flag, "-e"))
		return (search_for_flag(n, e_flag));
	else if (SE_(flag, "-k"))
		return (search_for_flag(n, k_flag));
	return (NULL);
}

void			*search_for_flag(t_node *n, unsigned int (*f)(t_ssl *, char ***))
{
	while (n)
	{
		if (n->content == f)
			return (n->content);
		n = n->next;
	}
	return (NULL);
}

void			clean_flag_queue(t_ssl *ssl)
{
	while (!isemptyq(ssl->flag_queue))
		dequeue(ssl->flag_queue);
	ft_memdel((void **)&ssl->flag_queue);
}

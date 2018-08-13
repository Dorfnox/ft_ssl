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
**	Adds both the flag and flag function to the queue
*/

void			add_flag(t_queue **q, char *flag, void *flag_func)
{
	t_flag_queue	*q_item;

	if (!q || !flag || !flag_func)
		return ;
	*q = !*q ? initq() : *q;
	q_item = malloc(sizeof(t_flag_queue));
	if (!q_item)
	{
		ssl_error("Malloc error", "Failed to add flag", 0);
		return ;
	}
	q_item->flag = flag;
	q_item->flag_func = flag_func;
	enqueue(*q, q_item);
}

/*
**	Flag handler moves av to the flag AFTER the last valid flag,
**	therefore, any extra flag handling can be done outside of the handler.
*/

unsigned int	flag_handler(t_ssl *ssl, char ***av)
{
	unsigned int	(*flag_func)(t_ssl *, char ***);

	if (isemptyq(ssl->flag_queue) || !av || !*av || !**av)
		return (1);
	while (**av)
	{
		flag_func = search_flag_queue(ssl->flag_queue->first, **av);
		if (!flag_func && CE_('-', ***av))
		{
			ssl->flag_error = FLAG_ERR2(**av);
			clean_flag_queue(&ssl->flag_queue);
			return (0);
		}
		else if (!flag_func || !flag_func(ssl, av))
		{
			clean_flag_queue(&ssl->flag_queue);
			return (0);
		}
		++(*av);
	}
	clean_flag_queue(&ssl->flag_queue);
	return (1);
}

/*
**	Connects the given flag with a function pointer to return from the
**	flag queue.
*/

void			*search_flag_queue(t_node *n, char *flag)
{
	t_flag_queue	*q_item;

	while (n)
	{
		q_item = n->content;
		if (SE_(q_item->flag, flag))
			return ((void *)q_item->flag_func);
		n = n->next;
	}
	return (NULL);
}

/*
**	General cleanup of the flag queue
*/

void			clean_flag_queue(t_queue **q)
{
	while (!isemptyq(*q))
		free(dequeue(*q));
	ft_memdel((void **)q);
}

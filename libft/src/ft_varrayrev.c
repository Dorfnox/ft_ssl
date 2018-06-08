/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_varrayrev.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 19:08:09 by bpierce           #+#    #+#             */
/*   Updated: 2018/06/07 20:06:21 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Reverses the given array of pointers
*/

void	ft_varrayrev(void **array, int size_of_array)
{
	int		beg;
	void	*tmp;

	if (!array || !(*array) || size_of_array < 2)
		return ;
	beg = 0;
	--size_of_array;
	while (beg < size_of_array)
	{
		tmp = array[beg];
		array[beg] = array[size_of_array];
		array[size_of_array] = tmp;
		++beg;
		--size_of_array;
	}
}

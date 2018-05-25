/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 15:44:40 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/22 15:44:48 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int	k_flag(t_ssl *ssl, char ***av)
{
	if (ssl->f.k && (ssl->flag_error = FLAG_ERR4("-k")))
		return (0);
	++(*av);
	if (!**av)
	{
		ssl->flag_error = ft_str256(2, FLAG_ERR1("-k"), ERROR_HEX1);
		return (0);
	}
	ssl->user_key = get_key_from_user(**av);
	if (!ssl->user_key)
		return (0);
	// create_subkeys();
	return ((ssl->f.k = 1));
}

// t_byte		get_8_bit_key(uint8_t hex, uint8_t hex2)
// {
// 	char		*key;
// 	t_byte		b;
// 	uint8_t		i;

// 	key = "0123456789ABCDEF";
// 	b.byte = 0;
// 	i = 0;
// 	while (i < 16)
// 	{
// 		if (key[i] == hex)
// 			b.byte |= i << 4;
// 		if (key[i] == hex2)
// 			b.byte |= i;
// 		i++;
// 	}
// 	return (b);
// }

char		*get_key_from_user(char *given_key)
{
	char	*key;

	if (!(key = ft_strncpy(malloc(17), given_key, 16)))
		return (NULL);
	key[16] = '\0';
	ft_strtoupper(&key);
	while (does_not_contain_hex_characters_or_is_null(key))
	{
		ft_bzero(key, 17);
		readpassphrase(ERROR_HEX, key, 17, RPP_FORCEUPPER);
		ft_putstr("-------------------------------------------\n");
	}
	while (ft_strlen(key) < 16)
		if (!(key = ft_strfjoin(&key, key)))
			return (ft_putnull("Failed to increase key length"));
	if (!(key = ft_strfsub(&key, 0, 16)))
		return (ft_putnull("Failed to reduce key length"));
	return (key);
}

int			does_not_contain_hex_characters_or_is_null(char *key)
{
	char	*hex;
	int		i;
	int		strlen;

	if (!key || ((strlen = ft_strlen(key)) < 1))
		return (1);
	hex = "0123456789ABCDEF";
	i = -1;
	while (++i < strlen)
		if (!ft_strchr(hex, key[i]))
			return (1);
	return (0);
}

// void		create_subkeys(t_ssl *ssl)
// {
// 	b->k.b1 = get_8_bit_key(key[0], key[1]);
// 	b->k.b2 = get_8_bit_key(key[2], key[3]);
// 	b->k.b3 = get_8_bit_key(key[4], key[5]);
// 	b->k.b4 = get_8_bit_key(key[6], key[7]);
// 	b->k.b5 = get_8_bit_key(key[8], key[9]);
// 	b->k.b6 = get_8_bit_key(key[10], key[11]);
// 	b->k.b7 = get_8_bit_key(key[12], key[13]);
// 	b->k.b8 = get_8_bit_key(key[14], key[15]);
// 	// b->subkeys = get_subkeys(&b->k, NULL, 0);
// 	// b->subkeys = (CE_(b->enc_type, DES) && b->d) ?
// 	// 	(uint8_t **)ft_arrayrev((void **)b->subkeys) : b->subkeys;
// 	return (key);
// }
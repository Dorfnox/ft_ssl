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

#ifndef FT_SSL_MACROS_H
# define FT_SSL_MACROS_H

# define USAGE "usage: ft_ssl command [command opts] [command args]\n"

# define MESSAGE_DIGEST_COMMANDS "Message Digest commands:\nmd5\nsha256\n"
# define COMMANDS MESSAGE_DIGEST_COMMANDS
# define MAX_COMMAND_SIZE 32

# define VALID_MD5_FLAGS "-p\n-q\n-r\n-s\n"
# define VALID_SHA_256_FLAGS "-p\n-q\n-r\n-s\n"
# define FLAG_ERROR ft_str256(6, "unknown option: '", ssl.flag_error, \
		"'\nValid ", ssl.cmd_name_upper, " flags:\n", ssl.cmd_valid_flags)

# define NO_SUCH_FD_ERROR ft_str128(2, ssl->input_files[i], \
		": no such file or directory\n")

/*
**	MD5 Auxiliary Functions
*/

# define MD5_AUX_F1(x, y, z) ((x & y) | (~(x) & z))
# define MD5_AUX_F2(x, y, z) ((x & z) | (y & ~(z)))
# define MD5_AUX_F3(x, y, z) (x ^ y ^ z)
# define MD5_AUX_F4(x, y, z) (y ^ (x | ~(z)))

#endif

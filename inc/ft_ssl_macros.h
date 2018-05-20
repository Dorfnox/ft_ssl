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
# define VALID_SHA256_FLAGS "-p\n-q\n-r\n-s\n"

# define FLAG_ERR1 ft_str256(2, *(av - 1), ": requires an argument\n")

# define FE_2A "unknown option: '"
# define FE_2B *av
# define FE_2C "'\nValid "
# define FE_2D ssl->cmd_name_upper
# define FE_2E " flags:\n"
# define FE_2F ssl->cmd_valid_flags
# define FLAG_ERR2 ft_str256(6, FE_2A, FE_2B, FE_2C, FE_2D, FE_2E, FE_2F)

/*
**	Super Helpful Functions
*/

# define LEFT_ROTATE(a, b) (((a) << (b)) | ((a) >> (32 - (b))))
# define RIGHT_ROTATE(a, b) (((a) >> (b)) | ((a) << (32 - (b))))

/*
**	MD5 Auxiliary Functions
*/

# define MD5_F1(b, c, d) ((b & c) | ((~b) & d))
# define MD5_F2(b, c, d) ((d & b) | ((~d) & c))
# define MD5_F3(b, c, d) (b ^ c ^ d)
# define MD5_F4(b, c, d) (c ^ (b | (~d)))

/*
**	SHA256 Auxiliary Functions
*/

# define TBE_1(a) ((((uint64_t)(a)[0]) << 56) | (((uint64_t) (a)[1]) << 48))
# define TBE_2(a) ((((uint64_t)(a)[2]) << 40) | (((uint64_t) (a)[3]) << 32))
# define TBE_3(a) ((((uint64_t)(a)[4]) << 24) | (((uint64_t) (a)[5]) << 16))
# define TBE_4(a) ((((uint64_t)(a)[6]) << 8) | (((uint64_t) (a)[7]) << 0))
# define TO_BIG_ENDIAN64(a) (TBE_1(a) | TBE_2(a) | TBE_3(a) | TBE_4(a))
# define TBE(a) TO_BIG_ENDIAN64(a)

#endif

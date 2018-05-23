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

/*
**	Commands
**	----------------------------------------------------------------------------
*/

# define MDC_A "Message Digest Commands:\n"
# define MDC_B "md5\tsha256\tsha224\n\n"
# define MESSAGE_DIGEST_COMMANDS MDC_A MDC_B

# define CC_A "Cipher Commands:\n"
# define CC_B "base64\ndes-ecb\n"
# define CIPHER_COMMADS CC_A CC_B

# define COMMANDS MESSAGE_DIGEST_COMMANDS CIPHER_COMMADS
# define MAX_COMMAND_SIZE 32

# define COMMAND_ERROR ft_str256(2, ssl.flag_error, COMMANDS)

/*
**	Flags
**	----------------------------------------------------------------------------
*/

/*
**	Valid Message Digest Flags
*/

# define VALID_MD5_FLAGS "-p\n-q\n-r\n-s\n"
# define VALID_SHA256_FLAGS "-p\n-q\n-r\n-s\n"
# define VALID_SHA224_FLAGS "-p\n-q\n-r\n-s\n"

/*
**	Valid Cipher Flags
*/

# define VALID_BASE64_FLAGS "-d\n-e\n-i\n-o\n"
# define VALID_DES_FLAGS "-d\n-e\n-i\n-o\n-k\n"

/*
**	Flag Errors
*/

# define FLAG_ERROR ssl.flag_error

# define FE_0A "error: '"
# define FE_0B "' is an invalid command\n\n"
# define FLAG_ERR0(a) ft_str256(3, FE_0A, (a), FE_0B)

# define FLAG_ERR1(a) ft_str256(3, "flag '", (a), "' requires an argument\n")

# define FE_2A "unknown option: '"
# define FE_2B "'\nValid "
# define FE_2C ssl->cmd_name_upper
# define FE_2D " flags:\n"
# define FE_2E ssl->cmd_valid_flags
# define FLAG_ERR2(a) ft_str256(6, FE_2A, (a), FE_2B, FE_2C, FE_2D, FE_2E)

# define FE_3A "consolidate: flag '"
# define FE_3B **av
# define FE_3C "' cannot be used with flag'"
# define FLAG_ERR3(a) ft_str256(5, FE_3A, FE_3B, FE_3C, (a), "'\n")

# define FE_4A "consolidate: flag '"
# define FE_4B "' cannot be used twice\n"
# define FLAG_ERR4(a) ft_str256(3, FE_4A, (a), FE_4B)

/*
**	Key Errors
*/

# define ERROR_HEX1 "[32mDES encryption needs a 16-char HEX keycode.[0m\n"
# define ERROR_HEX2 "The [1;31monly[0m acceptable hex characters are:\n"
# define ERROR_HEX3 "[93m0123456789ABCDEFabcdef[0m\n"
# define ERROR_HEX4 "Use any of these characters [31m1 - 16 times.[0m\n"
# define ERROR_HEX5 "Enter a [92mnew hex key[0m: "
# define ERROR_HEX ERROR_HEX1 ERROR_HEX2 ERROR_HEX3 ERROR_HEX4 ERROR_HEX5

/*
**	Auxiliary functions
**	----------------------------------------------------------------------------
*/

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

#endif

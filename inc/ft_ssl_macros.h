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

/*
**	Global definitions
*/

# define USAGE "usage: ft_ssl command [command opts] [command args]\n"

# define PBKDF_SALT_SIZE 16
# define PBKDF_ALGO execute_sha256
# define PBKDF_SALT ssl->user_salt
# define PBKDF_PASSWORD ssl->user_password
# define PBKDF_PASSWORD_SIZE 32

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

# define FE_3A "flag '"
# define FE_3B "' cannot be used with flag'"
# define FLAG_ERR3(a, b) ft_str256(5, FE_3A, (a), FE_3B, (b), "'\n")

# define FE_4A "consolidate: flag '"
# define FE_4B "' cannot be used twice\n"
# define FLAG_ERR4(a) ft_str256(3, FE_4A, (a), FE_4B)

/*
**	Key Errors
*/

# define HEX_ERR1 "[32mDES encryption needs a 16-char HEX keycode.[0m\n"
# define HEX_ERR2 "The [1;31monly[0m acceptable hex characters are:\n"
# define HEX_ERR3 "[93m0123456789ABCDEFabcdef[0m\n"
# define HEX_ERR4 "Use any of these characters [31m1 - 16 times.[0m\n"
# define HEX_ERR5 "Enter a [92mnew hex key[0m: "
# define HEX_ERROR HEX_ERR1 HEX_ERR2 HEX_ERR3 HEX_ERR4 HEX_ERR5

/*
**	Password Errors
*/

# define PASSWORD_ERR1 "[32mA password is required.[0m\n"
# define PASSWORD_ERR2 "Enter a [92mnew password[0m: "
# define PASSWORD_ERROR PASSWORD_ERR1 PASSWORD_ERR2

/*
**	Salt Errors
*/

# define SALT_ERR1 "[32mA salt is required ( 16 HEX chars).[0m\n"
# define SALT_ERR2 "Enter a [92mnew salt[0m: "
# define SALT_ERROR SALT_ERR1 SALT_ERR2

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

/*
**	DES Auxiliary Declarations
*/

# define PC_1A "57 49 41 33 25 17 9 "
# define PC_1B "1 58 50 42 34 26 18 "
# define PC_1C "10 2 59 51 43 35 27 "
# define PC_1D "19 11 3 60 52 44 36 "
# define PC_1E "63 55 47 39 31 23 15 "
# define PC_1F "7 62 54 46 38 30 22 "
# define PC_1G "14 6 61 53 45 37 29 "
# define PC_1H "21 13 5 28 20 12 4"
# define PERMUTATED_CHOICE_1 PC_1A PC_1B PC_1C PC_1D PC_1E PC_1F PC_1G PC_1H

# define PC_2A "14 17 11 24 1 5 "
# define PC_2B "3 28 15 6 21 10 "
# define PC_2C "23 19 12 4 26 8 "
# define PC_2D "16 7 27 20 13 2 "
# define PC_2E "41 52 31 37 47 55 "
# define PC_2F "30 40 51 45 33 48 "
# define PC_2G "44 49 39 56 34 53 "
# define PC_2H "46 42 50 36 29 32"
# define PERMUTATED_CHOICE_2 PC_2A PC_2B PC_2C PC_2D PC_2E PC_2F PC_2G PC_2H

# define MAX_64(a) ((a) > 64 ? 64 : a)

# define NUM_OF_SHIFTS "1 1 2 2 2 2 2 2 1 2 2 2 2 2 2 1"

# define LEFT_ROT_28(a, b) ((((a) << (b)) | ((a) >> (28 - (b)))) & 0xFFFFFFF)

# define IP_A "58 50 42 34 26 18 10 2 "
# define IP_B "60 52 44 36 28 20 12 4 "
# define IP_C "62 54 46 38 30 22 14 6 "
# define IP_D "64 56 48 40 32 24 16 8 "
# define IP_E "57 49 41 33 25 17 9 1 "
# define IP_F "59 51 43 35 27 19 11 3 "
# define IP_G "61 53 45 37 29 21 13 5 "
# define IP_H "63 55 47 39 31 23 15 7"
# define IP_TABLE IP_A IP_B IP_C IP_D IP_E IP_F IP_G IP_H

# define EBIT_A "32 1 2 3 4 5 "
# define EBIT_B "4 5 6 7 8 9 "
# define EBIT_C "8 9 10 11 12 13 "
# define EBIT_D "12 13 14 15 16 17 "
# define EBIT_E "16 17 18 19 20 21 "
# define EBIT_F "20 21 22 23 24 25 "
# define EBIT_G "24 25 26 27 28 29 "
# define EBIT_H "28 29 30 31 32 1"
# define EBIT_TABLE EBIT_A EBIT_B EBIT_C EBIT_D EBIT_E EBIT_F EBIT_G EBIT_H

# define S1_A "14 4 13 1 2 15 11 8 3 10 6 12 5 9 0 7"
# define S1_B "0 15 7 4 14 2 13 1 10 6 12 11 9 5 3 8"
# define S1_C "4 1 14 8 13 6 2 11 15 12 9 7 3 10 5 0"
# define S1_D "15 12 8 2 4 9 1 7 5 11 3 14 10 0 6 13"
# define GET_S1_A des->s[0][0] = ft_intarrayfromstr(S1_A);
# define GET_S1_B des->s[0][1] = ft_intarrayfromstr(S1_B);
# define GET_S1_C des->s[0][2] = ft_intarrayfromstr(S1_C);
# define GET_S1_D des->s[0][3] = ft_intarrayfromstr(S1_D)
# define GET_S1 GET_S1_A GET_S1_B GET_S1_C GET_S1_D

# define S2_A "15 1 8 14 6 11 3 4 9 7 2 13 12 0 5 10"
# define S2_B "3 13 4 7 15 2 8 14 12 0 1 10 6 9 11 5"
# define S2_C "0 14 7 11 10 4 13 1 5 8 12 6 9 3 2 15"
# define S2_D "13 8 10 1 3 15 4 2 11 6 7 12 0 5 14 9"
# define GET_S2_A des->s[1][0] = ft_intarrayfromstr(S2_A);
# define GET_S2_B des->s[1][1] = ft_intarrayfromstr(S2_B);
# define GET_S2_C des->s[1][2] = ft_intarrayfromstr(S2_C);
# define GET_S2_D des->s[1][3] = ft_intarrayfromstr(S2_D)
# define GET_S2 GET_S2_A GET_S2_B GET_S2_C GET_S2_D

# define S3_A "10 0 9 14 6 3 15 5 1 13 12 7 11 4 2 8"
# define S3_B "13 7 0 9 3 4 6 10 2 8 5 14 12 11 15 1"
# define S3_C "13 6 4 9 8 15 3 0 11 1 2 12 5 10 14 7"
# define S3_D "1 10 13 0 6 9 8 7 4 15 14 3 11 5 2 12"
# define GET_S3_A des->s[2][0] = ft_intarrayfromstr(S3_A);
# define GET_S3_B des->s[2][1] = ft_intarrayfromstr(S3_B);
# define GET_S3_C des->s[2][2] = ft_intarrayfromstr(S3_C);
# define GET_S3_D des->s[2][3] = ft_intarrayfromstr(S3_D)
# define GET_S3 GET_S3_A GET_S3_B GET_S3_C GET_S3_D

# define S4_A "7 13 14 3 0 6 9 10 1 2 8 5 11 12 4 15"
# define S4_B "13 8 11 5 6 15 0 3 4 7 2 12 1 10 14 9"
# define S4_C "10 6 9 0 12 11 7 13 15 1 3 14 5 2 8 4"
# define S4_D "3 15 0 6 10 1 13 8 9 4 5 11 12 7 2 14"
# define GET_S4_A des->s[3][0] = ft_intarrayfromstr(S4_A);
# define GET_S4_B des->s[3][1] = ft_intarrayfromstr(S4_B);
# define GET_S4_C des->s[3][2] = ft_intarrayfromstr(S4_C);
# define GET_S4_D des->s[3][3] = ft_intarrayfromstr(S4_D)
# define GET_S4 GET_S4_A GET_S4_B GET_S4_C GET_S4_D

# define S5_A "2 12 4 1 7 10 11 6 8 5 3 15 13 0 14 9"
# define S5_B "14 11 2 12 4 7 13 1 5 0 15 10 3 9 8 6"
# define S5_C "4 2 1 11 10 13 7 8 15 9 12 5 6 3 0 14"
# define S5_D "11 8 12 7 1 14 2 13 6 15 0 9 10 4 5 3"
# define GET_S5_A des->s[4][0] = ft_intarrayfromstr(S5_A);
# define GET_S5_B des->s[4][1] = ft_intarrayfromstr(S5_B);
# define GET_S5_C des->s[4][2] = ft_intarrayfromstr(S5_C);
# define GET_S5_D des->s[4][3] = ft_intarrayfromstr(S5_D)
# define GET_S5 GET_S5_A GET_S5_B GET_S5_C GET_S5_D

# define S6_A "12 1 10 15 9 2 6 8 0 13 3 4 14 7 5 11"
# define S6_B "10 15 4 2 7 12 9 5 6 1 13 14 0 11 3 8"
# define S6_C "9 14 15 5 2 8 12 3 7 0 4 10 1 13 11 6"
# define S6_D "4 3 2 12 9 5 15 10 11 14 1 7 6 0 8 13"
# define GET_S6_A des->s[5][0] = ft_intarrayfromstr(S6_A);
# define GET_S6_B des->s[5][1] = ft_intarrayfromstr(S6_B);
# define GET_S6_C des->s[5][2] = ft_intarrayfromstr(S6_C);
# define GET_S6_D des->s[5][3] = ft_intarrayfromstr(S6_D)
# define GET_S6 GET_S6_A GET_S6_B GET_S6_C GET_S6_D

# define S7_A "4 11 2 14 15 0 8 13 3 12 9 7 5 10 6 1"
# define S7_B "13 0 11 7 4 9 1 10 14 3 5 12 2 15 8 6"
# define S7_C "1 4 11 13 12 3 7 14 10 15 6 8 0 5 9 2"
# define S7_D "6 11 13 8 1 4 10 7 9 5 0 15 14 2 3 12"
# define GET_S7_A des->s[6][0] = ft_intarrayfromstr(S7_A);
# define GET_S7_B des->s[6][1] = ft_intarrayfromstr(S7_B);
# define GET_S7_C des->s[6][2] = ft_intarrayfromstr(S7_C);
# define GET_S7_D des->s[6][3] = ft_intarrayfromstr(S7_D)
# define GET_S7 GET_S7_A GET_S7_B GET_S7_C GET_S7_D

# define S8_A "13 2 8 4 6 15 11 1 10 9 3 14 5 0 12 7"
# define S8_B "1 15 13 8 10 3 7 4 12 5 6 11 0 14 9 2"
# define S8_C "7 11 4 1 9 12 14 2 0 6 10 13 15 3 5 8"
# define S8_D "2 1 14 7 4 10 8 13 15 12 9 0 3 5 6 11"
# define GET_S8_A des->s[7][0] = ft_intarrayfromstr(S8_A);
# define GET_S8_B des->s[7][1] = ft_intarrayfromstr(S8_B);
# define GET_S8_C des->s[7][2] = ft_intarrayfromstr(S8_C);
# define GET_S8_D des->s[7][3] = ft_intarrayfromstr(S8_D)
# define GET_S8 GET_S8_A GET_S8_B GET_S8_C GET_S8_D

# define P_A "16 7 20 21 "
# define P_B "29 12 28 17 "
# define P_C "1 15 23 26 "
# define P_D "5 18 31 10 "
# define P_E "2 8 24 14 "
# define P_F "32 27 3 9 "
# define P_G "19 13 30 6 "
# define P_H "22 11 4 25"
# define P_TABLE P_A P_B P_C P_D P_E P_F P_G P_H

# define INVP_A "40 8 48 16 56 24 64 32 "
# define INVP_B "39 7 47 15 55 23 63 31 "
# define INVP_C "38 6 46 14 54 22 62 30 "
# define INVP_D "37 5 45 13 53 21 61 29 "
# define INVP_E "36 4 44 12 52 20 60 28 "
# define INVP_F "35 3 43 11 51 19 59 27 "
# define INVP_G "34 2 42 10 50 18 58 26 "
# define INVP_H "33 1 41 9 49 17 57 25"
# define INVERSE_TABLE INVP_A INVP_B INVP_C INVP_D INVP_E INVP_F INVP_G INVP_H

#endif

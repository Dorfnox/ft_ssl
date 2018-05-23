/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 20:57:13 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/15 19:34:17 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <readpassphrase.h>
# include "libft.h"
# include "ft_ssl_structs.h"
# include "ft_ssl_macros.h"

/*
**	Error handling
**	----------------------------------------------------------------------------
*/

int						ssl_error(char *name, char *message, int ret_value);
void					clean_up(t_ssl *ssl);

/*
**	Argument / Flag handling
**	----------------------------------------------------------------------------
*/

unsigned int			handle_command(
							t_ssl *ssl, char **av);
unsigned int			handle_command_2(
							t_ssl *ssl, char **av);
void					init_command_settings(
							t_ssl *ssl, char *sn, char *ln, char *valid_flags);
unsigned int			collect_given_parameter(
							char ***save, char *param);

unsigned int			flag_handler(
							t_ssl *ssl, char ***av);
void					*search_flag_queue(
							t_node *n, char *flag);
void					*search_for_flag(
							t_node *n, unsigned int (*f)(t_ssl *, char ***));
void					clean_flag_queue(
							t_ssl *ssl);

/*
**	General flags in flags_*.c
*/

unsigned int			p_flag(t_ssl *ssl, char ***av);
unsigned int			q_flag(t_ssl *ssl, char ***av);
unsigned int			r_flag(t_ssl *ssl, char ***av);
unsigned int			s_flag(t_ssl *ssl, char ***av);

unsigned int			d_flag(t_ssl *ssl, char ***av);
unsigned int			e_flag(t_ssl *ssl, char ***av);
unsigned int			i_flag(t_ssl *ssl, char ***av);
unsigned int			o_flag(t_ssl *ssl, char ***av);

unsigned int			k_flag(t_ssl *ssl, char ***av);
char					*get_key_from_user(char *given_key);
int						does_not_contain_hex_characters_or_is_null(char *key);

/*
**	Specific flag handling for each different encryption type
*/

unsigned int			handle_md5_flags(t_ssl *ssl, char **av);
void					consolidate_md5_flags(t_ssl *ssl);

unsigned int			handle_sha256_flags(t_ssl *ssl, char **av);
void					consolidate_sha256_flags(t_ssl *ssl);

unsigned int			handle_base64_flags(t_ssl *ssl, char **av);
void					consolidate_base64_flags(t_ssl *ssl);

unsigned int			handle_des_flags(t_ssl *ssl, char **av);
void					consolidate_des_flags(t_ssl *ssl);



/*
**	Input handling
**	----------------------------------------------------------------------------
*/

char					*input_from_file(t_ssl *ssl);
char					*input_from_stdin(t_ssl *ssl);
char					*input_from_given_string(t_ssl *ssl);

/*
**	Output handling
**	----------------------------------------------------------------------------
*/

void					output_stdin(t_ssl *ssl, char *input, char *outputt);
void					output_given_string(t_ssl *ssl, char *in, char *out);
void					output_filename(t_ssl *ssl, char *input, char *outp);
void					output_to_file_or_stdout(t_ssl *s, char *i, char *o);

/*
**	Endian handling
**	----------------------------------------------------------------------------
*/

uint32_t				swap_endian32(uint32_t a);
uint64_t				swap_endian64(uint64_t a);

/*
**	Crypto execution
**	----------------------------------------------------------------------------
*/

void					execute_all(t_ssl *ssl);

void					execute_message_digest(t_ssl *ssl);
void					execute_given_strings(t_ssl *ssl);
void					execute_input_files(t_ssl *ssl);
void					execute_general(t_ssl *ssl, char *input, int type);

void					execute_cipher(t_ssl *ssl);

/*
**	Message Digest
**	----------------------------------------------------------------------------
**
**	MD5
*/

void					init_md5(t_md5 *md5);
void					init_md5_s_table(t_md5 *md5);
void					init_md5_k_table1(t_md5 *md5);
void					init_md5_k_table2(t_md5 *md5);
void					init_md5_k_table3(t_md5 *md5);

char					*execute_md5(t_ssl *ssl, char *input);
void					append_bits_md5(t_ssl *s, t_md5 *m, char *i);
void					execute_md5_(t_md5 *md5, int j);
char					*build_md5_output(t_md5 *md5);
void					clean_md5(t_md5 *md5);

/*
**	SHA256
*/

void					init_sha256(t_sha256 *sha);
void					init_sha256_k_table1(t_sha256 *sha);
void					init_sha256_k_table2(t_sha256 *sha);
void					init_sha256_k_table3(t_sha256 *sha);

char					*execute_sha256(t_ssl *ssl, char *input);
void					init_words(t_sha256 *sha, size_t *k);
void					init_working_variables(t_sha256 *sha);
void					perform_algorithm(t_sha256 *sha);
void					add_to_digest(t_sha256 *sha);

void					append_bits_sha256(t_ssl *s, t_sha256 *sha, char *i);
char					*build_sha256_output(t_sha256 *sha);
void					clean_sha256(t_sha256 *sha);

/*
**	SHA224
*/

void					init_sha224(t_sha256 *sha);
char					*execute_sha224(t_ssl *ssl, char *input);
char					*build_sha224_output(t_sha256 *sha);

/*
**	Cipher
**	----------------------------------------------------------------------------
**
**	BASE64
*/

char					*execute_base64(t_ssl *ssl, char *input);
char					*base64_encrypt(t_ssl *ssl, char *input);
char					*base64_decrypt(t_ssl *ssl, char *input);
int						*get_decrypt_table(char *input, int i_len, int *o_len);

/*
**	DES-ECB
*/


/*
**	To create new crypto algorithm:
**	-------------------------------
**	1) Add to handle_command in flags.c the initializing for the new algo
**	2) Create a valid flags macro for that algorithm
**	3) Add to Message Digest Commands macro the new name
**	4) Create the handle_flags and execute functions for the algorithm
*/

#endif

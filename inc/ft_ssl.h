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
void					malloc_error(char *message);
void					clean_up(t_ssl *ssl);

/*
**	Argument / Flag handling
**	----------------------------------------------------------------------------
*/

unsigned int			handle_command(t_ssl *ssl, char **av);
unsigned int			handle_command_2(t_ssl *ssl, char **av);
void					init_settings(t_ssl *s, char *l, char *b, char *v);
unsigned int			collect_given_parameter(char ***save, char *param);

void					add_flag(t_queue **q, char *flag, void *flag_func);
unsigned int			flag_handler(t_ssl *ssl, char ***av);
void					*search_flag_queue(t_node *n, char *flag);
void					clean_flag_queue(t_queue **q);

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

unsigned int			key_flag(t_ssl *ssl, char ***av);
char					*get_key_from_user(char *given_key);
int						key_is_valid(char *key);

unsigned int			password_flag(t_ssl *ssl, char ***av);
char					*get_password_from_user(char *given_password);

unsigned int			salt_flag(t_ssl *ssl, char ***av);
char					*get_salt_from_user(char *given_salt);
int						salt_is_valid(char *salt);

unsigned int			base64_flag(t_ssl *ssl, char ***av);

/*
**	Specific flag handling for each different encryption type
*/

unsigned int			handle_md5_flags(t_ssl *ssl, char **av);
unsigned int			consolidate_md5_flags(t_ssl *ssl);

unsigned int			handle_sha256_flags(t_ssl *ssl, char **av);
unsigned int			consolidate_sha256_flags(t_ssl *ssl);

unsigned int			handle_base64_flags(t_ssl *ssl, char **av);
unsigned int			consolidate_base64_flags(t_ssl *ssl);

unsigned int			handle_des_flags(t_ssl *ssl, char **av);
unsigned int			consolidate_des_flags(t_ssl *ssl);

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

/*
**	Endian handling
**	----------------------------------------------------------------------------
*/

uint32_t				swap_endian32(uint32_t a);
uint64_t				swap_endian64(uint64_t a);

/*
**	Password-Based Key Derivation Functionality (PBKDF2)
**	----------------------------------------------------------------------------
*/

void					pbkdf2(t_pbkdf *p);

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
void					clean_cipher(t_ssl *ssl);

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

char					*execute_md5(t_ssl *ssl, char *input, t_io_len *l);
void					append_bits_md5(t_md5 *m, char *in, t_io_len *l);
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

char					*execute_sha256(t_ssl *ssl, char *input, t_io_len *l);
void					init_words(t_sha256 *sha, size_t *k);
void					init_working_variables(t_sha256 *sha);
void					perform_algorithm(t_sha256 *sha);
void					add_to_digest(t_sha256 *sha);

void					append_bits_sha256(t_sha256 *s, char *i, size_t *len);
char					*build_sha256_output(t_sha256 *sha);
void					clean_sha256(t_sha256 *sha);

/*
**	SHA224
*/

void					init_sha224(t_sha256 *sha);

char					*execute_sha224(t_ssl *ssl, char *input, t_io_len *l);
char					*build_sha224_output(t_sha256 *sha);

/*
**	Cipher
**	----------------------------------------------------------------------------
**
**	BASE64
*/

char					*execute_base64(t_ssl *ssl, char *input, t_io_len *l);
char					*base64_encrypt(char *input, size_t ilen, size_t *olen);
char					*base64_decrypt(char *input, size_t ilen, size_t *olen);
int						*get_decrypt_table(char *in, size_t ilen, size_t *olen);

/*
**	DES-ECB
*/

void					init_des(t_des *des);
void					init_des_key(t_ssl *ssl, t_des *des);
void					init_des_subkeys(t_des *des, uint8_t rev);
uint64_t				permutated_choice(uint64_t key, int *pc, int size);
int						clean_des_ecb(t_des *des);

char					*execute_des_ecb(t_ssl *ssl, char *in, t_io_len *l);
uint64_t				des_ecb_str_to_64bit(char **input);
char					*create_des_output(t_ssl *s, size_t *iln, size_t *oln);
uint64_t				process_des_ecb(t_des *des, uint64_t message);
uint32_t				des_alg(t_des *des, uint32_t b, uint64_t key);

#endif

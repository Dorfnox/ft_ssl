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

# include "libft.h"
# include "ft_ssl_macros.h"

enum 					e_enc_type
{
	MD5 = 1,
	SHA_256
};

enum					e_output_type
{
	STDIN_OUTPUT = 1,
	GIVEN_STRING_OUTPUT,
	FILENAME_OUTPUT
};

typedef struct			s_flags
{
	unsigned int		p:1;
	unsigned int		q:1;
	unsigned int		r:1;
	unsigned int		s:1;
}						t_f;

typedef struct			s_ft_ssl
{
	unsigned int		enc_type;
	char				*cmd_name_lower;
	char				*cmd_name_upper;
	char				*cmd_valid_flags;
	struct s_flags		f;
	char				*flag_error;
	char				**input_files;
	char				*filename;
	char				**given_strings;
	char				*given_string;
	size_t				input_len;
	unsigned int		(*handle_flags)(struct s_ft_ssl *, char **);
	char				*(*execute_func)(struct s_ft_ssl *, char *);
}						t_ssl;

typedef union			u_32u
{
	uint32_t			v;
	uint16_t			p16[2];
	uint8_t				p8[4];
}						t_32bitunion;

typedef union			u_64u
{
	uint64_t			v;
	uint32_t			p32[2];
	uint16_t			p16[4];
	uint8_t				p8[8];
}						t_64bitunion;

typedef struct			s_md5
{
	uint32_t			a;
	uint32_t			b;
	uint32_t			c;
	uint32_t			d;
	uint32_t			a2;
	uint32_t			b2;
	uint32_t			c2;
	uint32_t			d2;
	uint32_t			f;
	uint32_t			g;
	uint32_t			k[64];
	uint32_t			s[64];
	uint32_t			m[16];
	uint8_t				*data;
}						t_md5;

typedef struct			s_sha256
{
	uint32_t			h0;
	uint32_t			h1;
	uint32_t			h2;
	uint32_t			h3;
	uint32_t			h4;
	uint32_t			h5;
	uint32_t			h6;
	uint32_t			h7;
	uint32_t			k[64];
	uint32_t			w[64];
	uint32_t			tmpa;
	uint32_t			tmpb;
	uint32_t			tmpc;
	uint32_t			tmpd;
	uint32_t			tmpe;
	uint32_t			tmpf;
	uint32_t			a;
	uint32_t			b;
	uint32_t			c;
	uint32_t			d;
	uint32_t			e;
	uint32_t			f;
	uint32_t			g;
	uint32_t			h;
	uint8_t				*data;
}						t_sha256;

/*
**	Error handling
**	----------------------------------------------------------------------------
*/

int						ssl_error(char *name, char *message, int ret_value);
void					clean_up(t_ssl *ssl);

/*
**	Argument handling
**	----------------------------------------------------------------------------
*/

unsigned int			handle_command(t_ssl *ssl, char **av);
void					init_command_settings(
						t_ssl *ssl, char *sn, char *ln, char *valid_flags);

unsigned int			handle_md5_flags(t_ssl *ssl, char **av);
unsigned int			handle_sha256_flags(t_ssl *ssl, char **av);

int						collect_given_parameter(char ***save, char *prm);

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

void					output_stdin(t_ssl *ssl, char *input, char *output);
void					output_given_string(t_ssl *ssl, char *input, char *output);
void					output_filename(t_ssl *ssl, char *input, char *output);

/*
**	Endian handling
*/
uint32_t				swap_endian32(uint32_t a);
uint64_t				swap_endian64(uint64_t a);

/*
**	Crypto execution
**	----------------------------------------------------------------------------
*/

void					execute_all(t_ssl *ssl);
void					execute_given_strings(t_ssl *ssl);
void					execute_input_files(t_ssl *ssl);
void					execute_general(t_ssl *ssl, char *input, int type);

/*
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
**	SHA-256
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

#endif

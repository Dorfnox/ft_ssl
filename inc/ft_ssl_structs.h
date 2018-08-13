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

#ifndef FT_SSL_STRUCTS_H
# define FT_SSL_STRUCTS_H

enum					e_output_type
{
	STDIN_OUTPUT = 1,
	GIVEN_STRING_OUTPUT,
	FILENAME_OUTPUT
};

typedef struct			s_flag_queue
{
	char				*flag;
	void				*flag_func;
}						t_flag_queue;

typedef struct			s_flags
{
	unsigned int		p:1;
	unsigned int		q:1;
	unsigned int		r:1;
	unsigned int		s:1;
	unsigned int		e:1;
	unsigned int		d:1;
	unsigned int		i:1;
	unsigned int		o:1;
	unsigned int		a:1;
	unsigned int		k:1;
	unsigned int		v:1;
}						t_f;

typedef struct			s_input_output_len
{
	size_t				in_len;
	size_t				out_len;
}						t_io_len;

typedef struct			s_ft_ssl
{
	char				*cmd_name_lower;
	char				*cmd_name_upper;
	char				*cmd_valid_flags;
	char				*user_password;
	char				*user_salt;
	char				*user_key;
	char				*user_iv;
	struct s_flags		f;
	t_queue				*flag_queue;
	char				*flag_error;
	char				**input_files;
	char				*in_file;
	char				*out_file;
	char				**given_strings;
	char				*given_string;
	size_t				input_len;
	void				(*execute_func)(struct s_ft_ssl *);
	unsigned int		(*handle_flags)(struct s_ft_ssl *, char **);
	char				*(*enc_func)(struct s_ft_ssl *, char *, t_io_len *);
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

/*
**	Password-Based Key Derivation Function (PBKDF2)
*/

typedef struct			s_pbkdf
{
	char				*key;
	char				*iv;
	char				*password;
	size_t				pass_len;
	uint64_t			salt;
	size_t				salt_len;
	size_t				num_of_iterations;
	char				*(*algo)(t_ssl *, char *, t_io_len *);
}						t_pbkdf;

/*
**	Message Digest Structs
*/

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
**	Cipher Structs
*/

typedef struct			s_base64
{
	size_t				i;
	size_t				j;
	size_t				k;
	int					res_a;
	int					res_b;
	int					res_c;
	int					res_d;
	int					res_e;
	int					input_len;
	int					output_len;
}						t_base64;

typedef struct			s_des
{
	uint64_t			key;
	uint64_t			key_pc1;
	uint32_t			l[16];
	uint32_t			r[16];
	uint64_t			subkey[16];
	uint64_t			initial_perm;
	char				*user_key;
	int					*pc1;
	int					*pc2;
	int					*shifts;
	int					*ip_table;
	int					*ebit;
	int					*s[8][4];
	int					*p_table;
	int					*inverse_table;
}						t_des;

#endif

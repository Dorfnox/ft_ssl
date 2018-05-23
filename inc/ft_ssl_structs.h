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
}						t_f;

typedef struct			s_ft_ssl
{
	char				*cmd_name_lower;
	char				*cmd_name_upper;
	char				*cmd_valid_flags;
	struct s_flags		f;
	t_queue				*flag_queue;
	char				*flag_error;
	char				**input_files;
	char				*filename;
	char				*in_file;
	char				*out_file;
	char				**given_strings;
	char				*given_string;
	size_t				input_len;
	void				(*execute_func)(struct s_ft_ssl *);
	unsigned int		(*handle_flags)(struct s_ft_ssl *, char **);
	char				*(*enc_func)(struct s_ft_ssl *, char *);
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
	int					i;
	int					j;
	int					k;
	int					res_a;
	int					res_b;
	int					res_c;
	int					res_d;
	int					res_e;
	int					input_len;
	int					output_len;
}						t_base64;

#endif

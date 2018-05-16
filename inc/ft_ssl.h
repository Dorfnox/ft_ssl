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
	unsigned int		(*handle_flags)(struct s_ft_ssl *, char **);
	char				*(*execute_func)(struct s_ft_ssl *, char *);
	void				*enc_struct;
}						t_ssl;

typedef struct			s_md5
{
	uint32_t			a;
	uint32_t			b;
	uint32_t			c;
	uint32_t			d;
}						t_md5;

/*
**	Error handling
**	----------------------------------------------------------------------------
*/

int						ssl_error(char *name, char *message, int ret_value);

/*
**	Argument handling
**	----------------------------------------------------------------------------
*/

unsigned int			handle_command(t_ssl *ssl, char **av);
void					init_command_settings(
						t_ssl *ssl, char *sn, char *ln, char *valid_flags);

unsigned int			handle_md5_flags(t_ssl *ssl, char **av);
unsigned int			handle_sha256_flags(t_ssl *ssl, char **av);

/*
**	Crypto execution
**	----------------------------------------------------------------------------
*/

void					execute_all(t_ssl *ssl);
void					execute_from_input_files(t_ssl *ssl);
void					execute_from_stdin(t_ssl *ssl);
void					execute_general(t_ssl *ssl, char *input);
void					display_output(t_ssl *ssl, char *output);

char					*execute_md5(t_ssl *ssl, char *input);
char					*execute_sha256(t_ssl *ssl, char *output);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:05:42 by mrolfe            #+#    #+#             */
/*   Updated: 2019/04/29 18:49:43 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

int				ret;
int				i;
int				zero;

typedef struct	s_spec
{
	char		type;
	int			precision;
	int			width;
	char		size[2];
	char		flags[5];
}				t_spec;

typedef struct	s_precise
{
	char		*ret;
	int			len;
	int         i;
	char		*point;
}				t_precise;

typedef struct	s_process
{
	int			dot;
	int			j;
	t_spec		spec;
	int			k;
	int			flag;
}				t_process;

int				ft_printf(const char *format, ...);
void			print_and_smth(const char *format, va_list *ap);
void			process_specifier(char *format, va_list *ap);
void			process_specifier2(char *format,  t_spec *spec, int *j);
void			process_specifier3(char *format, t_spec	*spec, int *j, va_list *ap);
void			process_specifier4(char *format, t_spec	*spec, int flag, int *j);
void			process_specifier5(char *format, va_list *ap, t_spec *spec, t_process *process);
char			*type_specifier(t_spec *spec, va_list *ap);
char			*width_specifier(char *res, t_spec *spec);
char			*precise_specifier(char *res, t_spec *spec);
char			*flag_specifier(char *res, t_spec *spec, int flag);
void			print_param(char *res);
char			*s_precise(char *res, t_spec *spec);
char			*f_precise(char *res, t_spec *spec);
char			*x_bigx_precise(char *res, t_spec *spec);
char			*type_percent(char *res);
char			*other_precise(char *res, t_spec *spec);
char			*other_precise2(char *res, t_spec *spec, t_precise *params);
void			call_specifier(va_list *ap, t_spec *spec, int flag);
char			*type_ox_bigx(char *res, t_spec *spec, va_list *ap);
char			*type_s(char *res, va_list *ap);
char			*type_p(char *res, va_list *ap, t_spec *spec);
char			*type_f(char *res, va_list *ap, t_spec *spec);
char			*type_c(char *res, va_list *ap);
char			*type_id(char *res, va_list *ap, t_spec *spec);
char			*zero_flag(char *res, t_spec *spec);
char			*zero_flag2(char **res, t_spec *spec, int *len);
char			*minus_flag(char *res, t_spec *spec);
char			*plus_flag(char *res, t_spec *spec);
char			*plus_flag2(char *res, int *len);
char			*plus_flag3(char *res, int *len);
char			*hash_flag(char *res, t_spec *spec);
char			*hash_flag_forx_bigx(char *res, t_spec *spec, int *len);
char			*hash_flag_else(char *res, t_spec *spec, int *len);
char			*space_flag(char *res, t_spec *spec);
char			*ft_fitoa(long double num);
char			*ft_itoa_base(long long num, int base, t_spec *spec);
char			*ft_uitoa_base(unsigned long long num, int base, t_spec *spec);
void			find_width_param(char *format, va_list *ap, t_spec *spec);
int				check_minus(char *res, char **point);
int				check_plus(char *res, char **point);
int				check_space(char *res, char **point);
int				check_0x(char *res, char **point);
void			clean_struct(t_spec *spec);
char			*p_precise(char *res, t_spec *spec);
char			*type_u(char *res, va_list *ap, t_spec *spec);
void			one_percent_only(char *format);

#endif

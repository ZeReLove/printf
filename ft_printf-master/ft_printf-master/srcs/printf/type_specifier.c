/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_specifier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:05:42 by mrolfe            #+#    #+#             */
/*   Updated: 2019/04/25 17:24:02 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*type_specifier(t_spec *spec, va_list *ap)
{
	char	*res;

	res = NULL;
	if (spec->type == 'c')
		res = type_c(res, ap);
	else if (spec->type == 's')
		res = type_s(res, ap);
	else if (spec->type == 'p')
		res = type_p(res, ap, spec);
	else if (spec->type == 'o'
			|| spec->type == 'x' || spec->type == 'X')
		res = type_oxX(res, spec, ap);
	else if (spec->type == 'f')
		res = type_f(res, ap, spec);
	else if (spec->type == 'i' || spec->type == 'd')
		res = type_id(res, ap, spec);
	else if (spec->type == '%')
		res = type_percent(res);
	else if (spec->type == 'u')
		res = type_u(res, ap, spec);
	return (res);
}

char	*type_percent(char *res)
{
	res = (char*)malloc(2 * sizeof(char));
	res[0] = '%';
	res[1] = '\0';
	return (res);
}

char	*type_u(char *res, va_list *ap, t_spec *spec)
{
	unsigned long long	nb;

	nb = va_arg(*ap, unsigned long long);
	if (spec->size[0] == 'h' && spec->size[1] == 'h')
		res = ft_uitoa_base((unsigned char)nb, 10, spec);
	else if (spec->size[0] == 'h' && spec->size[1] != 'h')
		res = ft_uitoa_base((unsigned short int)nb, 10, spec);
	else if (spec->size[0] == 'l' && spec->size[1] == 'l')
		res = ft_uitoa_base((unsigned long long)nb, 10, spec);
	else if (spec->size[0] == 'l' && spec->size[1] != 'l')
		res = ft_uitoa_base((unsigned long long)nb, 10, spec);
	else
		res = ft_uitoa_base((unsigned int)nb, 10, spec);
	return (res);
}

char	*type_oxX(char *res, t_spec *spec, va_list *ap)
{
	unsigned long long	nb;
	int					base;

	if (spec->type == 'o')
		base = 8;
	else if (spec->type == 'x')
		base = 16;
	else if (spec->type == 'X')
		base = 16;
	nb = va_arg(*ap, unsigned long long);
	if (spec->size[0] == 'h' && spec->size[1] == 'h')
		res = ft_uitoa_base((unsigned char)nb, base, spec);
	else if (spec->size[0] == 'h' && spec->size[1] != 'h')
		res = ft_uitoa_base((unsigned short int)nb, base, spec);
	else if (spec->size[0] == 'l' && spec->size[1] == 'l')
		res = ft_uitoa_base((unsigned long long)nb, base, spec);
	else if (spec->size[0] == 'l' && spec->size[1] != 'l')
		res = ft_uitoa_base((unsigned long long)nb, base, spec);
	else
		res = ft_uitoa_base((unsigned int)nb, base, spec);
	return (res);
}

char	*type_c(char *res, va_list *ap)
{
	int	ch;

	ch = va_arg(*ap, int);
	res = (char*)malloc(2 * sizeof(char));
	if (!ch)
		zero = 1;
	res[0] = ch;
	res[0] = (char)res[0];
	res[1] = '\0';
	return (res);
}

char	*type_s(char *res, va_list *ap)
{
	char	*s;
	int		len;

	s = va_arg(*ap, char*);
	if (s == NULL)
	{
		res = ft_strnew(6);
		ft_strcpy(res, "(null)");
		return (res);
	}
	len = (int)ft_strlen((char *)s);
	res = (char*)malloc((len + 1) * sizeof(char));
	ft_strcpy(res, s);
	return (res);
}

char	*type_p(char *res, va_list *ap, t_spec *spec)
{
	long	nb;
	char	*ret;
	int		len;

	nb = va_arg(*ap, long);
	res = ft_itoa_base(nb, 16, spec);
	len = (int)ft_strlen((char*)res);
	if (!(ret = ft_strnew(len + 2)))
		return (NULL);
	ft_strcpy(&ret[2], (char*)res);
	ret[0] = '0';
	ret[1] = 'x';
	free((char*)res);
	return (ret);
}

char	*type_f(char *res, va_list *ap, t_spec *spec)
{
	long double	nb;
	double		n;

	if (spec->size[0] == 'L')
	{
		nb = va_arg(*ap, long double);
		res = ft_fitoa(nb);
	}
	else
	{
		n = va_arg(*ap, double);
		res = ft_fitoa(n);
	}
	return (res);
}

char	*type_id(char *res, va_list *ap, t_spec *spec)
{
	long long	nb;

	nb = va_arg(*ap, long long);
	if (spec->size[0] == 'h' && spec->size[1] == 'h')
		res = ft_itoa_base((char)nb, 10, spec);
	else if (spec->size[0] == 'h' && spec->size[1] != 'h')
		res = ft_itoa_base((short int)nb, 10, spec);
	else if (spec->size[0] == 'l' && spec->size[1] == 'l')
		res = ft_itoa_base((long long)nb, 10, spec);
	else if (spec->size[0] == 'l' && spec->size[1] != 'l')
		res = ft_itoa_base((long long)nb, 10, spec);
	else
		res = ft_itoa((int)nb);
	return (res);
}

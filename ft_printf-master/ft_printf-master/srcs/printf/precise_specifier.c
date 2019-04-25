/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precise_specifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:05:42 by mrolfe            #+#    #+#             */
/*   Updated: 2019/04/25 17:46:23 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*precise_specifier(char *res, t_spec *spec)
{
	char	*ret;

	if (spec->type == 'f')
		ret = f_precise(res, spec);
	else if (spec->type == 's')
		ret = s_precise(res, spec);
	else if (spec->type == 'p')
		ret = p_precise(res, spec);
	else if (spec->type == 'x' || spec->type == 'X')
		ret = xX_precise(res, spec);
	else if (spec->type != 'c')
		ret = other_precise(res, spec);
	else
		ret = res;
	return (ret);
}

char	*xX_precise(char *res, t_spec *spec)
{
	char	*ret;

	if (res[0] == '0' && (res[1] == 'x' || res[1] == 'X'))
		ret = p_precise(res, spec);
	else
		ret = other_precise(res, spec);
	return (ret);
}

char	*p_precise(char *res, t_spec *spec)
{
	char	*ret;
	int		len;
	int		i;

	i = 0;
	len = (int)ft_strlen((char*)res) - 2;
	if (spec->precision == 0 && res[2] == '0' && res[3] == '\0')
	{
		res[2] = '\0';
		return (res);
	}
	if (len < spec->precision)
	{
		if (!(ret = ft_strnew((int)spec->precision + 2)))
			return (NULL);
		while (i < spec->precision - len)
			ret[i++] = '0';
		ft_strcpy(&ret[i], (char*)res);
		free((char*)res);
		return (ret);
	}
	return (res);
}

char	*other_precise(char *res, t_spec *spec)
{
	char	*ret;
	int		len;
	int		i;
	char	*point;

	i = 0;
	point = NULL;
	len = (int)ft_strlen((char*)res);
	if (zero)
		return (res);
	if (spec->precision == 0 && res[0] == '0' && res[1] == '\0')
	{
		res[0] = '\0';
		return (res);
	}
	if (res[0] == '0' && res[1] == '\0' && spec->type == 'o')
		return (res);
	if (check_minus(res, &point))
		spec->precision += 1;
	if (spec->precision == 0 && res[1] == '0' && res[2] == '\0')
	{
		res[1] = '\0';
		return (res);
	}
	if (len < spec->precision && spec->type != '%')
	{
		if (!(ret = ft_strnew((int)spec->precision)))
			return (NULL);
		while (i < spec->precision - len)
			ret[i++] = '0';
		ft_strcpy(&ret[i], (char*)res);
		free((char*)res);
		return (ret);
	}
	return (res);
}

char	*s_precise(char *res, t_spec *spec)
{
	char	*ret;

	if ((int)ft_strlen((char*)res) > spec->precision)
	{
		if (!(ret = ft_strnew((int)spec->precision)))
			return (NULL);
		ft_strncpy(ret, (char*)res, (int)spec->precision);
		free((char*)res);
		return (ret);
	}
	return (res);
}

char	*f_precise(char *res, t_spec *spec)
{
   int		i;
   char		*ret;
   int		count;

	i = 0;
	count = 0;
	while (res[i] != '.')
		i++;
	if ((int)ft_strlen((char*)(&res[++i])) < spec->precision)
	{
		if (!(ret = ft_strnew((int)spec->precision)))
			return (NULL);
		while (res[i])
		{
			i++;
			count++;
		}
		ft_strncpy(ret, (char*)res, (int)spec->precision);
		ft_memset((char*)(&ret[i]), '0', (int)(spec->precision - count));
		free((char*)res);
		return (ret);
	}
	return (res);
}

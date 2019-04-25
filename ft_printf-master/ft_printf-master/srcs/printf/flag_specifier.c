/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_specifier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:05:42 by mrolfe            #+#    #+#             */
/*   Updated: 2019/04/25 20:08:37 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*flag_specifier(char *res, t_spec *spec, int flag)
{
	if (spec->flags[flag] == '0')
		res = zero_flag(res, spec);
	else if (spec->flags[flag] == '-')
		res = minus_flag(res, spec);
	else if (spec->flags[flag] == '+')
		res = plus_flag(res, spec);
	else if (spec->flags[flag] == '#')
		res = hash_flag(res, spec);
	else if (spec->flags[flag] == ' ')
		res = space_flag(res, spec);
	return (res);
}

char	*zero_flag(char *res, t_spec *spec)
{
	int		len;
	int		i;
	char	*ret;
	int		size;

	i = 0;
	if (zero)
		spec->width -= 1;
	size = spec->width;
	len = (int)ft_strlen((char*)res);
	while (spec->flags[i])
	{
		if (spec->flags[i] == '-')
			return (res);
		i++;
	}
	if (((spec->type == 'i' || spec->type == 'd' || spec->type == 'u'
		|| spec->type == 'o' || spec->type == 'X' || spec->type == 'x')
		&& spec->precision == -1) || spec->type == 'f' || spec->type == 'p' ||
		spec->type == 's' || spec->type == 'c' || spec->type == '%')
	{
		if (len < spec->width)
			zero_flag2(res, spec);
	}
	return (res);
}

char	*zero_flag2(char *res, t_spec *spec)
{
	char	*ret;

	if (!(ret = ft_strnew((int)size)))
		return (NULL);
	ft_memset(ret, '0', spec->width - len);
	ft_strcpy(&ret[(spec->width) - len], (char*)res);
	free((char*)res);
	return (ret);
}

char	*minus_flag(char *res, t_spec *spec)
{
	int		len;
	char	*ret;
	int		size;

	len = (int)ft_strlen((char*)res);
	size = spec->width;
	if (spec->precision > spec->width)
		return (res);
	if (len < spec->width)
	{
		if (!(ret = ft_strnew((int)size)))
			return (NULL);
		ft_strcpy(&ret[0], (char*)res);
		ft_memset((void*)(&ret[len]), ' ', spec->width - len);
		free((char*)res);
		return (ret);
	}
	return (res);
}

char	*plus_flag(char *res, t_spec *spec)
{
	int		len;
	char	*ret;
	char	*point;

	point = NULL;
	len = (int)ft_strlen((char*)res);
	if (spec->type == 'i' || spec->type == 'd')
	{
		if (!check_minus(res, &point))
		{
			if (res[1] == '0' && len >= 2)
			{
				res[0] = '+';
				return (res);
			}
			plus_flag2(res, spec);
			}
		}
	}
	return (res);
}

char	*plus_flag2(char *res, t_spec *spec)
{
	int		len;
	char	*ret;

	if (res[len - 1] == ' ')
	{
		if (!(ret = ft_strnew(len)))
			return (NULL);
		ft_strncpy(&ret[1], res, len - 1);
		ret[0] = '+';
		free((char*)res);
		return (ret);
	}
	else
	{
		if (!(ret = ft_strnew(len + 1)))
			return (NULL);
		ret[0] = '+';
		ft_strcpy(&ret[1], (char*)res);
		free((char*)res);
		return (ret);
	}
}

char	*hash_flag(char *res, t_spec *spec)
{
	int		len;
	char	*ret;

	len = (int)ft_strlen((char*)res);
	if (spec->type == 'o')
	{
		if (res[len - 1] == ' ')
		{
			if (!(ret = ft_strnew(len)))
				return (NULL);
			ft_strncpy(&ret[1], res, len - 1);
			ret[0] = '0';
			free((char*)res);
		}
		else
			hash_flag_else(res, spec);
		return (ret);
	}
	if (spec->type == 'x' || spec->type == 'X')
		hash_flag_forxX(res, spec);
	return (res);
}

char	*hash_flag_forxX(char *res, t_spec *spec)
{
	char	*ret;

	if (res[0] == '0')
		return (res);
	if (!(ret = ft_strnew(len + 2)))
		return (NULL);
	ret[0] = '0';
	if (spec->type == 'x')
			ret[1] = 'x';
	if (spec->type == 'X')
			ret[1] = 'X';
	ft_strcpy(&ret[2], (char*)res);
	free((char*)res);
	return (ret);
}

char	*hash_flag_else(char *res, t_spec *spec)
{
	char	*ret;

	if (res[0] == '0' && res[1] == '\0' && spec->precision == -1)
		return (res);
	if (!(ret = ft_strnew(len + 1)))
		return (NULL);
	ret[0] = '0';
	ft_strcpy(&ret[1], (char*)res);
	free((char*)res);
}

char	*space_flag(char *res, t_spec *spec)
{
	int		len;
	char	*ret;
	int		i;

	i = 0;
	while (spec->flags[i])
	{
		if (spec->flags[i] == '-' || spec->flags[i] == '+')
			return (res);
		i++;
	}
	len = (int)ft_strlen((char*)res);
	if (spec->type == 'd' || spec->type == 'f' || spec->type == 'i')
	{
		if (res[0] != '-')
		{
			if (!(ret = ft_strnew(len + 1)))
				return (NULL);
			ret[0] = ' ';
			ft_strcpy(&ret[1], (char*)res);
			free((char*)res);
			return (ret);
		}
	}
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_specifier2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:05:42 by mrolfe            #+#    #+#             */
/*   Updated: 2019/04/26 18:11:36 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		process_specifier(char *format, va_list *ap)
{
	int		dot;
	int		j;
	t_spec	spec;
	int		k;
	int		flag;

	dot = 0;
	flag = -1;
	k = 0;
	find_width_param(&format[i], ap, &spec);
	i++;
	while (format[i] && format[i] != 'c' && format[i] != 's' && format[i] != 'p'
			&& format[i] != 'd' && format[i] != 'i' && format[i] != 'o' &&
			format[i] != 'u' && format[i] != 'x' && format[i] != 'X' &&
			format[i] != 'f' && format[i] != '%')
	{
		if (format[i] == '.')
			dot = 1;
		i++;
	}
	if (format[i] == '\0')
	{
		one_percent_only(format);
		return ;
	}
	spec.type = format[i];
	j = i;
	i++;
	format[j--] = '\0';
	if (format[j] == 'h' || format[j] == 'l' || format[j] == 'L')
		process_specifier2(format, &j, &spec);
	else
		spec.size[0] = '\0';
	if (dot)
	{
		while (format[j] != '.')
			j--;
		if (format[j + 1] == '*')
			spec.precision = va_arg(*ap, int);
		if (format[j + 1] == '\0')
			spec.precision = 0;
		else
			spec.precision = ft_atoi((char*)(&format[j + 1]));
		format[j] = '\0';
	}
	else
		spec.precision = -1;
	while (format[j] != '%')
		j--;
	j++;
	while (format[j] == '0' || format[j] == '#' || format[j] == '+'
			|| format[j] == '-' || format[j] == ' ')
	{
		while (k < 5)
		{
			if (spec.flags[k] == format[j])
				break ;
			k++;
		}
		if (k == 5)
		{
			flag++;
			spec.flags[flag] = format[j];
		}
		j++;
		k = 0;
	}
	if (format[j] <= '9' && format[j] >= '1')
		spec.width = ft_atoi((char*)(&format[j]));
	else
		spec.width = -1;
	call_specifier(ap, &spec, flag);
}

void		process_specifier2(char *format, int *j, t_spec	*spec)
{
	if (format[j[0] - 1] == 'l' || format[j[0] - 1] == 'h')
	{
		spec->size[1] = format[j[0]];
		j[0]--;
	}
	else
		spec->size[1] = '\0';
	spec->size[0] = format[j[0]];
	format[j[0]] = '\0';
}

void		one_percent_only(char *format)
{
	int		i;
	int		j;
	char	*str;

	j = 0;
	i = ft_strlen(format) - 1;
	while (format[j] != '%')
		j++;
	str = ft_strnew(i - j);
	j = i - j - 1;
	while (format[i] != '%')
	{
		str[j] = format[i];
		j--;
		i--;
	}
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
		ret++;
	}
}

static void	ft_swapp(char *a, char *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void		print_param(char *res)
{
	int		i;
	char	*point;

	i = 0;
	point = NULL;
	if (check_0x(res, &point) && res[0] == '0')
		ft_swapp(&res[1], point);
	while (res[i])
	{
		write(1, &res[i], 1);
		i++;
		ret++;
	}
	if (zero)
	{
		write(1, "\0", 1);
		ret++;
	}
	zero = 0;
}

void		clean_struct(t_spec *spec)
{
	spec->type = '\0';
	spec->precision = -1;
	spec->width = -1;
	spec->size[0] = '\0';
	spec->flags[0] = '\0';
}

void		find_width_param(char *format, va_list *ap, t_spec *spec)
{
	int	j;

	j = 0;
	while (format[j] == '0' || format[j] == '#' || format[j] == '+'
			|| format[j] == '-')
		j++;
	if (format[j] == '*')
		spec->width = va_arg(*ap, int);
}

void		call_specifier(va_list *ap, t_spec *spec, int flag)
{
	char	*res;
	int		count;
	char	*point;

	count = -1;
	point = NULL;
	res = type_specifier(spec, ap);
	while (count < flag)
	{
		count++;
		if ((spec->flags[count] == '-' || spec->flags[count] == ' ' ||
			spec->flags[count] == '+') && spec->type != 's')
			res = precise_specifier(res, spec);
		res = flag_specifier(res, spec, count);
	}
	if (spec->precision != -1)
		res = precise_specifier(res, spec);
	if (check_minus(res, &point) && res[0] != '-' && res[0] == '0')
		ft_swapp(&res[0], point);
	if (check_plus(res, &point) && res[0] != '+' && res[0] == '0')
		ft_swapp(&res[0], point);
	if (check_space(res, &point) && spec->type != 's')
		ft_swapp(&res[0], point);
	if (spec->width != -1)
		res = width_specifier(res, spec);
	print_param(res);
	clean_struct(spec);
	free((char*)res);
}

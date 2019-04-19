#include "ft_printf.h"

void	process_specifier(char *format, va_list *ap)
{
    int		dot;
	int		j;
	t_spec  spec;
	int		k;
	int		flag;

	dot = 0;
	flag = -1;
	k = 0;
	find_width_param(&format[i], ap, &spec);
	i++;
	while (format[i] && format[i] != 'c' && format[i] != 's' && format[i] != 'p' && format[i] != 'd'
			&& format[i] != 'i' && format[i] !='o' && format[i] != 'u' && format[i] != 'x' && format[i]
			!= 'X' && format[i] != 'f' && format[i] != '%')
	{
		if (format[i] == '.')
			dot = 1;
		i++;
	}
	spec.type = format[i];
	j = i;
	i++;
	format[j--] = '\0';
	if (format[j] == 'h' || format[j] == 'l' || format[j] == 'L')
	{
		if (format[j - 1] == 'l' || format[j - 1] == 'h')
		{
			spec.size[1] = format[j];
			j--;
		}
		else
			spec.size[1] = '\0';
		spec.size[0] = format[j];
		format[j] = '\0';
	}
	else
		spec.size[0] = '\0';
	if (dot)
	{
		while(format[j] != '.')
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

void    print_param(char *res)
{
	int i;

	i = 0;
	while (res[i])
	{
		write(1, &res[i], 1);
		i++;
		ret++;
	}
}

void	find_width_param(char *format, va_list *ap, t_spec *spec)
{
	int	j;

	j = 0;
	while (format[j] == '0' || format[j] == '#' || format[j] == '+'
			|| format[j] == '-')
		j++;
	if (format[j] == '*')
		spec->width = va_arg(*ap, int);
}

void    call_specifier(va_list *ap, t_spec *spec, int flag) // что в каком порядке обрабатывать??!!!
{
	char	*res;
	int		count;

	count = -1;
	res = type_specifier(spec, ap);
	while (count < flag)
	{
		count++;
		res = flag_specifier(res, spec, count);
	}
	if (spec->precision != -1)
		res = precise_specifier(res, spec); // Непонятное что-то с  точностью и шириной. Что если точность меньше?
	if (spec->width != -1)
		res = width_specifier(res, spec);
	print_param(res);
	free((char*)res);
}
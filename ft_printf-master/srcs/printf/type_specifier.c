#include "ft_printf.h"

char    *type_specifier(t_spec *spec, va_list *ap)
{
	char	*res;

	res = NULL;
	if (spec->type == 'c')
		res = type_c(res, ap);
	if (spec->type == 's')
		res = type_s(res, ap);
	if (spec->type == 'p')
		res = type_p(res, ap, spec);
	if (spec->type == 'o' || spec->type == 'u'
		|| spec->type == 'x' || spec->type == 'X')
		res = type_ouxX(res, spec, ap);
	if (spec->type == 'f')
		res = type_f(res, ap, spec);
	if (spec->type == 'i' || spec->type == 'd')
		res = type_id(res, ap, spec);
	if (spec->type == '%')
		res = type_percent(res);
	return (res);
}

char	*type_percent(char *res)
{
	res = (char*)malloc(2 * sizeof(char));
	res[0] = '%';
	res[1] = '\0';
	return (res);
}

char	*type_ouxX(char *res, t_spec *spec, va_list *ap)
{
	unsigned long long	nb;
	int					base;

	if (spec->type == 'o')
		base = 8;
	if (spec->type == 'u')
		base = 10;
	if (spec->type == 'x')
		base = 16;
	if (spec->type == 'X')
		base = 16;
	nb = va_arg(*ap, unsigned long long);
	if (spec->size[0] == 'h' && spec->size[1] == 'h')
		res = ft_itoa_base((unsigned char)nb, base, spec);
	else if (spec->size[0] == 'h' && spec->size[1] != 'h')
		res = ft_itoa_base((unsigned short int)nb, base, spec);
	else if (spec->size[0] == 'l' && spec->size[1] == 'l')
		res = ft_itoa_base((unsigned long long)nb, base, spec);
	else if (spec->size[0] == 'l' && spec->size[1] != 'l')
		res = ft_itoa_base((unsigned long long)nb, base, spec);
	else
		res = ft_itoa_base((unsigned int)nb, base, spec);
	return (res);
}

char	*type_c(char *res, va_list *ap)
{
	char	ch;

	res = (char*)malloc(2 * sizeof(char));
	ch = va_arg(*ap, int);
	res[0] = ch;
	res[1] = '\0';
	return (res);
}

char    *type_s(char *res, va_list *ap)
{
	char	*s;
	int		len;

	s = va_arg(*ap, char*);
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
	ret[0] = '0';
	ret[1] = 'x';
	ft_strcpy(&ret[2], (char*)res);
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

char    *type_id(char *res, va_list *ap, t_spec *spec)
{
	long long	nb;
	
	nb = va_arg(*ap, long long);
	if (spec->size[0] == 'h' && spec->size[1] == 'h')
		res = ft_itoa((char)nb);
	else if (spec->size[0] == 'h' && spec->size[1] != 'h')
		res = ft_itoa((short int)nb);
	else if (spec->size[0] == 'l' && spec->size[1] == 'l')
		res = ft_itoa((long long)nb);
	else if (spec->size[0] == 'l' && spec->size[1] != 'l')
		res = ft_itoa((long)nb);
	else
		res = ft_itoa((int)nb);
	return (res);
}

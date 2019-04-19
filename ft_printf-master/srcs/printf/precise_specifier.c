#include "ft_printf.h"

char    *precise_specifier(char *res, t_spec *spec)
{
	char    *ret;
	
	if (spec->type == 'f')
		ret = f_precise(res, spec);
	if (spec->type == 's')
		ret = s_precise(res, spec);
	else
		ret = other_precise(res, spec);
	return (ret);
}

char    *other_precise(char *res, t_spec *spec)
{
	char    *ret;
	int		len;
	int		i;

	i = 0;
	len = (int)ft_strlen((char*)res);
	if (len < spec->precision)
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

char    *s_precise(char *res, t_spec *spec)
{
	char    *ret;

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

char    *f_precise(char *res, t_spec *spec)
{
   int     i;
   char    *ret;
   int     count;

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

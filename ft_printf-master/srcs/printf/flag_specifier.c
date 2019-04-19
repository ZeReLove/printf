#include "ft_printf.h"

char	*flag_specifier(char *res, t_spec *spec, int flag)
{
	if (spec->flags[flag] == '-')
		res = minus_flag(res, spec);
	if (spec->flags[flag] == '+')
		res = plus_flag(res, spec);
	if (spec->flags[flag] == '0')
		res = zero_flag(res, spec);
	if (spec->flags[flag] == '#')
		res = hash_flag(res, spec);
	if (spec->flags[flag] == ' ')
		res = space_flag(res, spec);
	return (res);
}

char	*zero_flag(char *res, t_spec *spec)
{
	int		len;
	int		i;
	char	*ret;

	i = 0;
	len = (int)ft_strlen((char*)res);
	while (spec->flags[i])
	{
		if (spec->flags[i] == '-')
			return (res);
		i++;
	}
	if (((spec->type == 'i' || spec->type == 'd' || spec->type == 'u'
		|| spec->type == 'o' || spec->type == 'X' || spec->type == 'x')
		&& spec->precision == -1) || spec->type == 'f')
	{
		if (len < spec->width)
		{
			if (!(ret = ft_strnew((int)spec->width)))
				return (NULL);
			// if (spec->flags[i] == '+')
			// 	ft_memset(ret, '0', spec->width - len + 1);
			ft_memset(ret, '0', spec->width - len);
			ft_strcpy(&ret[(spec->width) - len], (char*)res);
			free((char*)res);
			return (ret);
		}
	}
	return (res);
}

char	*minus_flag(char *res, t_spec *spec)
{
	int		len;
    char 	*ret;

    len = (int)ft_strlen((char*)res);
	if (len < spec->width)
	{
		if (!(ret = ft_strnew((int)spec->width)))
			return (NULL);
		ft_strcpy(&ret[0], (char*)res);
		ft_memset((void*)(&ret[len]), ' ', spec->width - len);
		free((char*)res);
		return (ret);
	}
	return (res);
}

int check_minus(char *res, char *point)
{
	int i;

	while(res[i])
	{
		if (res[i] == '-')
		{
			point = &res[i];
			return (1);
		}
		i++;
	}
	return (0);	
}

char	*plus_flag(char *res, t_spec *spec)
{
	int		len;
    char	*ret;
	char	*point;

    len = (int)ft_strlen((char*)res);
	if (spec->type == 'i' || spec->type == 'd' || spec->type == 'u')
	{
		if (check_minus(res, point))
		{
			 if (!(ret = ft_strnew(len + 1)))
				return (NULL);
            ret[0] = '+';
			ft_strcpy(&ret[1], (char*)res);
			free((char*)res);
			return (ret);
		}
	}
	return (res);
}

char	*hash_flag(char *res, t_spec *spec)
{
	int		len;
    char	*ret;
	
	len = (int)ft_strlen((char*)res);
	if (spec->type == 'o')
	{
		if (!(ret = ft_strnew(len + 1)))
			return (NULL);
		ret[0] = '0';
		ft_strcpy(&ret[1], (char*)res);
		free((char*)res);
		return (ret);
	}
	if (spec->type == 'x' || spec->type == 'X')
	{
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
	return (res);
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
	if (spec->type == 'd' || spec->type == 'f')
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

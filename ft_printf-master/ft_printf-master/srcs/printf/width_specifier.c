/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_specifier.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrolfe <mrolfe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 17:05:42 by mrolfe            #+#    #+#             */
/*   Updated: 2019/04/29 20:02:02 by mrolfe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*width_specifier(char *res, t_spec *spec)
{
	int		len;
	int		i;
	char	*ret;
	int		size;

	i = 0;
	len = (int)ft_strlen((char*)res);
	if (zero)
		spec->width -= 1;
	size = spec->width;
	while (spec->flags[i])
		width_specifier2(&res, spec);
	i = 0;
	if (len < spec->width)
	{
		if (!(ret = ft_strnew((int)size)))
			return (NULL);
		while (i < spec->width - len)
			ret[i++] = ' ';
		ft_strcpy(&ret[i], (char*)res);
		free((char*)res);
		return (ret);
	}
	return (res);
}

void		width_specifier2(char **res, t_spec *spec)
{
	if (spec->flags[i] == '-')
	{
		res[0] = minus_flag(res[0], spec);
		return ;
	}
	if (spec->flags[i] == '0' && (spec->type == 'o' || spec->type == 's'))
	{
		res[0] = zero_flag(res[0], spec);
		return ;
	}
	i++;
}

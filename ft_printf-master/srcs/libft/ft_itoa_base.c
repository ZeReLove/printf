#include "ft_printf.h"

static size_t		ft_digits(long long num, int base)
{
	size_t i;

	i = 0;
	if (num == 0)
		i = 1;
	while (num)
	{
		num /= base;
		i++;
	}
	return (i);
}

char	*ft_itoa_neg_base(char *str, t_spec *spec, int base)
{
	char		*ret;
	size_t		len;
	int			count;
	int			bla;

	if (spec->size[0] == 'l' && spec->size[1] == 'l')
		count = 15;
	else
		count = 7;
	if(!(ret = ft_strnew(count + 1)))
		return (NULL);
	len = ft_strlen(str);
	while (len)
	{
		ret[count] = str[len - 1];
		len--;
		count--;
	}
	while (count >= 0)
		ret[count--] = '0';
	count = 0;
	while (count <= 7)
	{
		if (ret[count] <= '9' && ret[count] >= '0')
		{
			if (base - 1 - ret[count] + 48 < 10)
				ret[count] = base - 1 - ret[count] + 48;
			else if (spec->type == 'X')
				ret[count] = base - 1 - ret[count] + 48 + 55;
			else
				ret[count] = base - 1 - ret[count] + 48 + 87;
		}
		else if (spec->type == 'X')
		{
			if (base - 1 - ret[count] + 55 < 10)
				ret[count] = base - 1 - ret[count] + 55 + 48;
			else if (spec->type == 'X')
				ret[count] = base - 1 - ret[count] + 55 + 55;
			else
				ret[count] = base - 1 - ret[count] + 55 + 87;
		}
		else
		{
			bla = base - 1 - ret[count] + 87;
			if (base - 1 - ret[count] + 87 < 10)
				ret[count] = base - 1 - ret[count] + 87 + 48;
			else if (spec->type == 'X')
				ret[count] = base - 1 - ret[count] + 87 + 65;
			else
				ret[count] = base - 1 - ret[count] + 87 + 97;
		}
		count++;
	}
	ret[--count] += 1;
	free((char*)str);
	return (ret);
}

char	*ft_itoa_base(long long num, int base, t_spec *spec)
{
	char		*str;
	long long	nb;
	size_t		i;

	nb = num;
	if (num == -9223372036854775807 - 1)
		str = "-9223372036854775808";
	i = ft_digits(num, base);
	if (num < 0 && base == 10)
		i++;
	if(!(str = ft_strnew(i)))
		return (NULL);
	if (num < 0)
		nb *= -1;
	while(i-- > 0)
	{
		if (num < 0 && i == 0 && base == 10)
			str[i] = '-';
		else if (nb % base < 10)
			str[i] = nb % base + '0';
		else if (spec->type == 'X')
			str[i] = nb % base + 55;
		else
			str[i] = nb % base + 87;      
		nb /= base;
	}
	if (num < 0 && base != 10)
		str = ft_itoa_neg_base(str, spec, base);
	return (str);
}

#include "ft_printf.h"

static size_t		ft_digits(unsigned long long num, int base)
{
	size_t	i;

	i = 0;
	if (num == 0)
		return (i = 1);
	while (num)
	{
		i++;
		num /= base;
	}
	return (i);
}

char	*ft_uitoa_base(unsigned long long num, int base, t_spec *spec)
{
	char		        *str;
	size_t		        i;

	i = ft_digits(num, base);
	if(!(str = ft_strnew(i)))
		return (NULL);
	while(i-- > 0)
	{
		if (num % base < 10)
			str[i] = num % base + '0';
		else if (spec->type == 'X')
			str[i] = num % base + 55;
		else
			str[i] = num % base + 87;      
		num /= base;
	}
	return (str);
}

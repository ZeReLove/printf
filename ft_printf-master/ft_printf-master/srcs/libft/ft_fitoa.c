#include "ft_printf.h"

static size_t		ft_digits(long double num)
{
	size_t i;
	long long	n;

	n = (int)num;
	i = 0;
	if (num == 0)
		i = 1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static size_t  dig_after_dot(long double *num, size_t *zero_count)
{
    size_t  	count;
	long long	n;
	long double	nb;

    count = 0;
	*zero_count = 0;
	n = (int)(*num);
	if (n == 0)
		(*zero_count)++;
	nb = n;
    while (nb < *num && count < 6)
    {
        *num *= 10;
		n = (int)(*num);
		if (n == 0)
			(*zero_count)++;
		nb = n;
        count++;
    }
	return (count);
}

char	*ft_fitoa(long double num)
{
	char        *str;
	long double nb;
	size_t      i;
	size_t		tmp;
	size_t		dig;
	size_t		zero_count;
	long long	n;

	nb = num;
	if (num < 0)
		nb *= -1;
    dig = dig_after_dot(&nb, &zero_count);
	n = (int)nb;
	i = ft_digits(nb) + 1 + zero_count;
	tmp = i;
	if (num < 0)
		i++;
	if(!(str = ft_strnew(i)))
		return (NULL);
	while(i-- > 0)
	{
		if (num < 0 && i == 0)
			str[i] = '-';
		if (i == tmp - dig - 1)
		{
			str[i] = '.';
			i--;
		}
		if (n == 0)
			str[i] = '0';
		else
		{
			str[i] = n % 10 + '0';
			n /= 10;
		}
	}
	return (str);
}

#include "ft_printf.h"

void	print_and_smth(const char *format, va_list *ap)
{
	char	*copy;
	size_t		len;

	len = ft_strlen(format);
	copy = ft_strnew(len);
	ft_strcpy(copy, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
			process_specifier(copy, ap);
		else
		{
			write(1, &format[i], 1);
			i++;
			ret++;
		}
	}
	free((char*)copy);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;

	ret = 0;
	va_start(ap, format);
	print_and_smth(format, &ap);
	va_end(ap);
	return (ret);
}

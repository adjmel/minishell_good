#include "minishell.h"

int	ft_putnbr_fd(int n, int fd)
{
	long long	nb;
	char		c;
    int ret;

    ret = 0;
	nb = n;
	if (nb < 0)
	{
		ret += write(fd, "-", 1);
		nb *= -1;
	}
	if (nb >= 10)
		ret += ft_putnbr_fd(nb / 10, fd);
	c = '0' + (nb % 10);
	ret += write(fd, &c, 1);
    return (ret);
}

int	ft_putchar_fd(char c, int fd)
{
	return(write(fd, &c, 1));
}

int	ft_putstr_fd(char *s, int fd)
{
    int ret;

    ret = 0;
	if (!s)
		return 0;
	while (*s)
	{
		ret += ft_putchar_fd(*s, fd);
		s++;
	}
    return(ret);
}

int	fd_printf_format(int fd, va_list ap, const char *format)
{
	int	i;

	i = 0;
	if (format[i] == 's')
		return (ft_putstr_fd(va_arg(ap, char *), fd));
	else if (format[i] == '%')
		return (ft_putchar_fd('%', fd));
	else if (format[i] == 'd')
		return (ft_putnbr_fd(va_arg(ap, int), fd));
    return(0);
}


int	fd_printf(int fd, const char *format, ...)
{
	int		i;
	va_list	ap;
	int		count;

	i = 0;
	count = 0;
	va_start(ap, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			count += fd_printf_format(fd, ap, &format[i + 1]);
			i++;
		}
		else
		{
			if (format[i] == '%' && format[i + 1] == '\0')
				break ;
			count += ft_putchar_fd(format[i], fd);
		}
		i++;
	}
	va_end(ap);
	return (count);
}
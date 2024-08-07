#include <unistd.h>
#include <stdarg.h>

void	ft_putchar(char c, int *len)
{
	write(1, &c, 1);
	*len += 1;
}

void	ft_putstr(char *s, int *len)
{
	if (!s)
	{
		write(1, "(null)", 6);
		*len += 6;
	}
	else
	{
		while (*s)
			ft_putchar(*s++, len);
	}
}

void	ft_putnbr(int n, int *len)
{
	if (n == -2147483648)
		ft_putstr("-2147483648", len);
	else if (n < 0)
	{
		ft_putchar('-', len);
		ft_putnbr(-n, len);
	}
	else if (n >= 0 && n <= 9)
		ft_putchar(n + '0', len);
	else
	{
		ft_putnbr(n / 10, len);
		ft_putnbr(n % 10, len);
	}
}

void	ft_puthex(unsigned long n, int *len)
{
	char	*base = "0123456789abcdef";

	if (n >= 16)
	{
		ft_puthex(n / 16, len);
		ft_puthex(n % 16, len);
	}
	else
		ft_putchar(base[n], len);
}

void	ft_format(char c, int *len, va_list args)
{
	if (c == 's')
		ft_putstr((char *)va_arg(args, char *), len);
	else if (c == 'd')
		ft_putnbr((long)va_arg(args, int), len);
	else if (c == 'x')
		ft_puthex((unsigned long)va_arg(args, unsigned int), len);
}

int ft_printf(const char *s, ... )
{
	int	len = 0, i = 0;
	va_list	args;

	va_start(args, s);
	while (s[i])
	{
		if ((s[i] == '%') && (s[i + 1] == 's' || s[i + 1] == 'd' || s[i + 1] == 'x'))
		{
			ft_format(s[i + 1], &len, args);
			i++;
		}
		else if (s[i] != '%')
			ft_putchar(s[i], &len);
		else
			return (len);
		i++;
	}
	va_end(args);
	return (len);
}

/*
#include <stdio.h>
int	main(void)
{
	//char *s = "";
	int n = ft_printf("saotra %x\n", 2147483648);
	int x = printf("saotra %x\n", 2147483648);
	printf("%d\n", n);
	printf("%d\n", x);
}
*/
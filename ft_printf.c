#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

static void	ft_putstr(const char *s, int *count)
{
	if (!s)
		s = "(null)";
	while (*s)
	{
		write(1, s, 1); // write one character at a time
		s++;
		(*count)++; // incremet the value at the memory address, not the pointer
	}
}

static void	ft_putnbr(int n, int *count)
{
	char	number;

	if (n == -2147483648) // check INT_MIN
	{
		ft_putstr("-2147483648", count); // calls ft_putstr
		return ;
	}
	if (n < 0) // handles negative numbers, putting signal and convert to positive
	{
		write(1, "-", 1);
		(*count)++;
		n = n * -1;
	}
	if (n > 9) // calls ft_putnbr recursively
		ft_putnbr(n / 10, count);
	number = (n % 10) + '0';
	write(1, &number, 1);
	(*count)++;
}

static void	ft_puthex(unsigned int n, int *count)
{
	char	*hex;

	hex = "0123456789abcdef"; // possible character in hex
	if (n >= 16)              // recalls ft_puthex if > 16
		ft_puthex(n / 16, count);
	write(1, &hex[n % 16], 1);
	(*count)++;
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count = 0;

	va_start(args, format); // call for variadic arguments
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			if (*format == 's')
				ft_putstr(va_arg(args, char *), &count);
			else if (*format == 'd')
				ft_putnbr(va_arg(args, int), &count);
			else if (*format == 'x')
				ft_puthex(va_arg(args, unsigned int), &count);
			else // if not a correct specifier, print the % signal and the character
			{
				write(1, "%", 1);
				write(1, format, 1);
				count = count + 2;
			}
		}
		else
		{
			write(1, format, 1);
			count++;
		}
		format++;
	}
	va_end(args); // clean-up
	return (count); // number of characters printed
}
/*
int	main(void)
{
	ft_printf("%s %d %x %y % hey %this\n", "Hello world!", 42, 42, "kkk");
	//printf("%k %this", "kkk");
}*/

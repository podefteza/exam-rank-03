/*Assignment name  : ft_printf
Expected files   : ft_printf.c
Allowed functions: malloc, free, write, va_start, va_arg, va_copy, va_end
--------------------------------------------------------------------------------

Write a function named `ft_printf` that will mimic the real printf but
it will manage only the following conversions: s,d and x.

Your function must be declared as follows:

int ft_printf(const char *, ... );

Before you start we advise you to read the `man 3 printf` and the `man va_arg`.
To test your program compare your results with the true printf.

Exemples of the function output:

call: ft_printf("%s\n", "toto");
out: toto$

call: ft_printf("Magic %s is %d", "number", 42);
out: Magic number is 42%

call: ft_printf("Hexadecimal for %d is %x\n", 42, 42);
out: Hexadecimal for 42 is 2a$

Obs: Your function must not have memory leaks. Moulinette will test that.*/

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int ft_putstr(char *s)
{
	int i = 0;
	if (!s)
		s = "(null)"; // check for null string
	while (s[i])
	{
		write(1, &s[i], 1); // write one character at a time
		i++;
	}
	return(i);
}

int	ft_putnbr(int n)
{
	int count = 0;
	int number;

	if (n == -2147483648) // check INT_MIN
		return (ft_putstr("-2147483648"));
	if (n < 0) // handles negative numbers, putting signal and convert to positive
	{
		write(1, "-", 1);
		count++;
		n = n * -1;
	}
	if (n > 9) // calls ft_putnbr recursively
		count = count + ft_putnbr(n / 10);
	number = (n % 10) + '0';
	write(1, &number, 1);
	count++;
	return(count);
}

int	ft_puthex(unsigned int n)
{
	char	hex[16] = "0123456789abcdef"; // possible characters in hex
	int count = 0;
	if (n >= 16)              			// recalls ft_puthex if > 16
		count = count + ft_puthex(n / 16);
	write(1, &hex[n % 16], 1);
	count++;
	return(count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		i;

	count = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == 's')
				count += ft_putstr(va_arg(args, char *));
			else if (str[i] == 'd')
				count += ft_putnbr(va_arg(args, int));
			else if (str[i] == 'x')
				count += ft_puthex(va_arg(args, unsigned int));
			else
			{
				write(1, "%", 1);
				write(1, &str[i], 1);
				count = count + 2;
			}
		}
		else
		{
			write(1, &str[i], 1);
			count++;
		}

		i++;
	}
	va_end(args);
	return(count);
}

/*
#ifndef REAL
# define F	r += ft_printf
#else
# define F	r += printf
#endif

int
	main(void)
{
	int	r;

	r = 0;
	F("Simple test\n");
	F("");
	F("--Format---");
	F("\n");
	F("%d\n", 0);
	F("%d\n", 42);
	F("%d\n", 1);
	F("%d\n", 5454);
	F("%d\n", (int)2147483647);
	F("%d\n", (int)2147483648);
	F("%d\n", (int)-2147483648);
	F("%d\n", (int)-2147483649);
	F("\n");
	F("%x\n", 0);
	F("%x\n", 42);
	F("%x\n", 1);
	F("%x\n", 5454);
	F("%x\n", (int)2147483647);
	F("%x\n", (int)2147483648);
	F("%x\n", (int)-2147483648);
	F("%x\n", (int)-2147483649);
	F("%x\n", (int)0xFFFFFFFF);
	F("\n");
	F("%s\n", "");
	F("%s\n", "toto");
	F("%s\n", "wiurwuyrhwrywuier");
	F("%s\n", NULL);
	F("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
	F("\n--Mixed---\n");
	F("%d%x%d%x%d%x%d%x\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
	F("-%d-%x-%d-%x-%d-%x-%d-%x-\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
	F("\n");
	F("%s%s%s%s\n", "", "toto", "wiurwuyrhwrywuier", NULL);
	F("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
	printf("written: %d\n", r);
}
*/

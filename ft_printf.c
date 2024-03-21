/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:09:22 by sranaivo          #+#    #+#             */
/*   Updated: 2024/03/11 15:10:21 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* %s */
int	print_str(va_list arg, const char **str)
{
	int		len;
	char	*s;

	len = 0;
	s = (char *)va_arg(arg, char *);
	if (!s)
	{
		write(1, "(null)", 6);
		(*str)++;
		return (6);
	}
	while (*s)
	{
		write(1, &*(s), 1);
		len++;
		s++;
	}
	(*str)++;
	return (len);
}

/* %p */
void put_str(char *s)
{
	int i = 0;
	while(s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

int	print_hex(unsigned long long nb, int length, char c)
{
	char	*base;
	char	*res;
	int		len;

	if (c == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	res = 0;
	res = malloc(sizeof(char) * (length + 1));
	if (!res)
		return (0);
	res[length] = '\0';
	len = length;
	while (nb != 0)
	{
		res[--length] = base[nb % 16];
		nb = nb / 16;
	}
	put_str(res);
	free(res);
	return (len);
}

int	print_ptr(va_list arg, const char **str)
{
	unsigned long long	ptr;
	unsigned long long	nb;
	int					len;
	int					length;

	length = 0;
	ptr = (unsigned long long)va_arg(arg, void *);
	if (!ptr)
	{
		write(1, "(nil)", 5);
		(*str)++;
		return(5);
	}
	nb = ptr;
	while (ptr != 0)
	{
		ptr = ptr / 16;
		length++;
	}
	if (nb != 0)
		write(1, "0x", 2);
	len = 2;
	len += print_hex(nb, length, 'p');
	(*str)++;
	return (len);
}
/* pppppp */

// %d %i
static void	print_nbr(long long n)
{
	char	c;

	if (n >= 0 && n <= 9)
	{
		c = n + '0';
		write(1, &c, 1);
	}
	else
	{
		print_nbr(n / 10);
		print_nbr(n % 10);
	}
}

int	print_dec(va_list arg, const char **str)
{
	long long	nb;
	int			len;

	nb = va_arg(arg, int);
	if (nb == 0)
	{
		write(1, "0", 1);
		(*str)++;
		return (1);
	}
	len = 0;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
		len = 1;
	}
	print_nbr(nb);
	(*str)++;
	while (nb)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

// %u
int print_uint(va_list arg, const char **str)
{
	unsigned int	nb;
	int			len;

	nb = va_arg(arg, unsigned int);
	if (nb == 0)
	{
		write(1, "0", 1);
		(*str)++;
		return (1);
	}
	len = 0;
	print_nbr(nb);
	(*str)++;
	while (nb)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

// %x
static int count(unsigned long long	nb)
{
	int i;

	i = 0;
	while (nb != 0)
	{
		nb = nb / 16;
		i++;
	}
	return (i);
}

int print_x(va_list arg, const char **str)
{
	long long	nb;
	int					len;
	int					length;

	length = 0;
	nb = va_arg(arg, unsigned int);
	if (nb == 0)
	{
		write(1, "0", 1);
		(*str)++;
		return (1);
	}
	length = count(nb);
	len = 0;
	len += print_hex(nb, length, 'x');
	(*str)++;
	return (len);

}

// %X
int print_X(va_list arg, const char **str)
{
	long long	nb;
	int					len;
	int					length;

	length = 0;
	nb = va_arg(arg, unsigned int);
	if (nb == 0)
	{
		write(1, "0", 1);
		(*str)++;
		return (1);
	}
	length = count(nb);
	len = 0;
	len += print_hex(nb, length, 'X');
	(*str)++;
	return (len);

}

/* %c */
static int	print_char(va_list arg, const char **str)
{
	char	c;

	c = va_arg(arg, int);
	write(1, &c, 1);
	(*str)++;
	return (1);
}

/*  %%  */
static int	print_per(const char **str)
{
	write(1, "%", 1);
	(*str)++;
	return (1);
}

static int	format(va_list arg, const char **str)
{
	if (**str == 'c')
		return (print_char(arg, str));
	else if (**str == 's')
		return (print_str(arg, str));
	else if (**str == 'p')
		return (print_ptr(arg, str));
	else if (**str == 'd')
		return (print_dec(arg, str));
	else if (**str == 'i')
		return (print_dec(arg, str));
	else if (**str == 'u')
		return (print_uint(arg, str));
	else if (**str == 'x')
		return (print_x(arg, str));
	else if (**str == 'X')
		return (print_X(arg, str));
	else if (**str == '%')
		return (print_per(str));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	int		len;

	va_start(arg, str);
	len = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			len += format(arg, &str);
		}
		else
		{
			write(1, &(*str), 1);
			len++;
			str++;
		}
	}
	va_end(arg);
	return (len);
}

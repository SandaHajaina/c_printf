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
//#include <stdio.h>

/* %c */
int print_char(va_list arg, const char *str)
{
	char c;

	c = va_arg(arg, int);
	write(1, &c, 1);
	str = str + 2;
	return (1);
}

/* %s */
int	print_str(va_list arg, const char *str)
{
	int	len;
	char *s;

	len = 0;
	s = va_arg(arg, char *);
	while(*s)
	{
		write(1, &*(s), 1);
		len++;
		s++;
	}
	str += 2;
	return (len);
}

// %d
static void	print_nbr(long n)
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

int print_dec(va_list arg, const char *str)
{
	long	nb;
	char	minus;
	int		len;

	nb = va_arg(arg, int);
	len = 0;
	if (nb < 0)
	{
		minus = '-';
		write(1, &minus, 1);
		nb = -nb;
		len = 1;
	}
	print_nbr(nb);
	str += 2;
	while(nb)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

/*  %%  */
int print_per(const char *str)
{
	write(1, "%", 1);
	str += 2;
	return (1);
}

static int format(va_list arg, const char *str)
{
	if(*str == 'c')
		return (print_char(arg, str));
	else if (*str == 's')
		return (print_str(arg, str)); /*
	else if (*str == 'p')
		return (print_ptr()); */
	else if (*str == 'd')
		return (print_dec(arg, str)); 
	else if (*str == 'i')
		return (print_dec(arg, str));
	else if (*str == 'u')
		return (print_dec(arg, str));
	else if (*str == 'x')
		return (print_dec(arg, str));
	else if (*str == 'X')
		return (print_dec(arg, str));
	else if (*str == '%')
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
			len += format(arg, str);
		}
		else
		{
			write(1, &(*str), 1);
			len++;
		}
		str++;
	}
	va_end(arg);
	return (len);
}

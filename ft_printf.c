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

#include "printf.h"
//#include <stdio.h>
/*
static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
} */

int print_char(va_list arg, const char *str)
{
	char c;

	c = va_arg(arg, int);
	write(1, &c, 1);
	str = str + 2;
	return (1);
}

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
	str+= 2;
	return (len);
}

int print_dec(va_list arg, const char *str)
{

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
		return (print_dec()); /*
	else if (*str == 'i')
		return (print_int());
	else if (*str == 'u')
		return (print_uint());
	else if (*str == 'x')
		return (print_hex());
	else if (*str == 'X')
		return (print_uhex());
	else if (*str == '%')
		return (print_per()); */
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

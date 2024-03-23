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
		return (print_xx(arg, str));
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

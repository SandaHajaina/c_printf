/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:41:18 by sranaivo          #+#    #+#             */
/*   Updated: 2024/03/23 14:41:20 by sranaivo         ###   ########.fr       */
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
static void	put_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

static int	print_hex(unsigned long long nb, int length, char c)
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
		return (5);
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

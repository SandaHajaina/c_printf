/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:07:36 by sranaivo          #+#    #+#             */
/*   Updated: 2024/03/22 12:07:39 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

static int	count(unsigned long long nb)
{
	int	i;

	i = 0;
	while (nb != 0)
	{
		nb = nb / 16;
		i++;
	}
	return (i);
}

int	print_x(va_list arg, const char **str)
{
	long long	nb;
	int			len;
	int			length;

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
int	print_xx(va_list arg, const char **str)
{
	long long	nb;
	int			len;
	int			length;

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 14:38:09 by sranaivo          #+#    #+#             */
/*   Updated: 2024/03/23 14:38:16 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
int	print_uint(va_list arg, const char **str)
{
	unsigned int	nb;
	int				len;

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

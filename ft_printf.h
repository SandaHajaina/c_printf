/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sranaivo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:43:52 by sranaivo          #+#    #+#             */
/*   Updated: 2024/03/16 17:37:38 by sranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	print_str(va_list arg, const char **str);
int	print_ptr(va_list arg, const char **str);
int	print_dec(va_list arg, const char **str);
int	print_uint(va_list arg, const char **str);
int	print_x(va_list arg, const char **str);
int	print_xx(va_list arg, const char **str);

#endif

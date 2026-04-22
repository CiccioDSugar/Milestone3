/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:19:57 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/05/13 12:04:56 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	check_format(const char *format, va_list args, int fd)
{
	int	i;

	i = 0;
	if (*format == '%')
		i += ft_putchar_fd('%', fd);
	else if (*format == 'c')
		i += ft_putchar_fd(va_arg(args, int), fd);
	else if (*format == 'p')
		i += ft_forpointer(va_arg(args, void *), fd);
	else if (*format == 's')
		i += ft_putstr_fd(va_arg(args, char *), fd);
	else if (*format == 'd' || *format == 'i')
		i += ft_putnbr_fd(va_arg(args, int), fd);
	else if (*format == 'u')
		i += ft_unsigned_putnbr(va_arg(args, unsigned int), fd);
	else if (*format == 'x' || *format == 'X')
		i += ft_hexadecimal(va_arg(args, unsigned int), *format, fd);
	return (i);
}

int	ft_printf(int fd, const char *format, ...)
{
	int		count;
	va_list	args;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '\0')
				return (count);
			count += check_format(format, args, fd);
		}
		else
			count += ft_putchar_fd(*format, fd);
		format++;
	}
	va_end(args);
	return (count);
}

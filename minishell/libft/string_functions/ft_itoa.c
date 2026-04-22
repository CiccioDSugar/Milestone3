/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:58:16 by gpirozzi          #+#    #+#             */
/*   Updated: 2024/11/22 17:58:18 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
//#include <stdio.h>
static int	get_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*fstrcpy(char *str, char *s2)
{
	int	i;

	i = 0;
	while (s2[i] != '\0')
	{
		str[i] = s2[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*int_min(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 12);
	if (!str)
		return (NULL);
	fstrcpy(str, "-2147483648");
	return (str);
}

static char	*fget_itoa(char *str, int i, int n)
{
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	int		i;
	char	*str;

	len = get_len(n);
	i = len - 1;
	if (n == -2147483648)
		return (int_min());
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	fget_itoa(str, i, n);
	str[len] = '\0';
	return (str);
}

/*int	main(void)
{
//modulo 10 per prendere ultima cifra + 48 per convertire in stringa
//i-- perche parto dal fondo del numero per poter prendere tutte le cifre
//, se partissi da i = 0 perderei dei numeri
	printf("%s\n", ft_itoa(0));
	printf("%s\n", ft_itoa(1));
	printf("%s\n", ft_itoa(-1));
	printf("%s\n", ft_itoa(100));
	printf("%s\n", ft_itoa(-100));
	printf("%s\n", ft_itoa(1000));
	printf("%s\n", ft_itoa(-1000));
	printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(2147483647));
	printf("%s\n", ft_itoa(999999999));
	printf("%s", ft_itoa(-999999999));
}*/

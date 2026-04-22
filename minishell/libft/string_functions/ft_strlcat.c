/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:42:17 by gpirozzi          #+#    #+#             */
/*   Updated: 2024/11/19 17:42:20 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
//#include <stdio.h>
static	size_t	len(const char *str)
{
	size_t	j;

	j = 0;
	while (str[j] != '\0')
		j++;
	return (j);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	k;
	size_t	len_dst;
	size_t	len_src;

	k = 0;
	len_dst = len(dst);
	len_src = len(src);
	i = len_dst;
	if (len_dst >= size || size < 1)
		return (size + len_src);
	while (src[k] != '\0' && i < size - 1)
	{
		dst[i] = src[k];
		i++;
		k++;
	}
	dst[i] = '\0';
	return (len_dst + len_src);
}
/*int	main()
{
	char d[]="ciaoe";
	char s[]="mondo";
	printf("%zu", ft_strlcat(d, s, 9));
	printf("%s", d);
}*/

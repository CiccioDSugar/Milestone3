/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:48:22 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/04/09 16:16:34 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
	if (i != n)
		return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
	return (0);
}
/*int	main(void)
{
	const char s1[] = "ciao";
	const char s2[] = "ciao";
	int x = ft_strncmp(s1, s2, 10);
	printf("%d" , x);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:17:07 by gpirozzi          #+#    #+#             */
/*   Updated: 2024/11/19 19:17:09 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
//#include <stdio.h>
char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	k;

	k = (char) c;
	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	while (i >= 0)
	{
		if (s[i] == k)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
/*int	main()
{
	const char s[] = "\0";
	printf("%s", ft_strchr(s, 'f'));
}*/

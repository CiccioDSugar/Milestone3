/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:59:13 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/04/09 16:18:09 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	k;

	k = (char) c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == k)
			return ((char *)&s[i]);
		i++;
	}
	if (k == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
/*int	main()
{
	const char s[] = "";
	printf("%s", ft_strchr(s, '\0'));
}*/

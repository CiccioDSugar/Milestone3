/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:08:32 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/04/18 12:26:05 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stddef.h>

char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3)
{
	char	*joined;
	char	*rejoined;

	joined = ft_strjoin(s1, s2);
	rejoined = ft_strjoin(joined, s3);
	free(joined);
	return (rejoined);
}

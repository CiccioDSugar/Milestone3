/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:22:02 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/04/09 16:22:20 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_dup_matrix(char **matrix, char **dup_matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	dup_matrix = malloc(sizeof(char *) * (i + 1));
	if (!dup_matrix)
	{
		free(dup_matrix);
		return (NULL);
	}
	i = 0;
	while (matrix[i] != NULL)
	{
		dup_matrix[i] = ft_strdup(matrix[i]);
		if (!dup_matrix)
			return (free(dup_matrix), NULL);
		i++;
	}
	dup_matrix[i] = NULL;
	return (dup_matrix);
}

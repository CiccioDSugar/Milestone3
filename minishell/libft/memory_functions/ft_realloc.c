/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:56:21 by fzuccaro          #+#    #+#             */
/*   Updated: 2025/05/13 12:04:20 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_realloc_mtx(char **matrix, size_t new_size, size_t old_size)
{
	char	**new_matrix;
	size_t	i;

	i = 0;
	new_matrix = malloc(sizeof(char *) * (new_size + 1));
	if (!new_matrix)
		return (NULL);
	while (i < old_size && matrix[i] != NULL)
	{
		new_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	new_matrix[i] = NULL;
	ft_free_matrix(matrix);
	return (new_matrix);
}

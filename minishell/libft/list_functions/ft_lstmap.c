/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:14:54 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/04/09 15:57:19 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	void	*new_content;

	new_lst = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (new_node == NULL)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, new_node);
		lst = lst->next;
	}
	return (new_lst);
}
/*void	del(void *content)
{
	if (content)
		free(content);
}
void	*f(void *content)
{
	int i = 0;
	char *str = (char *)content;
	char *final = ft_strdup(str);
	while (final[i])
	{
		final[i] -= 32;
		i++;
	}
	return (final);
}
int	main()
{
	t_list *node1 =ft_lstnew(ft_strdup("ciao"));
	t_list *node2 =ft_lstnew(ft_strdup("mondo"));
	t_list *node3 = ft_lstnew(ft_strdup("indiano"));
	node1->next = node2;
	node2->next = node3;
	t_list *new_list = ft_lstmap(node1, f, del);
	t_list	*temp = node1;
	while(temp)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	temp = new_list;
	while(temp)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:12:52 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/05 10:25:19 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *add)
{
	if (lst && add)
	{
		add->next = *lst;
		*lst = add;
	}
}

// int main(void)
// {
// 	int			i = 1;
// 	int			j = 2;
// 	int			k = 3;
// 	int			l = 4;
// 	t_list		*current;
// 	t_list		*node1;
// 	t_list		*node2;
// 	t_list		*node3;
// 	t_list		*node4;

// 	node1 = ft_lstnew(&i);
// 	node2 = ft_lstnew(&j);
// 	node3 = ft_lstnew(&k);
// 	node4 = ft_lstnew(&l);
// 	current = node1;

// 	node1->next = node2;
// 	node2->next = node3;
// 	ft_lstadd_front(&current, node4);
// 	while(current)
// 	{
// 		printf("%d\n", *(int *)current->content);
// 		current = current->next;
// 	}
// }
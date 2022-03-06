/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 21:36:35 by hakim             #+#    #+#             */
/*   Updated: 2022/03/06 21:36:37 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == 0)
		return (lst);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst == 0 || new == 0)
		return ;
	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	new->prev = ft_lstlast(*lst);
	new->prev->next = new;
}

t_list	*ft_lstnew(char *line)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == 0)
		return (0);
	new->line = line;
	new->next = 0;
	new->prev = 0;
	return (new);
}

void	delete_node(t_list *lst)
{
	if (lst->prev == NULL && lst->next == NULL)
		;
	else if (lst->prev == NULL)
		lst->next->prev = NULL;
	else if (lst->next == NULL)
		lst->prev->next = NULL;
	else
	{
		lst->prev->next = lst->next;
		lst->next->prev = lst->prev;
	}
	free(lst->line);
	lst->line = 0;
	free(lst);
	lst = 0;
}

void	*ft_free_lst(t_list *lst)
{
	t_list	*temp;

	while (lst->next != NULL)
	{
		temp = lst->next;
		delete_node(lst);
		lst = temp;
	}
	return (NULL);
}

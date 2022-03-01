/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:53:50 by hakim             #+#    #+#             */
/*   Updated: 2022/03/01 17:53:52 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_list
{
	struct s_list	*next;
	char			*line;
}	t_list;

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
	ft_lstlast(*lst)->next = new;
}

t_list	*ft_lstnew(char *line)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == 0)
		return (0);
	new->line = line;
	new->next = 0;
	return (new);
}

void	ft_printlist(t_list *lst)
{
	if (lst == 0)
		return ;
	while (lst != 0)
	{
		printf("%s\n", lst->line);
		lst = lst->next;
	}
}

t_list	*envp_to_ours(char **envp)
{
	t_list	*head;
	int 	index;

	index = 0;
	head = ft_lstnew(envp[index++]);
	while (envp[index] != NULL)
		ft_lstadd_back(&head, ft_lstnew(envp[index++]));
	return (head);
}

//int main(int ac, char **av, char **envp)
//{
//	t_list *our_env;
//
//	our_env = envp_to_ours(envp);
//	ft_printlist(our_env);
//}


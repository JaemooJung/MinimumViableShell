/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemoojung <jaemoojung@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:53:50 by hakim             #+#    #+#             */
/*   Updated: 2022/03/08 23:40:14 by jaemoojung       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*envp_to_ours(char **envp)
{
	t_list	*head;
	t_list	*cur;
	char	*line;
	int		index;

	index = 0;
	line = ft_strdup(envp[index++]);
	if (line == NULL)
		return (NULL);
	head = ft_lstnew(line);
	if (head == NULL)
		return (ft_free_str(line));
	cur = head;
	while (envp[index] != NULL)
	{
		line = ft_strdup(envp[index++]);
		if (line == NULL)
			return (ft_free_lst(head));
		ft_lstadd_back(&head, ft_lstnew(line));
		cur = cur->next;
		if (cur == NULL)
			return (ft_free_lst(head));
	}
	return (head);
}
// when return NULL, should minishell_exit with error message??

char	*get_value(t_list *env, char *key)
{
	size_t	len;

	while (env != NULL)
	{
		len = ft_strlen(key);
		if (ft_strncmp(env->line, key, len) == 0 && env->line[len] == '=')
			return (env->line + len + 1);
		env = env->next;
	}
	return (NULL);
}

char	**to_vector(t_list *env)
{
	size_t	size;
	size_t	index;
	char	**envp;

	size = ft_lstsize(env);
	envp = malloc(sizeof(char *) * (size + 1));
	if (envp == NULL)
		return (NULL);
	index = 0;
	while (index < size)
	{
		envp[index++] = env->line;
		env = env->next;
	}
	envp[size] = NULL;
	return (envp);
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

/*int main(int ac, char **av, char **envp)
{
	t_list *our_env;
	char **hihi;

	our_env = envp_to_ours(envp);
	printf("%s\n", our_env);
//	our_env = ft_lstnew("aa");
//	ft_lstadd_back(&our_env, ft_lstnew("bb"));
//	ft_lstadd_back(&our_env, ft_lstnew("cc"));
//	ft_lstadd_back(&our_env, ft_lstnew("dd"));
//	ft_lstadd_back(&our_env, ft_lstnew("ee"));
//	ft_printlist(our_env);
//	ft_printlist(our_env);
}*/
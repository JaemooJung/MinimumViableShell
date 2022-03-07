/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:34:44 by hakim             #+#    #+#             */
/*   Updated: 2022/03/01 14:34:44 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_exported_quoted(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] != '=')
			write(STDOUT_FILENO, &str[index], 1);
		else
		{
			write(STDOUT_FILENO, &str[index], 1);
			write(STDOUT_FILENO, "\"", 1);
		}
		++index;
	}
	write(STDOUT_FILENO, "\"\n", 2);
}

static int	ft_strncmp_for_sort(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	while ((index < n) && (s1[index] != '\0' || s2[index] != '\0'))
	{
		if (s1[index] == '=')
			return (0 - (unsigned char)s2[index]);
		else if (s2[index] == '=')
			return ((unsigned char)s1[index]);
		if (s1[index] != s2[index])
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
		index++;
	}
	return (0);
}

static t_stat	print_sorted(t_list *env)
{
	t_list	*temp;
	t_list	*cur;

	temp = copy_list(env);
	if (temp == NULL)
		return (MALLOC_ERR);
	sort_list(temp, ft_strncmp_for_sort);
	cur = temp;
	while (cur != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		if (ft_strchr(cur->line, '=') != NULL)
			print_exported_quoted(cur->line);
		else
			ft_putendl_fd(cur->line, STDOUT_FILENO);
		cur = cur->next;
	}
	ft_free_lst(temp);
	return (SUCCESS);
}
// 인자 검사하고 ->
//	‘=‘이 있을 때	키가 없으면 더해주고 이미 키가 존재하면 대체해준다.
//	‘=‘이 없을 때	키가 없으면 더해주고 이미 키가 존재하면 패스

t_stat	mvs_export(char **chunk, t_list *env)
{
	int		index;
	t_stat	exit_status;

	index = 0;
	exit_status = SUCCESS;
	while (chunk[index] != NULL)
		++index;
	if (index == 1)
		exit_status = print_sorted(env);
	else
	{
		index = 1;
		while (chunk[index] != NULL)
		{
			if (append_to_env(env, chunk[index]) != SUCCESS)
				exit_status = FAILURE;
			++index;
		}
	}
	return (exit_status);
}

/*int main(int ac, char **av, char **envp)
{
	t_list	*env = envp_to_ours(envp);//ft_lstnew(NULL);//envp_to_ours(envp);
	char	*chunk[8];
	char	*chunk2[2];

	chunk[0] = "export";
	chunk[1] = "a";
	chunk[2] = "a=123";
	chunk[3] = "a";
	chunk[4] = "a";
	chunk[5] = "t=123";
	chunk[6] = "a12";
	chunk[7] = NULL;
	mvs_export(chunk, env);
	chunk2[0] = "export";
	chunk2[1] = NULL;
	mvs_export(chunk2, env);
	return (0);
}*/

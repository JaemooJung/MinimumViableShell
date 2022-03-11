/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:34:31 by hakim             #+#    #+#             */
/*   Updated: 2022/03/01 14:34:33 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	chdir_to_home(t_list *env)
{
	char	*homepath;
	int		status;

	homepath = get_value(env, "HOME");
	status = chdir(homepath);
	if (status < 0)
	{
		ft_print_error("cd", NULL, "HOME not set");
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	chdir_to_arg(char *path)
{
	int		status;

	status = chdir(path);
	if (status < 0)
	{
		ft_print_error("cd", path, strerror(errno));
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	manage_pwds(char *pwd, t_list *env)
{
	char	*temp;

	temp = ft_strjoin("OLDPWD=", pwd);
	if (temp == NULL)
		return (FAILURE);
	append_to_env(env, temp);
	ft_free_str(pwd);
	ft_free_str(temp);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (FAILURE);
	temp = ft_strjoin("PWD=", pwd);
	if (temp == NULL)
		return (FAILURE);
	append_to_env(env, temp);
	ft_free_str(temp);
	return (SUCCESS);
}

int	mvs_cd(char **chunk, t_list *env)
{
	int	exit_status;
	char	*pwd;
	char	*temp;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (FAILURE);
	if (chunk[1] == NULL)
		exit_status = chdir_to_home(env);
	else
		exit_status = chdir_to_arg(chunk[1]);
	if (exit_status == SUCCESS)
		exit_status = manage_pwds(pwd, env);
	ft_free_str(pwd);
	return (exit_status);
}

/*
int main(int ac, char **av, char **envp)
{
	t_list	*env = envp_to_ours(envp);
	char	*chunk[3];
	char	*chunk2[3];
	char *prevDir = getcwd(NULL, 0);
	if (prevDir == NULL)
	{
		strerror(errno);
		return (FAILURE);
	}
	printf("%s\n", prevDir);
	free(prevDir);
	prevDir = NULL;
	chunk2[0] = "unset";
	chunk2[1] = "HOME";
	chunk2[2] = NULL;
	mvs_env(chunk, env);
	mvs_unset(chunk2, env);
	chunk[0] = "export";
	chunk[1] = NULL;
	chunk[2] = NULL;
	mvs_cd(chunk, env);
	char *currentDir = getcwd(NULL, 0);
	if (currentDir == NULL)
	{
		strerror(errno);
		return (FAILURE);
	}
	printf("%s\n", currentDir);
	free(currentDir);
	currentDir = NULL;
	mvs_export(chunk, env);
//	return (0);
}*/

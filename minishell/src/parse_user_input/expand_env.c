#include "minishell.h"

int	get_quote_strlen(const char *str, char quote)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != quote)
		i++;
	if (str[i] == '\0')
		return (UNCLOSED_QUOTE);
	return (i);
}

int	join_unquoted_string(char **str, char *unquoted, int q_idx, int q_len)
{
	char	*fore;
	char	*back;
	char	*fore_and_unquoted;
	char	*full_str;
	int		rtn_len;

	fore = ft_strdup(*str);
	fore[q_idx] = '\0';
	back = ft_strdup(*str + q_idx + q_len + 1);
	fore_and_unquoted = ft_strjoin(fore, unquoted);
	full_str = ft_strjoin(fore_and_unquoted, back);
	rtn_len = ft_strlen(fore_and_unquoted);
	ft_free_str(fore);
	ft_free_str(back);
	ft_free_str(fore_and_unquoted);
	ft_free_str(*str);
	ft_free_str(unquoted);
	*str = full_str;
	return (rtn_len);
}

int	unquote_str(char **str_to_expand, int i, t_list *our_env, int exit_status)
{
	char	*quoted_str;
	int		quote_str_len;
	int		j;

	quote_str_len = get_quote_strlen(*str_to_expand + i, (*str_to_expand)[i]);
	if (quote_str_len == UNCLOSED_QUOTE)
		return (UNCLOSED_QUOTE);
	quoted_str = ft_substr(*str_to_expand, i + 1, quote_str_len - 1);
	if (quoted_str == NULL)
		return (UNQUOTE_MALLOC_FAIL);
	if ((*str_to_expand)[i] == '\"')
	{
		j = 0;
		while (quoted_str[j])
		{
			if (quoted_str[j] == '$')
				compare_and_join_env(&quoted_str, our_env, j, exit_status);
			j++;
		}
	}
	return (join_unquoted_string(str_to_expand, quoted_str, i, quote_str_len));
}

int	expand_env_in_str_and_unquote(char **str, t_list *our_env, int exit_status)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && (*str)[i + 1] != '\0')
			compare_and_join_env(str, our_env, i, exit_status);
		else if ((*str)[i] == '\"' || (*str)[i] == '\'')
		{
			i = unquote_str(str, i, our_env, exit_status);
			if (i < 0)
				return (i);
			continue ;
		}
		i++;
	}
	return (0);
}

int	expand_env(t_ast_node *tree, t_list *our_env, int exit_status)
{
	int	rtn_val;

	if (tree == NULL)
		return (0);
	if (tree->content != NULL)
	{
		rtn_val = expand_env_in_str_and_unquote(&(tree->content), our_env, exit_status);
		if (rtn_val < 0)
			return (rtn_val);
	}
	rtn_val = expand_env(tree->left, our_env, exit_status);
	if (rtn_val < 0)
		return (rtn_val);
	rtn_val = expand_env(tree->right, our_env, exit_status);
	if (rtn_val < 0)
		return (rtn_val);
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_list	*our_env;
// 	char	*env_string;
// 	char	*env_content;
// 	char	*input;
// 	int		rtn_val;

// 	our_env = envp_to_ours(envp);
// 	input = ft_strdup(argv[1]);
// 	rtn_val = expand_env_in_str_and_unquote(&input, our_env);
// 	if (rtn_val == UNCLOSED_QUOTE)
// 		printf("Unclosed quote\n");
// 	printf("final result: [%s]\n", input);
// 	ft_free_str(input);
// 	ft_free_lst(our_env);
// 	return (0);
// }

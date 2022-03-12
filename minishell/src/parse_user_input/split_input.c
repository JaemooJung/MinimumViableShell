#include "minishell.h"

static bool	m_is_sign(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

int get_sign_len(char const *input)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (2);
		else
			return (1);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (2);
		else
			return (1);
	}
	else if (input[i] == '|')
		return (1);
	return (len);
}

int	get_token_len(char const *input)
{
	int		i;
	bool	is_double_quote_on;
	bool	is_single_quote_on;

	i = 0;
	is_double_quote_on = false;
	is_single_quote_on = false;
	if (m_is_sign(input[i]))
		return (get_sign_len(input));
	while (input[i] != '\0')
	{
		if (input[i] == '"')
			is_double_quote_on = !is_double_quote_on;
		else if (input[i] == '\'')
			is_single_quote_on = !is_single_quote_on;
		else if (input[i] == ' ' && (!is_double_quote_on && !is_single_quote_on))
			break ;
		else if (m_is_sign(input[i]) && (!is_double_quote_on && !is_single_quote_on))
			break ;
		i++;
	}
	if (is_double_quote_on || is_single_quote_on)
		return (-1);
	return (i);
}

int	split_input(char const *input, t_list **splitted)
{
	t_list	*node;
	int		token_len;

	while (*input == ' ')
		input++;
	while (*input != '\0')
	{
		token_len = get_token_len(input);
		if (token_len == -1)
			return (UNCLOSED_QUOTE);
		node = ft_lstnew(ft_substr(input, 0, token_len));
		if (node == NULL || node->line == NULL)
			return (MALLOC_ERR);
		ft_lstadd_back(splitted, node);
		input += token_len;
		while (*input == ' ')
			input++;
	}
	return (0);
}

// int	main(int ac, char **av)
// {
// 	t_list	*result;
// 	t_list	*temp;

// 	if (ac != 2)
// 		return (0);
// 	result = split_input(av[1]);
// 	if (result == NULL)
// 	{
// 		printf("Error: unclosed quotation\n");
// 		return (0);
// 	}
// 	temp = result;
// 	while (temp != NULL)
// 	{
// 		printf("%s\n", temp->line);
// 		temp = temp->next;
// 	}
// 	ft_free_lst(result);
// 	return (0);
// }

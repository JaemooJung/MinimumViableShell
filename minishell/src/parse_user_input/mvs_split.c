#include "minishell.h"

static int	wordcount(char const *s, int i)
{
	int		count;
	char	flag;

	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && \
			(m_is_space(s[i]) == true && m_is_quote(s[i]) == false))
			++i;
		++count;
		if (m_is_quote(s[i]) == true)
		{
			flag = s[i++];
			while (s[i] != flag && s[i] != '\0')
				++i;
			if (s[i] != '\0')
				++i;
		}
		else
			while (s[i] != '\0' && \
			(m_is_space(s[i]) == false && m_is_quote(s[i]) == false))
				++i;
	}
	return (count);
}

static int	get_word_size(const char *s, int i)
{
	char	flag;

	while (m_is_space(s[i]) == true)
		i++;
	if (m_is_quote(s[i]) == true)
	{
		flag = s[i++];
		while (s[i] != flag)
			++i;
		++i;
	}
	else
		while ((m_is_space(s[i]) == false && m_is_quote(s[i]) == false)
			&& s[i] != '\0')
			++i;
	return (i);
}

static int	put_word(const char *src, char *dst, int i)
{
	int		srcdex;
	int		dstdex;
	char	flag;

	srcdex = i;
	dstdex = 0;
	if (m_is_quote(src[srcdex]) == true)
	{
		flag = src[srcdex];
		dst[dstdex++] = src[srcdex++];
		while (src[srcdex] != flag && src[srcdex] != '\0')
			dst[dstdex++] = src[srcdex++];
		dst[dstdex++] = src[srcdex++];
	}
	else
		while (src[srcdex] != '\0' && (m_is_space(src[srcdex]) == false \
			&& m_is_quote(src[srcdex]) == false))
			dst[dstdex++] = src[srcdex++];
	dst[dstdex] = '\0';
	return (srcdex);
}

static void	do_split(const char *s, char **words, int size)
{
	int		i;
	int		wordex;

	i = 0;
	wordex = 0;
	while (s[i] != '\0' && wordex < size)
	{
		while (s[i] != '\0' && \
			(m_is_space(s[i]) == true && m_is_quote(s[i]) == false))
			i++;
		words[wordex] = malloc(sizeof(char) * get_word_size(s, i));
		if (words[wordex] == 0)
			return (ft_free_split(words, wordex));
		i = put_word(s, words[wordex], i);
		wordex++;
	}
}

char	**mvs_split(char const *s)
{
	char	**words;
	int		size;

	if (s == NULL)
		return (NULL);
	size = wordcount(s, 0);
	words = malloc(sizeof(char *) * (size + 1));
	if (words == NULL)
		return (NULL);
	words[size] = NULL;
	do_split(s, words, size);
	return (words);
}

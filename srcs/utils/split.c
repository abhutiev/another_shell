#include "../../includes/minishell.h"

static size_t	ft_word_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static size_t	ft_word_count(char const *s, char c)
{
	size_t	i;
	size_t	counter;

	counter = 0;
	i = 0;
	while (s[i + 1] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c))
			counter++;
		i++;
	}
	if (s[i + 1] == '\0' && s[i] != c)
		counter++;
	return (counter);
}

static char	**ft_free_all(char ***result, size_t counter)
{
	size_t	i;

	if (counter > 0)
		i = counter - 1;
	else
		i = 0;
	while (i >= 0)
	{
		free(*result[i]);
		i--;
	}
	free(*result);
	return (NULL);
}

static char	**ft_if_empty_string(void)
{
	char	**result;

	result = (char **)malloc(sizeof(char *) * 1);
	result[0] = NULL;
	return (result);
}

char	**split(char *s, char c)
{
	size_t	i;
	char	**result;
	size_t	counter;

	i = 0;
	counter = 0;
	if (s == NULL)
		return (NULL);
	if (ft_strlen(s) == 0)
		return (ft_if_empty_string());
	result = (char **)ft_calloc((ft_word_count(s, c) + 100), sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (i < ft_strlen(s))
	{
		if (s[i++] != c)
		{
			result[counter] = ft_substr(s, i - 1, ft_word_len(s + i - 1, c));
			if (result[counter] == NULL)
				return (ft_free_all(&result, counter));
			i = i - 1 + ft_word_len(s + i - 1, c);
			counter++;
		}
	}
	return (result);
}

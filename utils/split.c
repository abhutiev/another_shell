/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 20:27:47 by gdoge             #+#    #+#             */
/*   Updated: 2020/11/05 14:09:28 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	How the function ft_split works:
**	1)	Check if argument is valid (!= NULL).
**	2)	Check if string passed as an argument is not empty
**		2.1)	If it's empty - we return pointer on NULL-pointer, that was
**				built by ft_if_empty_string.
**	3)	Allocation of memory for amount of words, counted by ft_word_count
**		+ one for NULL - pointer.
**		3.1)	If memory was not allocated, return NULL-pointer.
**	4)	Go through the line in increments of one element.
**		4.1)	If we faced with non - separator element, grab word.
**			4.1.1)	Try to grab whole word with ft_substr
**					(length was counted with ft_word_len).
**			4.1.2)	If memory was non allocated, we should free all memory,
**					that was allocated earlier with ft_free_all
**					and return NULL - pointer.
**			4.1.3)	Increase "i" to end of grabbed word;
**			4.1.4)	Increase counter for next "potential" word.
**	5)	Return pointer on successfully built words.
*/

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

static char		**ft_free_all(char ***result, size_t counter)
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

static char		**ft_if_empty_string(void)
{
	char	**result;

	result = (char **)malloc(sizeof(char *) * 1);
	result[0] = NULL;
	return (result);
}

char			**split(char *s, char c)
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
	result = (char **)malloc(sizeof(char *) * (ft_word_count(s, c) + 1));
	if (result == NULL)
		return (NULL);
	result[ft_word_count(s, c)] = NULL;
	while (i < ft_strlen(s))
		if (s[i++] != c)
		{
			result[counter] = ft_substr(s, i - 1, ft_word_len(s + i - 1, c));
			if (result[counter] == NULL)
				return (ft_free_all(&result, counter));
			i = i - 1 + ft_word_len(s + i - 1, c);
			counter++;
		}
	return (result);
}

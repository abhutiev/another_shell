/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 01:35:38 by gdoge             #+#    #+#             */
/*   Updated: 2020/11/05 09:53:43 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	How the function ft_substr.c works:
**	1)	Check if argument s is valid (!= NULL).
**	2)	Try to allocate memory for resulting string.
**		2.1)	If memory was not allocated, return NULL-pointer.
**	3)	Check, if index of first element to copy is more than a length of
**															string we handle.
**		3.1)	If it's more - return pointer on allocated memory.
**	4)	Go through the both lines in increments of one element and copy
**		elements from number "start" in string passed as an argument
**		to substring.
**	5)	NULL-terminating of our substring.
**	6)	Return pointer on first character of built string.
*/

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	substring = (char *)malloc(sizeof(char) * len + 1);
	if (substring == NULL)
		return (NULL);
	if (start > ft_strlen((char *)s))
		return (substring);
	while (i < len)
	{
		substring[i] = s[i + start];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

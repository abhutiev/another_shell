/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 16:17:06 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/17 16:17:07 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
**	How the function ft_strjoin.c works:
**	1)	Check if argument s is valid (!= NULL).
**	2)	Calculate summ of lengths of strings passed as an arguments.
**	3)	Try to allocate memory for resulting string.
**		2.1)	If memory was not allocated, return NULL-pointer.
**	4)	Go through the first line in increments of one element and copy
**		elements to new string.
**	5)	Go through the second line in increments of one element and copy
**		elements to new string.
**	6)	NULL-terminating of our substring.
**	7)	Return pointer on first character of built string.
*/

char			*strjoin_for_bin(char const *s1, char const *s2)
{
	size_t	new_size;
	char	*new_str;
	size_t	i;
	size_t	j;

	if (s1 == NULL)
		return (NULL);
	new_size = ft_strlen((char *)s1) + ft_strlen((char *)s2) - 1;
	new_str = (char *)malloc(sizeof(char) * (new_size + 2));
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	new_str[i++] = '/';
	while (s2[j] != '\0')
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
	return (new_str);
}

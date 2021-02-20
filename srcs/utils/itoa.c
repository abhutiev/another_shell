/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 14:30:25 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/19 14:30:26 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	len_str_to_prepare(int n)
{
	size_t			counter;

	counter = 1;
	while (n /= 10)
		counter++;
	return (counter);
}

char			*ft_itoa(int n)
{
	char			*result;
	int				length;
	int				is_negative;
	long long		num;

	is_negative = n < 0;
	length = len_str_to_prepare(n) + is_negative;
	result = (char *)malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);
	num = n;
	if (is_negative)
	{
		result[0] = '-';
		num = -num;
	}
	result[length] = '\0';
	while (--length >= is_negative)
	{
		result[length] = (num % 10) + '0';
		num = num / 10;
	}
	return (result);
}

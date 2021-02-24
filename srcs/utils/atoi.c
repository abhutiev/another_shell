/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:32:15 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/24 18:26:46 by sjeffry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		ft_iswhitespace(char str)
{
	if ((str >= 9 && str <= 13) || (str == 32))
		return (1);
	else
		return (0);
}

static int		is_sign(char str)
{
	if ((str == '-') || (str == '+'))
		return (1);
	else
		return (0);
}

int				ft_atoi(char *str)
{
	int				i;
	int				sign;
	unsigned int	res;
	unsigned int	big;

	big = 2147483647 / 10;
	sign = 1;
	i = 0;
	res = 0;
	while (ft_iswhitespace(str[i]) == 1)
		i++;
	if (is_sign(str[i]) == 1)
		if (str[i++] == '-')
			(sign = -1);
	while (ft_isdigit(str[i]))
		res = res * 10 + str[i++] - '0';
	return ((int)(res) * sign);
}

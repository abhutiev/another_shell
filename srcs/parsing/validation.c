/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 09:06:06 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/21 09:06:07 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	validation_of_requests(t_all *all)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (all->requests.separated[i] != NULL)
	{
		j = 0;
		if (!ft_strlen(all->requests.separated[i]))
		{
			change_exitcode_and_err_msg(all,
						SNTX_ERR_DOUBLE_SEMICOLON, "258", -1);
			return (258);
		}
		while (all->requests.separated[i][j] == ' ')
			j++;
		if (!all->requests.separated[i][j])
		{
			change_exitcode_and_err_msg(all, SNTX_ERR_ONE_SEMICOLON, "258", -1);
			return (258);
		}
		i++;
	}
	return (0);
}

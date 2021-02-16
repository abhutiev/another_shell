/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_lowercase.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:54:43 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/16 16:54:51 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	str_to_lowercase(t_all *all, size_t j)
{
	size_t	i;

	i = 0;
	while (all->command[j].name[i])
	{
		if ((all->command[j].name[i] <= 'Z') && (all->command[j].name[i] >= 'A'))
			all->command[j].name[i] += 32;
		i++;
	}
}

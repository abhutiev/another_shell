/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 09:58:24 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/10 09:58:26 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		unset(t_all *all, size_t j)
{
	size_t	i;

	i = 1;
	while (all->command[j].args[i])
	{
		delete_environment(all, all->command[j].args[i]);
		i++;
	}
	change_exitcode_success(all);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_and_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:53:32 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/19 13:57:00 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		parsing_and_execution(t_all *all)
{
	size_t	i;

	i = 0;
	while (all->requests.separated[i])
	{
		first_circle_of_parsing(all, i);
		second_circle_of_parsing(all, i);
		allocate_memory_for_commands(all);
		filling_command_structure(all);
		request_execution(all);
		free_after_parsing(all);
		i++;
	}
	clean_after_yourself(all, i);
	return (0);
}

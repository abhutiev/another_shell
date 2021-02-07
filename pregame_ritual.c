/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pregame_ritual_up.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 03:41:25 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/04 03:41:27 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	flags_shutting_up(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

void		pregame_ritual(t_all *all, int ac, char **av, char **env)
{
	flags_shutting_up(ac, av);
	load_environments(all, env);
	sort_environments(all);
}
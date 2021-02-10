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

#include "../includes/minishell.h"

static void	flags_shutting_up(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

static void	save_fd(t_all *all)
{
	all->descriptors.standard_input = dup(0);
	all->descriptors.standard_output = dup(1);
}

void		pregame_ritual(t_all *all, int ac, char **av, char **env)
{
	flags_shutting_up(ac, av);
	load_environments(all, env);
	sort_environments(all);
	save_fd(all);
	dup2(0, all->descriptors.standard_input);
	dup2(1, all->descriptors.standard_output);
	//signal(SIGINT, );
	//signal(SIGQUIT, );
}
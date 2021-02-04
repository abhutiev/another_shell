/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 03:41:25 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/04 03:41:27 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	flags_shutting_up(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

int		main(int argc, char **argv, char **env)
{
	t_all	all;
	size_t	i;

	i = 0;
	flags_shutting_up(argc, argv);
	load_environments(&all, env);
	while (1)
	{
		write(1, SHELL_NAME, ft_strlen(SHELL_NAME));

	}
	return (0);
}

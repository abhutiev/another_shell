/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 01:49:20 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/09 01:49:22 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_ctrl_c(int sig)
{
	int		pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (sig == SIGINT)
	{
		g_lobal = 1;
		ft_putstr_fd("\b\b  \b\b", 1);
		ft_putendl_fd("", 1);
		if (pid)
		{
			ft_putstr_fd(SHL_NAME, 1);
		}
	}
}

void	signal_ctrl_backslash(int sig)
{
	int		pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (sig == SIGQUIT)
	{
		if (!pid)
		{
			ft_putendl_fd("Quit: 3", 1);
			g_lobal = 131;
		}
		else
		{
			ft_putstr_fd("\b\b  \b\b", 1);
		}
	}
}

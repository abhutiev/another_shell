/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_last_process_code.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 07:30:18 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/21 07:30:21 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_exitcode_and_err_msg(t_all *all, char *msg, char *code, size_t j)
{
	ft_putstr_fd(SHELL_NAME, 1);
	if (j != -1)
		ft_putstr_fd(all->command[j].name, 1);
	ft_putendl_fd(msg, 1);
	delete_environment(all, "?");
	add_environment(all, "?", code);
}
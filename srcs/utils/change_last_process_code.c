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

int		change_exitcode_and_err_msg(t_all *all, char *msg, char *code, size_t j)
{
	ft_putstr_fd(SHELL_NAME, 1);
	if (j != 4294967295)
		ft_putstr_fd(all->command[j].name, 1);
	ft_putendl_fd(msg, 1);
	delete_environment(all, "?");
	add_environment(all, "?", code);
	return (ft_atoi(code));
}

void	change_exitcode_success(t_all *all)
{
	delete_environment(all, "?");
	add_environment(all, "?", "0");
}

int		error_while_binary_execution(t_all *all, size_t j)
{
	if (look_for_env(all, "PATH"))
		change_exitcode_and_err_msg(all, CMD_NOT_FOUND, "127", j);
	else
		change_exitcode_and_err_msg(all, NO_FILE_OR_DIR, "127", j);
	return (127);
}

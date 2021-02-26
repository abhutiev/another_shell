/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 17:58:52 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/24 17:58:53 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	to_right_redir(t_all *all, t_redirect_utils *utils, size_t j)
{
	utils->flag_right = 1;
	all->command[j].files[utils->k].fd =
			open(all->command[j].files[utils->k].name,
						O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (utils->last_right)
		close(all->command[j].files[utils->last_right].fd);
	utils->last_right = utils->k;
}

static void	to_right_double_redir(t_all *all, t_redirect_utils *utils, size_t j)
{
	utils->flag_right = 1;
	all->command[j].files[utils->k].fd =
			open(all->command[j].files[utils->k].name,
							O_CREAT | O_RDWR | O_APPEND, 0644);
	if (utils->last_right)
		close(all->command[j].files[utils->last_right].fd);
	utils->last_right = utils->k;
}

static int	to_left_redir(t_all *all, t_redirect_utils *utils, size_t j)
{
	utils->flag_left = 1;
	all->command[j].files[utils->k].fd =
			open(all->command[j].files[utils->k].name, O_RDONLY);
	if (all->command[j].files[utils->k].fd == -1)
	{
		close(all->command[j].files[utils->last_left].fd);
		utils->last_left = utils->k;
		close(0);
		free(all->command[j].files[utils->k].name);
		change_exitcode_and_err_msg(all, NO_FILE_OR_DIR, "1", j);
		return (1);
	}
	if (utils->last_left)
		close(all->command[j].files[utils->last_left].fd);
	utils->last_left = utils->k;
	return (0);
}

int			open_file_descriptors(t_all *all, size_t j)
{
	t_redirect_utils utils;

	utils_to_zero(&utils);
	while (all->command[j].files[utils.k].name)
	{
		if (all->command[j].files[utils.k].output_flag == TO_RIGHT_REDIR)
			to_right_redir(all, &utils, j);
		else if (all->command[j].files[utils.k].output_flag ==
		TO_RIGHT_DOUBLE_REDIR)
			to_right_double_redir(all, &utils, j);
		else if (all->command[j].files[utils.k].output_flag == TO_LEFT_REDIR)
			if (to_left_redir(all, &utils, j))
				return (1);
		free(all->command[j].files[utils.k].name);
		utils.k++;
	}
	if (utils.flag_right)
		dup2(all->command[j].files[utils.last_right].fd, 1);
	if (utils.flag_left)
		dup2(all->command[j].files[utils.last_left].fd, 0);
	all->fd.fd_out = all->command[j].files[utils.last_right].fd;
	all->fd.fd_in = all->command[j].files[utils.last_left].fd;
	return (0);
}

void		close_file_descriptors(t_all *all, size_t j)
{
	close(0);
	close(1);
	close(all->fd.fd_in);
	close(all->fd.fd_out);
	dup2(all->fd.standard_output, 1);
	dup2(all->fd.standard_input, 0);
	free(all->command[j].files);
}

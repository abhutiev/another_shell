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

static void	utils_to_zero(t_redirect_utils *utils)
{
	utils->k = 0;
	utils->last_right = 0;
	utils->last_left = 0;
	utils->flag_left = 0;
	utils->flag_right = 0;
}

int 		open_file_descriptors(t_all *all, size_t j)
{
	t_redirect_utils utils;

	utils_to_zero(&utils);
	while (all->command[j].files[utils.k].name)
	{
		if (all->command[j].files[utils.k].output_flag == TO_RIGHT_REDIR)
		{
			utils.flag_right = 1;
			all->command->files[utils.k].fd = open(all->command[j].files[utils.k].name, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (utils.last_right)
				close(all->command->files[utils.last_right].fd);
			utils.last_right = utils.k;
		}
		else if (all->command[j].files[utils.k].output_flag == TO_RIGHT_DOUBLE_REDIR)
		{
			utils.flag_right = 1;
			all->command->files[utils.k].fd = open(all->command[j].files[utils.k].name, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (utils.last_right)
				close(all->command->files[utils.last_right].fd);
			utils.last_right = utils.k;
		}
		else if (all->command[j].files[utils.k].output_flag == TO_LEFT_REDIR)
		{
			utils.flag_left = 1;
			all->command->files[utils.k].fd = open(all->command[j].files[utils.k].name, O_RDONLY);
			if (utils.last_left)
				close(all->command->files[utils.last_right].fd);
			utils.last_left = utils.k;
		}
		free(all->command[j].files[utils.k].name);
		utils.k++;
	}
	if (utils.flag_right)
		dup2(all->command[j].files[utils.last_right].fd, 1);
	if (utils.flag_left)
		dup2(all->command[j].files[utils.last_left].fd, 0);
	all->fd.fd_out = all->command[j].files[utils.last_right].fd;
	all->fd.fd_in = all->command[j].files[utils.last_left].fd;
	return (utils.last_right);
}

int 	close_file_descriptors(t_all *all, size_t j)
{
	close(1);
	close(all->fd.fd_in);
	close(all->fd.fd_out);
	dup2(all->fd.standard_output, 1);
	dup2(all->fd.standard_input, 0);
	free(all->command[j].files);
}

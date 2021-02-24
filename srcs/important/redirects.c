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

int 	open_file_descriptors(t_all *all, size_t j)
{
	int		k;
	int		last_right;
	int		last_left;
	int		flag_left;
	int		flag_right;

	k = 0;
	last_right = 0;
	last_left = 0;
	flag_left = 0;
	flag_right = 0;
	while (all->command[j].files[k].name)
	{
		if (all->command[j].files[k].output_flag == TO_RIGHT_REDIR)
		{
			flag_right = 1;
			all->command->files[k].fd = open(all->command[j].files[k].name, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (last_right)
				close(all->command->files[last_right].fd);
			last_right = k;
		}
		else if (all->command[j].files[k].output_flag == TO_RIGHT_DOUBLE_REDIR)
		{
			flag_right = 1;
			all->command->files[k].fd = open(all->command[j].files[k].name, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (last_right)
				close(all->command->files[last_right].fd);
			last_right = k;
		}
		else if (all->command[j].files[k].output_flag == TO_LEFT_REDIR)
		{
			flag_left = 1;
			all->command->files[k].fd = open(all->command[j].files[k].name, O_RDONLY);
			if (last_left)
				close(all->command->files[last_right].fd);
			last_left = k;
		}
		free(all->command[j].files[k].name);
		k++;
	}
	if (flag_right)
		dup2(all->command[j].files[last_right].fd, 1);
	if (flag_left)
		dup2(all->command[j].files[last_left].fd, 0);
	all->fd.fd_out = all->command[j].files[last_right].fd;
	all->fd.fd_in = all->command[j].files[last_left].fd;
	return (last_right);
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

#include "../../includes/minishell.h"

int	find_left_redirect_pipe(t_all *all)
{
	size_t	i;
	int		current_fd;

	i = 0;
	current_fd = 0;
	while (all->command[0].files[i].name)
	{
		if (all->command[0].files[i].output_flag == TO_LEFT_REDIR)
		{
			if (current_fd != 0)
				close(current_fd);
			current_fd = open(all->command[0].files[i].name, O_RDONLY);
			if (current_fd == -1)
			{
				change_exitcode_and_errno(all, "1", 0);
				return (-1);
			}
		}
		i++;
	}
	return (current_fd);
}

int	find_right_redirect_pipe(t_all *all, size_t j)
{
	size_t	k;
	int		output_fd;

	k = 0;
	output_fd = 0;
	while (all->command[j].files[k].name)
	{
		if (all->command[j].files[k].output_flag == TO_RIGHT_REDIR)
		{
			if (output_fd)
				close(output_fd);
			output_fd = open(all->command[j].files[k].name,
					O_CREAT | O_RDWR | O_TRUNC, 0644);
		}
		else if (all->command[j].files[k].output_flag == TO_RIGHT_DOUBLE_REDIR)
		{
			if (output_fd)
				close(output_fd);
			output_fd = open(all->command[j].files[k].name,
					O_CREAT | O_RDWR | O_APPEND, 0644);
		}
		k++;
	}
	return (output_fd);
}

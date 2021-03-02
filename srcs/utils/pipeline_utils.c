#include "../../includes/minishell.h"

void	close_all_pipes(t_all *all)
{
	size_t	j;

	j = 0;
	free(all->pid);
	dup2(all->fd.standard_output, 1);
	dup2(all->fd.standard_input, 0);
	while (j < all->fd.number_of_pipes)
	{
		close(all->fd.pipeline[j][0]);
		close(all->fd.pipeline[j][1]);
		free(all->fd.pipeline[j]);
		j++;
	}
	free(all->fd.pipeline);
}

void	build_pipeline(t_all *all)
{
	size_t	j;

	all->fd.number_of_pipes = 0;
	while (all->command[all->fd.number_of_pipes].name)
		all->fd.number_of_pipes++;
	all->pid = (pid_t *)ft_calloc(all->fd.number_of_pipes + 1, sizeof(pid_t));
	all->fd.pipeline = ft_calloc(all->fd.number_of_pipes--, sizeof(int) * 2);
	j = 0;
	while (j < all->fd.number_of_pipes)
	{
		all->fd.pipeline[j] = ft_calloc(2, sizeof(int));
		pipe(all->fd.pipeline[j]);
		j++;
	}
}

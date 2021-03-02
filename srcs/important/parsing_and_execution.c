#include "../../includes/minishell.h"

static void	is_signals_changed_last_process_code(t_all *all)
{
	char	*buf;

	if (g_lobal)
	{
		delete_environment(all, "?");
		buf = ft_itoa(g_lobal);
		add_environment(all, "?", buf);
		free(buf);
		g_lobal = 0;
	}
}

static int	request_execution(t_all *all)
{
	if (!all->fd.pipe_flag)
		return (single_command_execution(all, 0));
	return (multiple_command_execution(all));
}

int	parsing_and_execution(t_all *all)
{
	size_t	i;

	i = 0;
	while (all->requests.separated[i])
	{
		first_circle_of_parsing(all, i);
		second_circle_of_parsing(all, i);
		allocate_memory_for_commands(all);
		filling_command_structure(all);
		request_execution(all);
		free_after_parsing(all);
		is_signals_changed_last_process_code(all);
		i++;
	}
	clean_after_yourself(all, i);
	return (0);
}

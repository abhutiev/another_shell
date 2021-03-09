#include "../includes/minishell.h"

int	main(int argc, char **argv, char **en)
{
	t_all	all;

	pregame_ritual(&all, argc, argv, en);
	while (1)
	{
		g_signal_mode = 1;
		ft_putstr_fd(SHL_NAME, 1);
		if (!get_next_line(0, &(all.buffer.line_1))
			&& !ft_strcmp(all.buffer.line_1, ""))
			exit(ft_putendl_fd("  \b\b\nexit", 1));
		count_requests(&all);
		separate_requests(&all);
		if (validation_of_requests(&all))
		{
			free_memory_in_case_of_invalid_request(&all);
			continue ;
		}
		parsing_and_execution(&all);
	}
}

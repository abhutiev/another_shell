#include "../../includes/minishell.h"

int	requests_validation_after_filling_circle(t_all *all)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (all->requests.line_with_substitutions[i])
	{
		if (!ft_strlen(all->requests.line_with_substitutions[i]))
			return (1);
		j = 0;
		while (all->requests.line_with_substitutions[i][j])
		{
			if (ft_strcmp("|", all->requests.line_with_substitutions[i]))
				return (1);
		}
	}
	return (0);
}

static int	free_if_not_valid_after_first_circle(t_all *all, size_t i)
{
	while (all->requests.line_with_substitutions[i])
	{
		free(all->requests.line_with_substitutions[i++]);
	}
	free(all->requests.line_with_substitutions[i++]);
	free(all->requests.line_with_substitutions);
	free(all->requests.separated);
	change_exitcode_and_err_msg_with_no_command_name(all,
		 "shitty and multiline cases not in subject, but we've tried to handle it",
		 "258");
	return (1);
}

int	requests_validation_after_first_circle(t_all *all, size_t i)
{
	size_t	j;

	if (!ft_strlen(all->requests.line_with_substitutions[i]))
		return (free_if_not_valid_after_first_circle(all, i));
	j = 0;
	while (all->requests.line_with_substitutions[i][j] == ' ')
	{
		if (!all->requests.line_with_substitutions[i][j])
			return (free_if_not_valid_after_first_circle(all, i));
		j++;
	}
	return (0);
}
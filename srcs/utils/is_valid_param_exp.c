#include "../../includes/minishell.h"

static int	ft_is_valid_param_exp(int c)
{
	if ((c == '_') || ft_isdigit(c) || ft_isalpha(c))
		return (c);
	return (0);
}

int	export_validation(t_all *all, char *param, size_t j)
{
	int			i;

	i = 0;
	if (ft_isdigit(param[0]))
	{
		change_exitcode_and_err_msg(all,
			": not a valid identifier", "1", j);
		return (0);
	}
	while (param[i])
	{
		if (!ft_is_valid_param_exp(param[i]))
		{
			change_exitcode_and_err_msg(all,
				": not a valid identifier", "1", j);
			return (0);
		}
		i++;
	}
	return (1);
}

#include "../../includes/minishell.h"

int	env(t_all *all, size_t j)
{
	size_t	i;

	i = 0;
	if (all->command[j].args[1] != NULL)
		return (change_exitcode_and_err_msg(all, NO_FILE_OR_DIR, "127", j));
	while (all->env[i].name)
	{
		if (!ft_strcmp(all->env[i].name, "?")
			|| !ft_strcmp(all->env[i].name, "$"))
		{
			i++;
			continue ;
		}
		if (ft_strlen(all->env[i].value))
		{
			ft_putstr_fd(all->env[i].name, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(all->env[i].value, 1);
		}
		i++;
	}
	change_exitcode_success(all);
	return (1);
}

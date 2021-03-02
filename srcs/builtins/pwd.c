#include "../../includes/minishell.h"

int	pwd(t_all *all)
{
	char	*res;

	res = getcwd(NULL, -1);
	ft_putendl_fd(res, 1);
	free(res);
	change_exitcode_success(all);
	return (1);
}

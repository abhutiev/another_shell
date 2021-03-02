#include "../../includes/minishell.h"

int	validation_of_requests(t_all *all)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (all->requests.separated[i] != NULL)
	{
		j = 0;
		if (!ft_strlen(all->requests.separated[i]))
		{
			change_exitcode_and_err_msg(all,
						SNTX_ERR_DOUBLE_SEMICOLON, "258", -1);
			return (258);
		}
		while (all->requests.separated[i][j] == ' ')
			j++;
		if (!all->requests.separated[i][j])
		{
			change_exitcode_and_err_msg(all, SNTX_ERR_ONE_SEMICOLON, "258", -1);
			return (258);
		}
		i++;
	}
	return (0);
}

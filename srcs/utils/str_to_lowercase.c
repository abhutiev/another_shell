#include "../../includes/minishell.h"

void	str_to_lowercase(t_all *all, size_t j)
{
	size_t	i;

	i = 0;
	while (all->command[j].name[i])
	{
		if ((all->command[j].name[i] <= 'Z')
			&& (all->command[j].name[i] >= 'A'))
			all->command[j].name[i] += 32;
		i++;
	}
}

#include "../../includes/minishell.h"

int	is_shielded(t_all *all)
{
	int		counter;
	size_t	i;

	if (!all->buffer.iter_1)
		return (0);
	i = all->buffer.iter_1 - 1;
	counter = 0;
	while (all->buffer.line_1[i] == '\\' && i >= 0)
	{
		counter++;
		i--;
	}
	return (counter % 2);
}

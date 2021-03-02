#include "../../includes/minishell.h"

void	skip_spaces(t_all *all)
{
	while (all->buffer.line_1[all->buffer.iter_1] == ' ')
		all->buffer.iter_1++;
}

#include "../../includes/minishell.h"

void	iterators_to_zero(t_all *all)
{
	all->iter.i = 0;
	all->iter.j = 0;
	all->iter.k = 0;
	all->iter.n = 0;
	all->fd.pipe_flag = 0;
}

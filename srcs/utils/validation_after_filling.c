#include "../../includes/minishell.h"

int	free_after_filling(t_all *all)
{
	free(all->separated_request[all->iter.i]);
	free_after_parsing(all);
	//free(all->requests.line_with_substitutions);
	//free(all->requests.separated);
	return (2);
}

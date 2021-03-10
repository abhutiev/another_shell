#include "../../includes/minishell.h"

void	free_after_parsing(t_all *all)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (all->separated_request[i])
		i++;
	i = 0;
	while (all->command[i].name)
	{
		j = 1;
		while (all->command[i].args[j])
			free(all->command[i].args[j++]);
		free(all->command[i].args[j]);
		free(all->command[i].name);
		free(all->command[i].args);
		k = 0;
		while (all->command[i].files[k].name)
			free(all->command[i].files[k++].name);
		free(all->command[i++].files);
	}
	free(all->command[i].args);
	free(all->command[i].name);
	free(all->separated_request);
	free(all->command);
}

void	clean_after_yourself(t_all *all, size_t i)
{
	free(all->requests.separated[i]);
	free(all->requests.separated);
	free(all->requests.line_with_substitutions[i]);
	free(all->requests.line_with_substitutions);
}

void	free_memory_in_case_of_invalid_request(t_all *all)
{
	size_t	i;

	i = 0;
	while (all->requests.separated[i] != NULL)
	{
		free(all->requests.separated[i]);
		all->requests.separated[i] = NULL;
		i++;
	}
	free(all->requests.separated[i]);
	free(all->requests.line_with_substitutions);
	free(all->requests.separated);
	all->requests.separated = NULL;
}

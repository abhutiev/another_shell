#include "../../includes/minishell.h"

void	add_environment(t_all *all, char *name, char *value)
{
	size_t			i;
	size_t			number_of_envs;
	static size_t	allocated = 100;

	i = 0;
	number_of_envs = 0;
	while (all->env[number_of_envs].name)
	{
		if (!ft_strcmp(all->env[number_of_envs].name, name))
			delete_environment(all, name);
		number_of_envs++;
	}
	all->env = ft_realloc(all->env, 8 * (allocated++));
	while (all->env[i].name && (ft_strcmp(all->env[i].name, name) > 0))
		i++;
	while (number_of_envs + 1 > i)
	{
		all->env[number_of_envs + 1].name = all->env[number_of_envs].name;
		all->env[number_of_envs + 1].value = all->env[number_of_envs].value;
		number_of_envs--;
	}
	all->env[number_of_envs + 1].name = ft_strdup(name);
	all->env[number_of_envs + 1].value = ft_strdup(value);
}

void	delete_environment(t_all *all, char *name)
{
	size_t	i;

	i = 0;
	while (all->env[i].name && (ft_strcmp(all->env[i].name, name) != 0))
		i++;
	if (all->env[i].name == 0)
		return ;
	free(all->env[i].name);
	free(all->env[i].value);
	while (all->env[i + 1].name)
	{
		all->env[i].name = all->env[i + 1].name;
		all->env[i].value = all->env[i + 1].value;
		i++;
	}
	all->env[i].name = NULL;
	all->env[i].value = NULL;
}

char	*look_for_env(t_all *all, char *name)
{
	size_t	i;

	i = 0;
	while (all->env[i].name)
	{
		if (!ft_strcmp(name, all->env[i].name))
			return (all->env[i].value);
		i++;
	}
	return (NULL);
}

char	**env_for_execve(t_all *all)
{
	size_t	i;
	size_t	number_of_envs;
	char	**result;

	i = 0;
	number_of_envs = 0;
	while (all->env[number_of_envs].name)
		number_of_envs++;
	result = ft_calloc(number_of_envs + 2, sizeof(char *));
	while (all->env[i].name)
	{
		if (all->env[i].value)
		{
			result[i] = ft_calloc(ft_strlen(all->env[i].name)
					+ ft_strlen(all->env[i].value) + 2, sizeof(char));
			ft_strcpy(result[i], all->env[i].name);
			ft_strlcat(result[i], "=", ft_strlen(all->env[i].name) + 2);
			ft_strlcat(result[i], all->env[i].value,
				ft_strlen(all->env[i].name) + ft_strlen(all->env[i].value) + 2);
		}
		i++;
	}
	return (result);
}

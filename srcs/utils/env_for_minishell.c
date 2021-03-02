#include "../../includes/minishell.h"

char	**allocate_memory_for_env(t_all *all)
{
	size_t	number_of_envs;
	char	**result;

	number_of_envs = 0;
	while (all->env[number_of_envs].name)
		number_of_envs++;
	result = ft_calloc(number_of_envs + 2, sizeof(char *));
	return (result);
}

void	rewrite_shlvl(t_all *all, char ***result, size_t *i)
{
	*(result[*i]) = ft_calloc(200, 1);
	ft_strcpy(*result[*i], "SHLVL=");
	ft_strlcat(*result[*i], ft_itoa(ft_atoi(all->env[*i].value) + 1), 180);
	*i++;
}

char	**env_for_minishell(t_all *all)
{
	size_t	i;
	char	**result;

	i = 0;
	result = allocate_memory_for_env(all);
	while (all->env[i].name)
	{
		if (!ft_strcmp(all->env[i].name, "SHLVL"))
		{
			rewrite_shlvl(all, &result, &i);
			continue ;
		}
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

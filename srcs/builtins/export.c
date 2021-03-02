#include "../../includes/minishell.h"

static void	skip_till_quote(t_all *all, char c)
{
	all->buffer.iter_1++;
	while (all->buffer.line_1[all->buffer.iter_1]
		&& all->buffer.line_1[all->buffer.iter_1] != c)
	{
		all->buffer.line_2[all->buffer.iter_2++]
			= all->buffer.line_1[all->buffer.iter_1++];
	}
	all->buffer.iter_1++;
}

static void	prepare_for_split(t_all *all, size_t i, size_t j)
{
	all->buffer.buff = (char **)ft_calloc(3, sizeof(char *));
	all->buffer.line_1 = all->command[j].args[i];
	all->buffer.line_2 = ft_calloc(1024, sizeof(char));
	all->buffer.iter_1 = 0;
	all->buffer.iter_2 = 0;
}

static int	display_export(t_all *all)
{
	size_t	i;

	i = 0;
	while (all->env[i].name)
	{
		if (!ft_strcmp(all->env[i].name, "?")
			|| !ft_strcmp(all->env[i].name, "$"))
		{
			i++;
			continue ;
		}
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(all->env[i].name, 1);
		if (all->env[i].value)
		{
			ft_putchar_fd('=', 1);
			ft_putchar_fd('\"', 1);
			if (ft_strlen(all->env[i].value))
				ft_putstr_fd(all->env[i].value, 1);
			ft_putchar_fd('\"', 1);
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (1);
}

static char	**split_export_args(t_all *all, size_t j, size_t i)
{
	prepare_for_split(all, i, j);
	while (all->buffer.line_1[all->buffer.iter_1]
		&& all->buffer.line_1[all->buffer.iter_1] != '=')
	{
		if (all->buffer.line_1[all->buffer.iter_1] == '\"')
			skip_till_quote(all, '\"');
		if (all->buffer.line_1[all->buffer.iter_1] == '\'')
			skip_till_quote(all, '\'');
		if (all->buffer.line_1[all->buffer.iter_1++] == '=')
			all->buffer.line_2[all->buffer.iter_2] = '\0';
		else
			all->buffer.line_2[all->buffer.iter_2++]
				= all->buffer.line_1[all->buffer.iter_1 - 1];
	}
	all->buffer.buff[0] = all->buffer.line_2;
	if (all->buffer.line_1[all->buffer.iter_1] == '=')
		all->buffer.buff[1] = ft_strdup(all->buffer.line_1
				+ all->buffer.iter_1 + 1);
	else
		all->buffer.buff[1] = NULL;
	return (all->buffer.buff);
}

int	export(t_all *all, size_t j)
{
	size_t	i;
	char	**splitted;

	if (all->command[j].args[1] == NULL)
		return (display_export(all));
	i = 0;
	while (all->command[j].args[++i])
	{
		splitted = split_export_args(all, j, i);
		if (export_validation(all, splitted[0], j))
		{
			add_environment(all, splitted[0], splitted[1]);
			change_exitcode_success(all);
		}
		free(splitted[0]);
		free(splitted[1]);
		free(splitted);
	}
	return (1);
}

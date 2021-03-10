#include "../../includes/minishell.h"

static void	dollar_substitution(t_all *all)
{
	size_t	i;
	size_t	j;
	char	name_of_env[100];

	all->buffer.iter_1++;
	i = 0;
	if (all->buffer.line_1[all->buffer.iter_1] == '\''
		|| all->buffer.line_1[all->buffer.iter_1] == '\"')
		all->buffer.iter_1++;
	while (!is_special_symbol(all->buffer.line_1[all->buffer.iter_1]))
		name_of_env[i++] = all->buffer.line_1[all->buffer.iter_1++];
	name_of_env[i] = '\0';
	j = 0;
	while (all->env[j].name)
	{
		if (ft_strcmp(all->env[j].name, name_of_env) == 0)
			break ;
		j++;
	}
	if (all->env[j].name)
	{
		ft_strcpy(all->buffer.line_2
		+ all->buffer.iter_2, all->env[j].value);
		all->buffer.iter_2 += ft_strlen(all->env[j].value);
	}
}

static void	get_argument_from_single_quote(t_all *all)
{
	all->buffer.line_2[all->buffer.iter_2++] = '\'';
	all->buffer.iter_1++;
	while (all->buffer.line_1[all->buffer.iter_1]
		&& (all->buffer.line_1[all->buffer.iter_1] != '\'' || is_shielded(all)))
	{
		all->buffer.line_2[all->buffer.iter_2++]
			= all->buffer.line_1[all->buffer.iter_1++];
	}
	all->buffer.line_2[all->buffer.iter_2++] = '\'';
	all->buffer.iter_1++;
}

static void	get_argument_from_double_quote(t_all *all)
{
	all->buffer.line_2[all->buffer.iter_2++] = '\"';
	all->buffer.iter_1++;
	while (all->buffer.line_1[all->buffer.iter_1]
		&& (all->buffer.line_1[all->buffer.iter_1] != '\"' || is_shielded(all)))
	{
		if (all->buffer.line_1[all->buffer.iter_1] == '$' && !is_shielded(all))
			dollar_substitution(all);
		else
			all->buffer.line_2[all->buffer.iter_2++]
				= all->buffer.line_1[all->buffer.iter_1++];
	}
	all->buffer.line_2[all->buffer.iter_2++] = '\"';
	all->buffer.iter_1++;
}

void	first_circle_of_parsing(t_all *all, size_t i)
{
	all->buffer.iter_1 = 0;
	all->buffer.iter_2 = 0;
	all->buffer.line_1 = all->requests.separated[i];
	all->buffer.line_2 = (char *)ft_calloc(1000, sizeof(char));
	while (all->buffer.line_1[all->buffer.iter_1])
	{
		if (all->buffer.line_1[all->buffer.iter_1] == '\''
			&& !is_shielded(all))
			get_argument_from_single_quote(all);
		else if (all->buffer.line_1[all->buffer.iter_1] == '\"'
			&& !is_shielded(all))
			get_argument_from_double_quote(all);
		else if (all->buffer.line_1[all->buffer.iter_1] == '$'
			&& !is_shielded(all))
			dollar_substitution(all);
		else
			all->buffer.line_2[all->buffer.iter_2++]
				= all->buffer.line_1[all->buffer.iter_1++];
	}
	all->buffer.line_2[all->buffer.iter_2] = '\0';
	all->requests.line_with_substitutions[i] = all->buffer.line_2;
	free(all->buffer.line_1);
}

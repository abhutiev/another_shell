#include "../../includes/minishell.h"

int	stop_buffering_condition(t_all *all)
{
	if (!is_shielded(all)
		&& (all->buffer.line_1[all->buffer.iter_1] == ' '
				|| all->buffer.line_1[all->buffer.iter_1] == '>'
				|| all->buffer.line_1[all->buffer.iter_1] == '|'
				|| all->buffer.line_1[all->buffer.iter_1] == '<'))
		return (1);
	else
		return (0);
}

void	get_ready_for_separator_check(t_all *all)
{
	all->buffer.line_2[all->buffer.iter_2] = '\0';
	all->buffer.iter_2 = 0;
	all->separated_request[all->n++] = all->buffer.line_2;
	all->buffer.line_2 = (char *)ft_calloc(1024, 1);
}

//qwe

void	stop_buffering(t_all *all)
{
	skip_spaces(all);
	get_ready_for_separator_check(all);
	if (!ft_strncmp(all->buffer.line_1 + all->buffer.iter_1, ">>", 2))
	{
		all->separated_request[all->n++] = ft_strdup(">>");
		all->buffer.iter_1 += 2;
	}
	else if (all->buffer.line_1[all->buffer.iter_1] == '>')
	{
		all->separated_request[all->n++] = ft_strdup(">");
		all->buffer.iter_1++;
	}
	else if (all->buffer.line_1[all->buffer.iter_1] == '<')
	{
		all->separated_request[all->n++] = ft_strdup("<");
		all->buffer.iter_1++;
	}
	else if (all->buffer.line_1[all->buffer.iter_1] == '|')
	{
		all->separated_request[all->n++] = ft_strdup("|");
		all->buffer.iter_1++;
	}
	skip_spaces(all);
}

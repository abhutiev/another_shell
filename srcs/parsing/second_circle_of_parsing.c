#include "../../includes/minishell.h"

static void	fill_buffer_from_quotes(t_all *all, char c)
{
	all->buffer.iter_1++;
	while (all->buffer.line_1[all->buffer.iter_1] != '\0' )
	{
		if (all->buffer.line_1[all->buffer.iter_1] == '\\'
			&& c == '\"')
		{
			all->buffer.iter_1++;
		}
		if (all->buffer.line_1[all->buffer.iter_1] == c
			&& !is_shielded(all))
			break ;
		all->buffer.line_2[all->buffer.iter_2++]
			= all->buffer.line_1[all->buffer.iter_1++];
	}
	all->buffer.iter_1++;
}

static void	prepare_for_parsing(t_all *all, size_t i)
{
	all->n = 0;
	all->buffer.iter_1 = 0;
	skip_spaces(all);
	all->buffer.line_1 = all->requests.line_with_substitutions[i];
	all->buffer.iter_2 = 0;
	all->buffer.line_2 = (char *)ft_calloc(1024, 1);
	all->separated_request = (char **)ft_calloc(256, sizeof(char *));
}

static int	end_of_parsing(t_all *all, size_t i)
{
	free(all->requests.line_with_substitutions[i]);
	all->buffer.line_2[all->buffer.iter_2] = '\0';
	if (!all->buffer.line_2[0])
	{
		free(all->buffer.line_2);
		all->separated_request[all->n] = NULL;
		return (1);
	}
	all->buffer.iter_2 = 0;
	all->separated_request[all->n] = all->buffer.line_2;
	all->n++;
	all->separated_request[all->n] = NULL;
	return (0);
}

int	second_circle_of_parsing(t_all *all, size_t i)
{
	prepare_for_parsing(all, i);
	while (all->buffer.line_1[all->buffer.iter_1]
		&& all->buffer.line_1[all->buffer.iter_1] != ';')
	{
		if (stop_buffering_condition(all))
			stop_buffering(all);
		if (all->buffer.line_1[all->buffer.iter_1] == '\"')
			fill_buffer_from_quotes(all, '\"');
		else if (all->buffer.line_1[all->buffer.iter_1] == '\'')
			fill_buffer_from_quotes(all, '\'');
		else
		{
			if (all->buffer.line_1[all->buffer.iter_1] == '\\')
			{
				all->buffer.line_2[all->buffer.iter_2++]
					= all->buffer.line_1[++all->buffer.iter_1];
				all->buffer.iter_1++;
			}
			else
				all->buffer.line_2[all->buffer.iter_2++]
					= all->buffer.line_1[all->buffer.iter_1++];
		}
	}
	end_of_parsing(all, i);
	return (0);
}

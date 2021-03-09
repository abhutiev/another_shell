#include "../../includes/minishell.h"

int	ft_strcmp(char *line1, char *line2)
{
	size_t	i;

	i = 0;
	if (line1 == NULL || line2 == NULL)
		return (1);
	while (line1[i])
	{
		if (line1[i] != line2[i])
			return (line2[i] - line1[i]);
		i++;
	}
	return (line2[i] - line1[i]);
}

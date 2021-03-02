#include "../../includes/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!s1[0] && !s2[0])
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	while (i < n)
	{
		if (!s1[i] && !s2[i])
			return (0);
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

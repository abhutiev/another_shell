#include "../../includes/minishell.h"

char	*ft_strdup(char *s1)
{
	size_t	memory;
	char	*new_str;

	if (s1 == NULL)
		return (NULL);
	memory = ft_strlen(s1);
	new_str = (void *)malloc(memory + 1);
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, s1, memory + 1);
	return (new_str);
}

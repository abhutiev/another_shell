#include "../../includes/minishell.h"

char	*strjoin_for_path(char const *s1, char const *s2)
{
	size_t	new_size;
	char	*new_str;
	size_t	i;
	size_t	j;

	if (s1 == NULL)
		return (NULL);
	new_size = ft_strlen((char *)s1) + ft_strlen((char *)s2) - 1;
	new_str = (char *)ft_calloc((new_size + 2000), sizeof(char));
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	new_str[i++] = '/';
	while (s2[j] != '\0')
	{
		new_str[i + j] = s2[j];
		j++;
	}
	new_str[i + j] = '\0';
	return (new_str);
}

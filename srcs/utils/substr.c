#include "../../includes/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	substring = (char *)malloc(sizeof(char) * len + 1);
	if (substring == NULL)
		return (NULL);
	if (start > ft_strlen((char *)s))
		return (substring);
	while (i < len)
	{
		substring[i] = s[i + start];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

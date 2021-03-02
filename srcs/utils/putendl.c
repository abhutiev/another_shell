#include "../../includes/minishell.h"

int	ft_putendl_fd(char *s, int fd)
{
	size_t	length;
	size_t	i;

	if (s == NULL)
		return (0);
	length = ft_strlen(s);
	i = 0;
	while (i < length)
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
	return (0);
}

#include "../../includes/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	length;
	size_t	i;

	if (s == NULL)
		return ;
	length = ft_strlen(s);
	i = 0;
	while (i < length)
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

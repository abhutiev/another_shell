#include "../../includes/minishell.h"

void	*ft_bzero(void *b, size_t len)
{
	unsigned char	*tmp_mem;
	size_t			i;

	i = 0;
	tmp_mem = (unsigned char *)b;
	while (i < len)
	{
		tmp_mem[i] = 0;
		i++;
	}
	return (b);
}

#include "../../includes/minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;
	size_t			i;

	if (dst == NULL && src == NULL)
		return (dst);
	tmp_src = (unsigned char *)src;
	tmp_dst = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		tmp_dst[i] = tmp_src[i];
		i++;
	}
	return (dst);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tmp_mem;
	size_t			i;

	i = 0;
	tmp_mem = (unsigned char *)b;
	while (i < len)
	{
		tmp_mem[i] = c;
		i++;
	}
	return (b);
}

void	*ft_realloc(void *ptr, size_t len)
{
	void	*new_allocated;

	new_allocated = malloc(len);
	ft_memset(new_allocated, 0, len);
	if (new_allocated)
		ft_memcpy(new_allocated, ptr, len);
	free(ptr);
	return (new_allocated);
}

#include "../../includes/minishell.h"

static size_t	len_str_to_prepare(int n)
{
	size_t			counter;

	counter = 0;
	while (n)
	{
		counter++;
		n /= 10;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char		*result;
	int			length;
	int			is_negative;
	long long	num;

	is_negative = n < 0;
	if (n == 0)
		return (ft_strdup("0"));
	length = len_str_to_prepare(n) + is_negative;
	result = (char *)ft_calloc(sizeof(char), (length + 1));
	if (!result)
		return (NULL);
	num = n;
	if (is_negative)
	{
		result[0] = '-';
		num = -num;
	}
	result[length] = '\0';
	while (--length >= is_negative)
	{
		result[length] = (num % 10) + '0';
		num = num / 10;
	}
	return (result);
}

#include "../../includes/minishell.h"

static size_t	ncopy(char **dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		(*dst)[i] = src[i];
		i++;
	}
	(*dst)[i] = '\0';
	return (i);
}

int	get_next_line(int fd, char **line)
{
	char	*buffer;
	char	check;
	int		eof;
	int		help;
	size_t	i;

	if (!line || (read(fd, &check, 0) < 0))
		return (-1);
	i = 0;
	eof = 1;
	buffer = (char *)ft_calloc(2048, sizeof(char));
	help = 1;
	while (help == 1)
	{
		help = read(fd, &buffer[i], 1);
		if (!help && i)
		{
			help = 1;
			continue ;
		}
		else if (!help)
			break ;
		if (buffer[i] == '\n')
		{
			eof = 0;
			break ;
		}
		i++;
	}
	(*line) = (char *)calloc(i + 1, sizeof(char));
	ncopy(line, buffer, i);
	free(buffer);
	return (!eof);
}

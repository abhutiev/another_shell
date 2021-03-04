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

void	get_ready_to_gnl(t_gnl_utils *gnl)
{
	gnl->i = 0;
	gnl->eof = 1;
	gnl->buffer = (char *)ft_calloc(2048, sizeof(char));
	gnl->help = 1;
}

int	get_next_line(int fd, char **line)
{
	t_gnl_utils	gnl;

	get_ready_to_gnl(&gnl);
	while (gnl.help == 1)
	{
		gnl.help = read(fd, &gnl.buffer[gnl.i], 1);
		if (!gnl.help && gnl.i)
		{
			gnl.help = 1;
			continue ;
		}
		else if (!gnl.help)
			break ;
		if (gnl.buffer[gnl.i] == '\n')
		{
			gnl.eof = 0;
			break ;
		}
		gnl.i++;
	}
	(*line) = (char *)calloc(gnl.i + 1, sizeof(char));
	ncopy(line, gnl.buffer, gnl.i);
	free(gnl.buffer);
	return (!gnl.eof);
}

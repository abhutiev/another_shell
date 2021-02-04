/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <gdoge@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 15:29:58 by gdoge             #+#    #+#             */
/*   Updated: 2020/12/01 03:04:14 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


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

int				get_next_line(int fd, char **line)
{
	char	*buffer;
	char	check;
	int		eof;
	size_t	i;

	if (!line || (read(fd, &check, 0) < 0))
		return (-1);
	i = 0;
	eof = 1;
	buffer = (char *)malloc(2048);
	while (read(fd, &buffer[i], 1) == 1)
	{
		if (buffer[i] == '\n')
		{
			eof = 0;
			break ;
		}
		i++;
	}
	(*line) = (char *)malloc(i + 1);
	ncopy(line, buffer, i);
	free(buffer);
	return (!eof);
}

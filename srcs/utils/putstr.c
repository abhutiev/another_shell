/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:00:13 by gdoge             #+#    #+#             */
/*   Updated: 2020/11/03 00:06:59 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

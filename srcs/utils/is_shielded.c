/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon_shielded.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 07:04:50 by gdoge             #+#    #+#             */
/*   Updated: 2021/01/27 07:04:52 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_shielded(t_all *all)
{
	int		counter;
	size_t	i;

	if (!all->buffer.iter_1)
		return (0);
	i = all->buffer.iter_1 - 1;
	counter = 0;
	while (all->buffer.line_1[i] == '\\' && i >= 0)
	{
		counter++;
		i--;
	}
	return (counter % 2);
}

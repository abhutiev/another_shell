/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators_to_zero.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 18:13:26 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/17 18:13:27 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	iterators_to_zero(t_all *all)
{
	all->iter.i = 0;
	all->iter.j = 0;
	all->iter.k = 0;
	all->iter.n = 0;
}

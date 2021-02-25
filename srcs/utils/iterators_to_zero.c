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
	all->fd.pipe_flag = 0;
}

void	utils_to_zero(t_redirect_utils *utils)
{
	utils->k = 0;
	utils->last_right = 0;
	utils->last_left = 0;
	utils->flag_left = 0;
	utils->flag_right = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 22:06:29 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/08 22:06:52 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		pwd(t_all *all)
{
	char	*res;

	res = getcwd(NULL, -1);
	ft_putendl_fd(res, 1);
	free(res);
	change_exitcode_success(all);
	return (1);
}

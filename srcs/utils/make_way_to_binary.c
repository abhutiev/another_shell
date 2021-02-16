/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_way_to_bin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/13 14:35:47 by gdoge             #+#    #+#             */
/*   Updated: 2021/02/13 14:35:50 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*to_usr_bin(char *command)
{
	char	*bin;

	bin = (char *)ft_calloc(ft_strlen(command) + 10, 1);
	ft_strlcpy(bin, "/usr/bin/", 10);
	ft_strlcat(bin, command, ft_strlen(command) + 10);
	return (bin);
}

char	*to_usr_local_bin(char *command)
{
	char	*bin;

	bin = (char *)ft_calloc(ft_strlen(command) + 16, 1);
	ft_strlcpy(bin, "/usr/local/bin/", 16);
	ft_strlcat(bin, command, ft_strlen(command) + 16);
	return (bin);
}

char	*to_bin(char *command)
{
	char	*bin;

	bin = (char *)ft_calloc(ft_strlen(command) + 6, 1);
	ft_strlcpy(bin, "/bin/", 6);
	ft_strlcat(bin, command, ft_strlen(command) + 6);
	return (bin);
}

char	*to_usr_sbin(char *command)
{
	char	*bin;

	bin = (char *)ft_calloc(ft_strlen(command) + 11, 1);
	ft_strlcpy(bin, "/usr/sbin/", 11);
	ft_strlcat(bin, command, ft_strlen(command) + 11);
	return (bin);
}

char	*to_local_munki(char *command)
{
	char	*bin;

	bin = (char *)ft_calloc(ft_strlen(command) + 18, 1);
	ft_strlcpy(bin, "/usr/local/munki/", 18);
	ft_strlcat(bin, command, ft_strlen(command) + 18);
	return (bin);
}
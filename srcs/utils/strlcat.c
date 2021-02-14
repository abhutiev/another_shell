/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdoge <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 16:31:44 by gdoge             #+#    #+#             */
/*   Updated: 2020/11/04 05:11:06 by gdoge            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;

	i = 0;
	dst_len = ft_strlen(dst);
	if (dstsize > dst_len)
	{
		while (i < dstsize - dst_len - 1 && src[i])
		{
			dst[i + dst_len] = (unsigned char)src[i];
			i++;
		}
		dst[i + dst_len] = 0;
	}
	while (src[i])
		i++;
	if (dst_len > dstsize)
		dst_len = dstsize;
	return (i + dst_len);
}

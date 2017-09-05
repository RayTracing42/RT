/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 11:43:24 by edescoin          #+#    #+#             */
/*   Updated: 2016/12/01 17:41:56 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrealloc(char *src, size_t new_size)
{
	char	*tmp;

	if (!(tmp = ft_strnew(new_size)))
		return (NULL);
	tmp = ft_strncpy(tmp, src, ft_strlen(src));
	free(src);
	return (tmp);
}

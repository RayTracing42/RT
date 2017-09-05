/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 12:01:45 by edescoin          #+#    #+#             */
/*   Updated: 2016/11/21 17:53:36 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	long	i;

	i = -1;
	if ((str = (char*)malloc(size + 1)))
		while (++i <= (long)size)
			str[i] = '\0';
	return (str);
}

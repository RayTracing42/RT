/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:19:48 by edescoin          #+#    #+#             */
/*   Updated: 2016/11/24 13:02:38 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *big, const char *little)
{
	if (little && !(*little))
		return ((char*)big);
	if (big && *big)
	{
		if (!ft_strncmp(big, little, ft_strlen(little)))
			return ((char*)big);
		else
			return (ft_strstr(big + 1, little));
	}
	return (NULL);
}

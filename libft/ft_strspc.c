/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 14:07:55 by edescoin          #+#    #+#             */
/*   Updated: 2017/01/19 14:10:58 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strspc(char *s)
{
	if (s && !ft_isspace(*s) && *s != '\0')
		return (ft_strspc(s + 1));
	return (s && ft_isspace(*s) ? (char*)s : NULL);
}

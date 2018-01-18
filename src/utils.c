/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 11:25:07 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/18 17:12:08 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			get_status(char *status)
{
	if (ft_strcmp("empty", status) == 0)
		return (EMPTY);
	else if (ft_strcmp("full", status) == 0)
		return (FULL);
	else if (ft_strcmp("none", status) == 0)
		return (NONE);
	else
		return (-1);
}

int		gt(double nb1, double nb2)
{
	return ((long)(nb1 * POW) > (long)(nb2 * POW));
}

int		lt(double nb1, double nb2)
{
	return ((long)(nb1 * POW) < (long)(nb2 * POW));
}

int		ge(double nb1, double nb2)
{
	return ((long)(nb1 * POW) >= (long)(nb2 * POW));
}

int		le(double nb1, double nb2)
{
	return ((long)(nb1 * POW) <= (long)(nb2 * POW));
}

int		eq(double nb1, double nb2)
{
	return ((long)(nb1 * POW) == (long)(nb2 * POW));
}

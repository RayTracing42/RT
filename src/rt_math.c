/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 14:56:10 by shiro             #+#    #+#             */
/*   Updated: 2018/01/08 14:59:01 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>


int		gt(double nb1, double nb2)
{
	return ((long)(nb1 * POW) > (long)(nb2 * POW));
}

int		lt(double nb1, double nb2)
{
	return ((long)(nb1 * POW) < (long)(nb2 * POW));
}

int		eq(double nb1, double nb2)
{
	return ((long)(nb1 * POW) == (long)(nb2 * POW));
}

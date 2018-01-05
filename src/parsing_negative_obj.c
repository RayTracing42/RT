/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_negative_obj.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 00:21:37 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/05 03:50:14 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		parsing_negative_obj(t_object *obj, char *object)
{
	char		*data;

	/*penser a attribuer un status negative aux objs*/
	if ((data = get_interval(object, "<negative_obj>", "</negative_obj>")))
	{
		if (!(obj->negative_obj = parsing_object(data)))
			return (-1);

		free(data);
	}
	return (0);
}

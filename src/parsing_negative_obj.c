/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_negative_obj.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 00:21:37 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/18 13:09:21 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parsing_negative_obj(t_object *obj, char *neg)
{
	char		*data[5];
	t_object	*neg_obj;

	if (neg)
	{
		while ((data[0] = get_interval(neg, "<object>", "</object>")))
		{
			data[4] = get_interval(data[0], "<negative_obj>", "</negative_obj>");
			data[1] = get_interval(data[0], "<limit>", "</limit>");
			data[2] = get_interval(data[0], "<transformations>", "</transformations>");
			if (!(neg_obj = parsing_object2(data[0]))
				|| !(data[3] = get_interval(data[0], "<status>", "</status>"))
				|| (neg_obj->status = get_status(data[3])) == -1)
				exit_custom_error("rt", ":parsing_negative_obj() failed");
			parsing_transformations(neg_obj, data[2]);
			parsing_limit(neg_obj, data[1]);
			free(data[0]);
			free(data[1]);
			free(data[2]);
			free(data[3]);
			free(data[4]);
			new_cell_obj(&obj->negative_obj, neg_obj);
		}
	}
}

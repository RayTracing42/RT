/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_transformations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 20:28:14 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/08 03:03:39 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parsing_transformations( t_object *obj, char *object)
{
	char			*data[4];
	t_trans_data	trs;

	trs = (t_trans_data){(t_dot){0, 0, 0}, (t_dot){0, 0, 0}, (t_dot){1, 1, 1}};
	if ((data[0] = get_interval(object, "<transformations>",
		"</transformations>")))
	{
		if ((data[1] = get_interval(data[0], "<translation>",
			"</translation>")))
			if (parsing_dot(data[1], &trs.trans) == -1)
				exit_custom_error("rt", ":parsing translation failed");
		if ((data[2] = get_interval(data[0], "<rotation>", "</rotation>")))
			if(parsing_dot(data[2], &trs.rot) == -1)
				exit_custom_error("rt", ":parsing rotation failed");
		if ((data[3] = get_interval(data[0], "<scale>", "</scale>")))
			if (parsing_dot(data[3], &trs.scale) == -1)
				exit_custom_error("rt", ":parsing scale failed");
		if (trs.scale.x < 0 || trs.scale.y < 0 || trs.scale.z < 0)
			exit_custom_error("rt", ":scale must be greater than <0>");
		free(data[0]);
		free(data[1]);
		free(data[2]);
		free(data[3]);
	}
	set_all_matrix(obj, trs);
}

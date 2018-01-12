/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_transformations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 20:28:14 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/12 00:53:14 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parsing_transformations(t_object *obj, char *trans)
{
	char			*data[3];
	t_trans_data	trs;

	trs = (t_trans_data){(t_dot){0, 0, 0}, (t_dot){0, 0, 0}, (t_dot){1, 1, 1}};
	if (trans)
	{
		if ((data[0] = get_interval(trans, "<translation>", "</translation>")))
			if (parsing_dot(data[0], &trs.trans) == -1)
				exit_custom_error("rt", ":parsing translation failed");
		if ((data[1] = get_interval(trans, "<rotation>", "</rotation>")))
			if(parsing_dot(data[1], &trs.rot) == -1)
				exit_custom_error("rt", ":parsing rotation failed");
		if ((data[2] = get_interval(trans, "<scale>", "</scale>")))
			if (parsing_dot(data[2], &trs.scale) == -1)
				exit_custom_error("rt", ":parsing scale failed");
		if (trs.scale.x < 0 || trs.scale.y < 0 || trs.scale.z < 0)
			exit_custom_error("rt", ":scale must be greater than <0>");
		free(data[0]);
		free(data[1]);
		free(data[2]);
	}
	set_all_matrix(obj, trs);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_transformations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 20:28:14 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/03 13:42:19 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_trans_data	parsing_transformations(char *object)
{
	char			*data[4];
	t_trans_data	trans;

	trans = (t_trans_data){(t_dot){0, 0, 0}, (t_dot){0, 0, 0},
							(t_dot){1, 1, 1}};
	if (!(data[0] = get_interval(object, "<transformations>",
			"</transformations>")))
		return (trans);
	if ((data[1] = get_interval(data[0], "<translation>", "</translation>")))
		if (parsing_dot(data[1], &trans.trans) == -1)
			exit_custom_error("rt", ":parsing translation failed");
	if ((data[2] = get_interval(data[0], "<rotation>", "</rotation>")))
		if(parsing_dot(data[2], &trans.rot) == -1)
			exit_custom_error("rt", ":parsing rotation failed");
	if ((data[3] = get_interval(data[0], "<scale>", "</scale>")))
		if (parsing_dot(data[3], &trans.scale) == -1)
			exit_custom_error("rt", ":parsing scale failed");
	if (trans.scale.x < 0 || trans.scale.y < 0 || trans.scale.z < 0)
		exit_custom_error("rt", ":scale must be greater than <0>");
	free(data[0]);
	free(data[1]);
	free(data[2]);
	free(data[3]);
	return (trans);
}

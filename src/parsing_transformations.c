/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_transformations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 20:28:14 by fcecilie          #+#    #+#             */
/*   Updated: 2017/12/16 11:34:56 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_trans_data	parsing_transformations(char *object)
{
	char			*data[4];
	t_trans_data	trans;

	if (!(data[0] = get_interval(object, "<transformations>",
			"</transformations>"))
		|| !(data[1] = get_interval(data[0], "<translation>", "</translation>"))
		|| !(data[2] = get_interval(data[0], "<rotation>", "</rotation>"))
		|| !(data[3] = get_interval(data[0], "<scale>", "</scale>"))
		|| (parsing_dot(data[1], &trans.trans) == -1)
		|| (parsing_dot(data[2], &trans.rot) == -1)
		|| (parsing_dot(data[3], &trans.scale) == -1))
		exit_custom_error("rt", ":parsing_transformations() failed");
	if (trans.scale.x < 1 || trans.scale.y < 1 || trans.scale.z < 1)
		exit_custom_error("rt", ":scale must be between <1 - x>");
	free(data[0]);
	free(data[1]);
	free(data[2]);
	free(data[3]);
	return (trans);
}

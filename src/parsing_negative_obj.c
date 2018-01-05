/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_negative_obj.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 00:21:37 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/05 05:32:02 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parsing_negative_obj(t_object *obj, char *object)
{
	char		*data[3];
	t_object	*neg_obj;
	t_list_objs	*n;
	
	n = obj->negative_obj;
	if ((data[0] = get_interval(object, "<negative_obj>", "</negative_obj>")))
	{
		while ((data[1] = get_interval(data[0], "<object>", "</object>")))
		{
			if (!(neg_obj = parsing_object2(data[1])))
				exit_custom_error("rt", ":parsing_negative_obj() failed");
			if (!(data[2] = get_interval(data[1], "<status>", "</status>")))
				exit_custom_error("rt", ":parsing_negative_obj() failed");
			if ((neg_obj->status = get_status(data[2])) == -1)
				exit_custom_error("rt", ":parsing_negative_obj() failed");
			parsing_transformations(neg_obj, data[1]);
			parsing_limit(neg_obj, data[1]);
			parsing_negative_obj(neg_obj, data[1]);
			data[0] = ft_strstr(data[0], "<object>") +
				ft_strlen("<object></object>") + ft_strlen(data[1]);
			free(data[2]);
			free(data[1]);
			new_cell_obj(&obj->negative_obj, neg_obj);
		}
		free(data[0]);
	}
}

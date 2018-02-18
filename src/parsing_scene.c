/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 14:48:47 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/18 16:38:05 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parsing_effects(char *data, t_scene *scn)
{
	int	i;
	char	*tmp;

	i = -1;
	while (*data && ft_isspace(*data))
		data++;
	tmp = NULL;
	while (tmp != data && *data)
	{
		tmp = data;
		data = parsing_anaglyph(data, scn, &i);
		data = parsing_blur(data, scn, &i);
		data = parsing_bwnoise(data, scn, &i);
		data = parsing_cartoon(data, scn, &i);
		data = parsing_duotone(data, scn, &i);
		data = parsing_gray(data, scn, &i);
		data = parsing_laplacian(data, scn, &i);
		data = parsing_lofi(data, scn, &i);
		data = parsing_motionblur(data, scn, &i);
		data = parsing_negative(data, scn, &i);
		data = parsing_noise(data, scn, &i);
		data = parsing_pop(data, scn, &i);
		data = parsing_prewitt(data, scn, &i);
		data = parsing_sepia(data, scn, &i);
	}
}

t_scene		*parsing_scene(char *scene)
{
	int			brightness;
	char		*data;
	t_scene		*scn;
	t_camera	cam;

	if (parsing_camera(scene, &cam))
		exit_custom_error("rt", ":parsing_camera() failed");
	if (!(data = get_interval(scene, "<brightness>", "</brightness>")))
		return (NULL);
	if (between(brightness = atod(data), 0, 100) == -1)
		exit_custom_error("rt", ":brightness must be between <0 - 100>");
	free(data);
	scn = new_scene(cam, brightness);
	if ((data = get_interval(scene, "<effects>", "</effects>")))
	{
		parsing_effects(data, scn);
		free(data);
	}
	return (scn);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 14:43:47 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/26 12:55:35 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			parsing_vector(char *data_vector, t_vector *d)
{
	char	*x;
	char	*y;
	char	*z;

	if (!(x = get_interval(data_vector, "<x>", "</x>"))
			|| !(y = get_interval(data_vector, "<y>", "</y>"))
			|| !(z = get_interval(data_vector, "<z>", "</z>")))
		return (-1);
	*d = vector(atod(x), atod(y), atod(z));
	free(x);
	free(y);
	free(z);
	return (0);
}

int			parsing_dot(char *data_dot, t_dot *d)
{
	char	*x;
	char	*y;
	char	*z;

	if (!(x = get_interval(data_dot, "<x>", "</x>"))
			|| !(y = get_interval(data_dot, "<y>", "</y>"))
			|| !(z = get_interval(data_dot, "<z>", "</z>")))
		return (-1);
	*d = dot(atod(x), atod(y), atod(z));
	free(x);
	free(y);
	free(z);
	return (0);
}

int			parsing_color(char *data_color, SDL_Color *c)
{
	char	*r;
	char	*g;
	char	*b;

	if (!(r = get_interval(data_color, "<r>", "</r>"))
			|| !(g = get_interval(data_color, "<g>", "</g>"))
			|| !(b = get_interval(data_color, "<b>", "</b>")))
		return (-1);
	*c = (SDL_Color){atoi(r), atoi(g), atoi(b), 255};
	free(r);
	free(g);
	free(b);
	return (0);
}

void		parsing_physic(char *data_physic, t_objs_comp *args)
{
	char	*data[4];

	args->refraction_amount = 0;
	args->refractive_index = 0;
	args->reflection_amount = 0;
	args->shininess = 30;
	if ((data[0] = get_interval(data_physic, "<refraction_amount>",
					"</refraction_amount>")))
		if (between(args->refraction_amount = atod(data[0]), 0, 1) == -1)
			exit_custom_error("rt", ":refraction_amount must be between <0 - 1.0>");
	if ((data[1] = get_interval(data_physic, "<refraction_index>",
					"</refraction_index>")))
		if (args->refraction_amount != 0 &&
				(args->refractive_index = atod(data[1])) < 1)
			exit_custom_error("rt", ":refractive_index must be greater than <1>");
	if ((data[2] = get_interval(data_physic, "<reflexion_amount>",
					"</reflexion_amount>")))
		if (between(args->reflection_amount = atod(data[2]), 0, 1) == -1)
			exit_custom_error("rt", ":reflection_amount must be between <0 - 1.0>");
	if ((data[3] = get_interval(data_physic, "<shininess>", "</shininess>")))
		if (between(args->shininess = atod(data[3]), 0, 100) == -1)
			exit_custom_error("rt", ":shininess must be between <0 - 100>");
	free(data[0]);
	free(data[1]);
	free(data[2]);
	free(data[3]);
}

t_scene		*parsing(int argc, char **argv)
{
	t_scene	*scn;
	char	*file;
	char	*scene;
	int		fd;

	scn = NULL;
	if (argc == 2 && argv[1] && ft_strstr(argv[1], ".xml"))
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			exit_custom_error("rt", ":open() failed");
		if (get_file_to_string(fd, &file) == -1)
			exit_custom_error("rt", ":get_file_to_string() failed");
		if (!(scene = get_interval(file, "<scene>", "</scene>"))
				|| !(scn = parsing_scene(scene)))
			exit_custom_error("rt", ":parsing_scene() failed");
		if (!(scn->lights = parsing_light(scene)))
			exit_custom_error("rt", ":parsing_light() failed");
		if (!(scn->objects = parsing_object(scene)))
			exit_custom_error("rt", ":parsing_object() failed");
		if (close(fd) == -1)
			exit_custom_error("rt", ":close() failed");
		free(scene);
		free(file);
	}
	return (scn);
}

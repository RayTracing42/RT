/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 14:43:47 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/15 16:24:05 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	free_data_norme(char *data[4])
{
	free(data[0]);
	free(data[1]);
	free(data[2]);
	free(data[3]);
}

void		parsing_physic(char *data_physic, t_objs_comp *args)
{
	char	*data[4];

	args->refraction_amount = 0;
	args->refractive_index = 0;
	args->reflection_amount = 0;
	args->shininess = 0;
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
	free_data_norme(data);
}

static void	end_fct_norme(int fd, char *file, char *scene)
{
	get_sdl_core()->nb_threads = fd;
	get_pxl_queue(fd);
	free(scene);
	free(file);
}

t_scene		*parsing(int argc, char **argv)
{
	t_scene	*scn;
	char	*file;
	char	*scene;
	int		fd;

	scn = NULL;
	if ((argc == 2 || (argc == 3 && ft_atoi(argv[2]) > 0)) && argv[1] && ft_strstr(argv[1], ".xml"))
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			exit_custom_error("rt", ":open() failed");
		if (get_file_to_string(fd, &file) == -1)
			exit_custom_error("rt", ":get_file_to_string() failed");
		if (!(scene = get_interval(file, "<scene>", "</scene>"))
				|| !(scn = parsing_scene(scene)))
			exit_custom_error("rt", ":parsing_scene() failed");
		if (!(scn->lights = parsing_light(scene, &scn->objects)))
			ft_putstr_fd("\nWarning: no light found!\n", 2);
		if (!(scn->objects = parsing_object(scene, scn->objects)))
			ft_putstr_fd("\nWarning: no object found!\n", 2);
		if (close(fd) == -1)
			exit_custom_error("rt", ":close() failed");
		fd = (argc == 3 ? ft_atoi(argv[2]) : 1);
		end_fct_norme(fd, file, scene);
	}
	return (scn);
}

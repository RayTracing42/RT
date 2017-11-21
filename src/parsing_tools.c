/*============================================================================*/
/*                                                                            */
/*        fichier :   parsing_tools.c                                         */
/*                                                                            */
/*        auteur  :   fcecilie                                                */
/*        adresse :   fcecilie@student.42.fr                                  */
/*                                                                            */
/*============================================================================*/

#include "rt.h"

/*
**	get_interval() retourne l'intervalle alloué entre deux strings valides;
**	Retourne NULL si l'un des parametres n'est pas valide;
**	Retourne NULL si l'intervalle est inexistant : "";
**	Retourne NULL si start et stop ne sont pas trouvés dans src;
*/

int		value_is_in_interval(double value, double low_limit, double height_limit)
{
	if (value < low_limit || value > height_limit)
		return (-1);
	return (1);
}

double	int_to_decimal(int n)
{
	double	d;

	d = (double)n;
	while (d > 1 || d < -1)
		d = d / 10;
	return (d);
}

double	atod(char *src)
{
	double	integer_part;
	double	decimal_part;
	int		tmp_decimal;

	decimal_part = 0.0;
	integer_part = (double)atoi(src);
	if (ft_strchr(src, '.'))
	{
		tmp_decimal = atoi((src + ft_strnlen(src, '.') + 1));
		decimal_part = int_to_decimal(tmp_decimal);
	}
	return (integer_part + decimal_part);
}

char	*get_interval(const char *src, const char *start, const char *stop)
{
	const char	*ptr_start;
	const char	*ptr_stop;
	char		*dst;
	int			len_dst;

	dst = NULL;
	if (src && ft_strcmp(src, "") && start && ft_strcmp(start, "")
		&& stop && ft_strcmp(stop, ""))
	{
		if ((ptr_start = ft_strstr(src, start)))
		{
			ptr_start = ptr_start + ft_strlen(start);
			if ((ptr_stop = ft_strstr(ptr_start, stop))
				&& (len_dst = ft_strlen(ptr_start) - ft_strlen(ptr_stop)) > 0)
			{
				if ((dst = (char *)ft_memalloc(len_dst + 1)))
					dst = ft_strncpy(dst, ptr_start, len_dst);
			}
		}
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 14:47:51 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/04 02:43:37 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	get_interval() retourne l'intervalle alloué entre deux strings valides;
**	Retourne NULL si l'un des parametres n'est pas valide;
**	Retourne NULL si l'intervalle est inexistant : "";
**	Retourne NULL si start et stop ne sont pas trouvés dans src;
*/

int		between(double value, double low_limit, double height_limit)
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

int		get_nb_occ(const char *src, const char *occ, int lim)
{
	const char	*current;
	int			n;
	
	n = 0;
	current = src;
	if (src && ft_strcmp(src, "") && occ && ft_strcmp(occ, "")
		&& lim <= (int)ft_strlen(src) && lim >= 0)
	{
		while ((current = ft_strstr(current, occ)))
		{
			current = current + ft_strlen(occ);
			if (ft_strlen(current) < ft_strlen(src + lim))
				return (n);
			n++;
		}
		return (n);
	}
	return (-1);
}

char	*get_interval(const char *src, const char *start, const char *stop)
{
	const char	*ptr_start;
	const char	*ptr_stop;
	char		*dst;
	int			len_dst;
	int			occ_start;
	int			n;

	dst = NULL;
	if (src && ft_strcmp(src, "") && start && ft_strcmp(start, "")
		&& stop && ft_strcmp(stop, ""))
	{
		if ((ptr_start = ft_strstr(src, start))
			&& (ptr_stop = ft_strstr(ptr_start + ft_strlen(start), stop)))
		{
			ptr_start = ptr_start + ft_strlen(start);
			occ_start = get_nb_occ(ptr_start, start,
				ft_strlen(ptr_start) - ft_strlen(ptr_stop));
			n = 0;
			while (n < occ_start)
			{
				ptr_stop = ptr_stop + ft_strlen(stop);
				if (!(ptr_stop = ft_strstr(ptr_stop, stop)))
					return (NULL);
				occ_start = get_nb_occ(ptr_start, start,
					ft_strlen(ptr_start) - ft_strlen(ptr_stop));
				n++;
			}
			if ((len_dst = ft_strlen(ptr_start) - ft_strlen(ptr_stop)) > 0)
			{
				if ((dst = (char *)ft_memalloc(len_dst + 1)))
					dst = ft_strncpy(dst, ptr_start, len_dst);
			}
		}
	}
	return (dst);
}

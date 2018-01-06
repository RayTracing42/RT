/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_interval.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 02:24:44 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/06 06:46:42 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*cut_interval(char *src, const char *interval)
{
	char	*final;
	char	*ptr_inter;
	int		len_inter;
	int		len_src;
	int		len_first;
	int		len_final;

	if (src && ft_strcmp(src, "") && interval && ft_strcmp(interval, ""))
	{
		ptr_inter = ft_strstr(src, interval);
		len_inter = ft_strlen(interval);
		len_src = ft_strlen(src);
		len_final = len_src - len_inter;
		len_first = len_src - ft_strlen(ptr_inter);
		if (!(final = ft_memalloc(len_final + 1)))
			return (NULL);
		ft_strncpy(final, src, len_first);
		ft_strcat(final, ptr_inter + len_inter);
		return (final);
	}
	return (NULL);
}

int		get_order_of_apparition(const char *src, const char *s1, const char *s2)
{
	char	*str1;
	char	*str2;
	int		len1;
	int		len2;

	str1 = NULL;
	str2 = NULL;
	str1 = ft_strstr(src, s1);
	str2 = ft_strstr(src, s2);
	if (!(str1) && !(str2))
		return (0);
	if (str1 && !str2)
		return (1);
	if (str2 && !str1)
		return (2);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 > len2)
		return (1);
	else
		return (2);
}

char	*get_order_buffer(const char *src, const char *start, const char *stop)
{
	char	*buffer;
	int		n;
	int		order;

	if (!(buffer = ft_memalloc(ft_strlen(src) + 1)))
		return (NULL);
	n = 0;
	while ((order = get_order_of_apparition(src, start, stop)))
	{
		buffer[n] = order + '0';
		if (order == 1)
			src = ft_strstr(src, start) + ft_strlen(start);
		if (order == 2)
			src = ft_strstr(src, stop) + ft_strlen(stop);
		n++;
	}
	if (n == 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[n] = '\0';
	return (buffer);
}

char	*get_stop_ptr(const char *src, char *buffer, const char *start,
	const char *stop)
{
	char	*ptr;
	int		len_start;
	int		len_stop;
	int		status;
	int		n;
	
	status = -1;
	n = 0;
	len_start = ft_strlen(start);
	len_stop = ft_strlen(stop);
	while (buffer[n] && status)
	{
		if (status == -1)
			status++;
		if (buffer[n] == '1')
		{
			ptr = ft_strstr(src, start) + len_start;
			status++;
		}
		if (buffer[n] == '2')
		{
			ptr = ft_strstr(src, stop) + len_stop;
			status--;
		}
		n++;
	}
	return (ptr);
}

char	*get_interval(char **src, const char *start, const char *stop)
{
	char		*dst;
	char		*cut;
	char		*buffer;
	char		*ptr_stop;
	char		*ptr_start;

	dst = NULL;
	if (*src && ft_strcmp(*src, "") && start && ft_strcmp(start, "")
			&& stop && ft_strcmp(stop, ""))
	{
		if ((buffer = get_order_buffer(*src, start, stop)))
		{
			ptr_stop = get_stop_ptr(*src, buffer, start, stop) - ft_strlen(stop);
			ptr_start = ft_strstr(*src, start);
			if ((dst = (char *)ft_memalloc(ft_strlen(ptr_start +
				ft_strlen(start)) - ft_strlen(ptr_stop) + 1)))
			{
				if ((cut = (char *)ft_memalloc(ft_strlen(ptr_start) -
					ft_strlen(ptr_stop) + ft_strlen(stop) + 1)))
				{
dst = ft_strncpy(dst, ptr_start + ft_strlen(start), 
		ft_strlen(ptr_start + ft_strlen(start)) - ft_strlen(ptr_stop));
					cut = ft_strncpy(cut, ptr_start, ft_strlen(ptr_start) -
						ft_strlen(ptr_stop) + ft_strlen(stop));
					cut = cut_interval(*src, cut);
			//		free(*src);
//					free(buffer);
					*src = cut;
//					printf("stt : %s\n", ptr_start);
//					printf("stp : %s\n", ptr_stop);
//					printf("dst : %s\n", dst);
//					printf("cut : %s\n", cut);
				}
			}
		}
	}
	return (dst);
}

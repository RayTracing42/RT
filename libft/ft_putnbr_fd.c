/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 13:46:06 by edescoin          #+#    #+#             */
/*   Updated: 2017/02/10 18:49:23 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	l;
	char	c;

	l = (long)n;
	if (n < 0)
	{
		write(fd, "-", 1);
		l = -l;
	}
	if (n > 9 || n < -9)
		ft_putnbr_fd((int)(l / 10), fd);
	c = '0' + (l % 10);
	write(fd, &c, 1);
}

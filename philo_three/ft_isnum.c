/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:34:14 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/30 03:48:23 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_isnum(const char *ptr)
{
	char	*tmp;

	tmp = (char *)ptr;
	if (*tmp == '-' || *tmp == '+')
		tmp++;
	while (*tmp)
		if (*tmp < '0' || *tmp++ > '9')
			return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 22:21:49 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/08 20:04:28 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	ft_atol(const char *str)
{
	char		*ptr_str;
	long int	to_dec;
	int			is_neg;

	is_neg = 1;
	to_dec = 0;
	ptr_str = (char *)str;
	if (*ptr_str == '-' || *ptr_str == '+')
		if (*ptr_str++ == '-')
			is_neg = ~(is_neg - 1);
	while (*ptr_str++)
		to_dec = (to_dec * 10) + (*(ptr_str - 1) - '0');
	return (to_dec * is_neg);
}

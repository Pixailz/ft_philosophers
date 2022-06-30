/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 00:49:42 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/19 17:31:46 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atol(const char *ptr)
{
	const char	*tmp_ptr;
	long		nb_ptr;
	int			is_neg;

	nb_ptr = 0;
	is_neg = 1;
	tmp_ptr = (char *)ptr;
	while (*tmp_ptr == ' ' || (*tmp_ptr >= '\t' && *tmp_ptr <= '\r'))
		tmp_ptr++;
	if (*tmp_ptr == '+' || *tmp_ptr == '-')
		if (*tmp_ptr++ == '-')
			is_neg = ~(is_neg - 1);
	while (*tmp_ptr >= '0' && *tmp_ptr <= '9')
		nb_ptr = (nb_ptr * 10) + (*tmp_ptr++ & 0xF);
	return (nb_ptr * is_neg);
}

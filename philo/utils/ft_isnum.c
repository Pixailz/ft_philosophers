/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:24:48 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/02 23:12:28 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isnumeric(const char *str)
{
	char	*ptr_str;

	ptr_str = (char *)str;
	if (*ptr_str == '-' || *ptr_str == '+')
		ptr_str++;
	while (*ptr_str++)
		if (*(ptr_str - 1) <= '0' || *(ptr_str - 1) >= '9')
			return (0);
	return (1);
}

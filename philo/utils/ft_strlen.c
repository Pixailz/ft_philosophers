/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 23:14:08 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/02 23:15:18 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(const char *str)
{
	char	*ptr_str;

	ptr_str = (char *)str;
	while (*ptr_str)
		ptr_str++;
	return (ptr_str - str);
}

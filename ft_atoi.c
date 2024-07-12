/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miguiji <miguiji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:02:46 by miguiji           #+#    #+#             */
/*   Updated: 2024/07/07 11:02:50 by miguiji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	a;

	a = 0;
	signe = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45)
	{
		signe = signe * -1;
		i++;
	}
	else if (str[i] == 43)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		a = a * 10 + str[i] - 48;
		i++;
	}
	return (a * signe);
}

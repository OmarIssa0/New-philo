/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_philo_ate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:23:05 by oissa             #+#    #+#             */
/*   Updated: 2025/01/21 13:10:49 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	all_philosophers_ate(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->num_philosophers)
	{
		if (simulation->philosopher[i].meals_eaten < simulation->num_each_eat)
			return (false);
		i++;
	}
	return (true);
}

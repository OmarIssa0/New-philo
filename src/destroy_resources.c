/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_resources.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 19:01:24 by oissa             #+#    #+#             */
/*   Updated: 2025/01/19 17:43:10 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_resources(t_simulation *simulation)
{
	int	i;

	i = 0;
	if (simulation->fork)
	{
		while (i < simulation->num_philosophers)
		{
			pthread_mutex_destroy(&simulation->fork[i]);
			i++;
		}
		free(simulation->fork);
	}
	pthread_mutex_destroy(&simulation->print_mutex);
	pthread_mutex_destroy(&simulation->data_lock);
	if (simulation->philosopher)
		free(simulation->philosopher);
}

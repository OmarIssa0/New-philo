/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:28:05 by oissa             #+#    #+#             */
/*   Updated: 2025/01/19 17:22:21 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_died(t_simulation *simulation, int i)
{
	pthread_mutex_lock(&simulation->data_lock);
	if (time_of_philo()
		- simulation->philosopher[i].last_meal_time > simulation->time_to_die)
	{
		pthread_mutex_lock(&simulation->print_mutex);
		printf(RED "%lld\t%d  died" RESET "\n", time_of_philo()
			- simulation->start_time, simulation->philosopher[i].id);
		pthread_mutex_unlock(&simulation->print_mutex);
		simulation->is_running = false;
		pthread_mutex_unlock(&simulation->data_lock);
		return (EXIT_FAILURE);
	}
	pthread_mutex_unlock(&simulation->data_lock);
	usleep(1000);
	return (EXIT_SUCCESS);
}

void	*monitor_death(void *arg)
{
	int				i;
	t_simulation	*simulation;

	simulation = (t_simulation *)arg;
	while (1)
	{
		i = 0;
		while (i < simulation->num_philosophers)
		{
			if (check_died(simulation, i) == EXIT_FAILURE)
				return (NULL);
			i++;
		}
		pthread_mutex_lock(&simulation->data_lock);
		if (simulation->num_each_eat != -1 && all_philosophers_ate(simulation))
		{
			simulation->is_running = false;
			pthread_mutex_unlock(&simulation->data_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&simulation->data_lock);
	}
	return (NULL);
}

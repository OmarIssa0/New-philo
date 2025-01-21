/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:21:02 by oissa             #+#    #+#             */
/*   Updated: 2025/01/19 00:31:28 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	pthread_monitor(t_simulation *simulation, pthread_t *threads,
		pthread_t monitor_thread)
{
	int	i;

	if (pthread_create(&monitor_thread, NULL, monitor_death, simulation) != 0)
	{
		printf("ERROR: Failed to create monitor thread\n");
		free(threads);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < simulation->num_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
	free(threads);
	return (EXIT_SUCCESS);
}

int	start_simulation(t_simulation *simulation)
{
	pthread_t	*threads;
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	monitor_thread = 0;
	threads = malloc(sizeof(pthread_t) * simulation->num_philosophers);
	if (!threads)
		return (EXIT_FAILURE);
	while (i < simulation->num_philosophers)
	{
		if (pthread_create(&threads[i], NULL, philo_routine,
				&simulation->philosopher[i]) != 0)
		{
			printf("ERROR: Failed to create thread for philosopher %d\n", i
				+ 1);
			free(threads);
			return (EXIT_FAILURE);
		}
		i++;
	}
	if (pthread_monitor(simulation, threads, monitor_thread) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

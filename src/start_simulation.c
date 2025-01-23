/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:21:02 by oissa             #+#    #+#             */
/*   Updated: 2025/01/23 20:59:46 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	pthread_monitor(t_simulation *simulation, pthread_t *threads)
{
	int	i;

	monitor_death(simulation);
	i = 0;
	while (i < simulation->num_philosophers)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	return (EXIT_SUCCESS);
}

int	start_simulation(t_simulation *simulation)
{
	pthread_t	*threads;
	int			i;

	i = 0;
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
	if (pthread_monitor(simulation, threads) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

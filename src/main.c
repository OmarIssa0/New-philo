/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:29:31 by oissa             #+#    #+#             */
/*   Updated: 2025/01/19 17:33:30 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_init(t_simulation *simulation, int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("ERROR: ./philo 5 800 200 200 [option]\n");
		return (EXIT_FAILURE);
	}
	if (init_argument(simulation, ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_forks(simulation) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_philosophers(simulation) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (start_simulation(simulation) == EXIT_FAILURE)
	{
		destroy_resources(simulation);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_simulation	simulation;

	memset(&simulation, 0, sizeof(t_simulation));
	simulation.start_time = time_of_philo();
	simulation.is_running = true;
	if (pthread_mutex_init(&simulation.print_mutex, NULL)
		|| pthread_mutex_init(&simulation.data_lock, NULL) != 0)
	{
		printf("ERROR: Failed to initialize mutexes\n");
		return (EXIT_FAILURE);
	}
	if (check_init(&simulation, ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	destroy_resources(&simulation);
	return (EXIT_SUCCESS);
}

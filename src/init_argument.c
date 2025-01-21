/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_argument.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:05:22 by oissa             #+#    #+#             */
/*   Updated: 2025/01/21 23:04:51 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_argument(t_simulation *simulation, int ac, char **av)
{
	t_var_long	var_long;

	var_long.num_philosophers = ft_atol_handle(av[1], &var_long.valid);
	var_long.time_to_die = ft_atol_handle(av[2], &var_long.valid);
	var_long.time_to_eat = ft_atol_handle(av[3], &var_long.valid);
	var_long.time_to_sleep = ft_atol_handle(av[4], &var_long.valid);
	if (ac == 5)
		simulation->num_each_eat = -1;
	else
		var_long.num_each_eat = ft_atol_handle(av[5], &var_long.valid);
	if (var_long.num_philosophers <= 0 || var_long.time_to_die <= 0
		|| var_long.time_to_eat <= 0 || var_long.time_to_sleep <= 0
		|| (ac == 6 && var_long.num_each_eat <= 0)
		|| var_long.valid == 0)
	{
		printf("ERROR: value argument\n");
		return (EXIT_FAILURE);
	}
	simulation->num_philosophers = var_long.num_philosophers;
	simulation->time_to_die = var_long.time_to_die;
	simulation->time_to_eat = var_long.time_to_eat;
	simulation->time_to_sleep = var_long.time_to_sleep;
	if (ac == 6)
		simulation->num_each_eat = var_long.num_each_eat;
	return (EXIT_SUCCESS);
}

int	init_forks(t_simulation *simulation)
{
	int	i;

	i = 0;
	simulation->fork = malloc(sizeof(pthread_mutex_t)
			* simulation->num_philosophers);
	if (!simulation->fork)
		return (EXIT_FAILURE);
	while (i < simulation->num_philosophers)
	{
		if (pthread_mutex_init(&simulation->fork[i], NULL) != 0)
		{
			destroy_resources(simulation);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	init_philosophers(t_simulation *simulation)
{
	int	i;

	i = 0;
	simulation->philosopher = malloc(sizeof(t_philosophers)
			* simulation->num_philosophers);
	if (!simulation->philosopher)
		return (EXIT_FAILURE);
	while (i < simulation->num_philosophers)
	{
		simulation->philosopher[i].id = i + 1;
		simulation->philosopher[i].meals_eaten = 0;
		simulation->philosopher[i].last_meal_time = time_of_philo();
		simulation->philosopher[i].right_fork = &simulation->fork[(i + 1)
			% simulation->num_philosophers];
		simulation->philosopher[i].left_fork = &simulation->fork[i];
		simulation->philosopher[i].simulation = simulation;
		i++;
	}
	return (EXIT_SUCCESS);
}

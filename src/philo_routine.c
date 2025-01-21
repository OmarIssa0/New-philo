/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:29:41 by oissa             #+#    #+#             */
/*   Updated: 2025/01/21 17:04:04 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	if_philo_num_one(t_philosophers *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->simulation->print_mutex);
	if (philo->simulation->is_running)
		printf(GREEN "%lld\t%d  has taken a fork" RESET "\n",
			time_of_philo() - philo->simulation->start_time,
			philo->id);
	pthread_mutex_unlock(&philo->simulation->print_mutex);
	precise_sleep(time_of_philo(), philo->simulation->time_to_die, philo);
	pthread_mutex_unlock(philo->left_fork);
}

static int	break_if(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->simulation->data_lock);
	if (!philo->simulation->is_running || (philo->simulation->num_each_eat != -1
			&& philo->meals_eaten >= philo->simulation->num_each_eat))
	{
		pthread_mutex_unlock(&philo->simulation->data_lock);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	is_running_check(t_philosophers *philo)
{
	if (!philo->simulation->is_running)
	{
		pthread_mutex_unlock(&philo->simulation->data_lock);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	get_value(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->simulation->data_lock);
	philo->simulation_start_time = time_of_philo();
	pthread_mutex_unlock(&philo->simulation->data_lock);
}

void	*philo_routine(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	philo->simulation_start_time = time_of_philo();
	while (1)
	{
		get_value(philo);
		if (break_if(philo) == EXIT_FAILURE)
			break ;
		thinking_philo(philo);
		if (philo->simulation->num_philosophers == 1)
		{
			if_philo_num_one(philo);
			break ;
		}
		else
			lock_fork(philo);
		pthread_mutex_lock(&philo->simulation->data_lock);
		if (is_running_check(philo) == EXIT_FAILURE)
			break ;
		eating_philo(philo);
		check_is_running(philo);
	}
	return (NULL);
}

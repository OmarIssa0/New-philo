/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:06:59 by oissa             #+#    #+#             */
/*   Updated: 2025/01/21 23:19:06 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long	time_of_philo(void)
{
	struct timeval	time;
	long long		current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (current_time);
}

void	precise_sleep(long long start_time, long long duration_ms,
						t_philosophers *philo)
{
	long long	end_time;

	end_time = start_time + duration_ms;
	while (time_of_philo() < end_time)
	{
		pthread_mutex_lock(&philo->simulation->data_lock);
		if (!philo->simulation->is_running)
		{
			pthread_mutex_unlock(&philo->simulation->data_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->simulation->data_lock);
		usleep(1);
	}
}

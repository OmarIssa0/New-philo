/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_too.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:27:17 by oissa             #+#    #+#             */
/*   Updated: 2025/01/23 19:44:04 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	thinking_philo(t_philosophers *philo)
{
	pthread_mutex_unlock(&philo->simulation->data_lock);
	pthread_mutex_lock(&philo->simulation->data_lock);
	// pthread_mutex_lock(&philo->simulation->print_mutex);
	
	if (philo->simulation->is_running)
	{
		
		pthread_mutex_lock(&philo->simulation->print_mutex);
		printf(BLUE "%lld\t%d  is thinking" RESET "\n", time_of_philo()
			- philo->simulation->start_time, philo->id);
		pthread_mutex_unlock(&philo->simulation->print_mutex);
	}
	pthread_mutex_unlock(&philo->simulation->data_lock);
	// pthread_mutex_unlock(&philo->simulation->print_mutex);
}

void	eating_philo(t_philosophers *philo)
{
	pthread_mutex_unlock(&philo->simulation->data_lock);
	
	pthread_mutex_lock(&philo->simulation->data_lock);
	pthread_mutex_lock(&philo->simulation->print_mutex);
	printf(PURPLE "%lld\t%d  has taken a fork" RESET "\n", time_of_philo()
		- philo->simulation->start_time, philo->id);
	printf(PURPLE "%lld\t%d  has taken a fork" RESET "\n", time_of_philo()
		- philo->simulation->start_time, philo->id);
	pthread_mutex_unlock(&philo->simulation->print_mutex);
	
	// pthread_mutex_lock(&philo->simulation->print_mutex);
	// pthread_mutex_lock(&philo->simulation->data_lock);
	if (philo->simulation->is_running)
	{
		pthread_mutex_lock(&philo->simulation->print_mutex);
		printf(YELLOW "%lld\t%d  is eating" RESET "\n", time_of_philo()
			- philo->simulation->start_time, philo->id);
		pthread_mutex_unlock(&philo->simulation->print_mutex);
	}
	
	// pthread_mutex_unlock(&philo->simulation->data_lock);
	// pthread_mutex_lock(&philo->simulation->data_lock);
	philo->last_meal_time = time_of_philo();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->simulation->data_lock);
	
	precise_sleep(time_of_philo(), philo->simulation->time_to_eat, philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	
	pthread_mutex_lock(&philo->simulation->data_lock);
}

void	check_is_running(t_philosophers *philo)
{
		pthread_mutex_lock(&philo->simulation->print_mutex); 
	if (philo->simulation->is_running)
	{
		printf(GREEN "%lld\t%d  is sleeping" RESET "\n", time_of_philo()
			- philo->simulation->start_time, philo->id);
	}
		pthread_mutex_unlock(&philo->simulation->print_mutex);
	pthread_mutex_unlock(&philo->simulation->data_lock);
	precise_sleep(time_of_philo(), philo->simulation->time_to_sleep, philo);
}

void	lock_fork(t_philosophers *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
}

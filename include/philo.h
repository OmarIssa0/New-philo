/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oissa <oissa@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:29:42 by oissa             #+#    #+#             */
/*   Updated: 2025/01/21 17:03:14 by oissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"
# define PURPLE "\033[0;35m"
# define WHITE "\033[0;37m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[0;33m"

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/*
	! Philo struct
*/
typedef struct s_philosopher
{
	int					id;
	int					meals_eaten;
	long				last_meal_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_simulation	*simulation;
	long long			simulation_start_time;
}						t_philosophers;

/*
	! Simulation struct
*/
typedef struct s_simulation
{
	long				start_time;
	bool				is_running;
	int					num_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					num_each_eat;
	pthread_mutex_t		*fork; // ? 5 -> 5 fork and 5 philo
	t_philosophers		*philosopher;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		data_lock;
}						t_simulation;

/*
	! Var_long
	* atol handle
*/
typedef struct s_var_long
{
	long				num_philosophers;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				num_each_eat;
	int					valid;
}						t_var_long;

long					ft_atol_handle(const char *str, int *valid);
void					destroy_resources(t_simulation *simulation);
int						init_argument(t_simulation *simulation, int ac,
							char **av);
int						init_forks(t_simulation *simulation);
int						init_philosophers(t_simulation *simulation);
void					*monitor_death(void *arg);
void					*philo_routine(void *arg);
bool					all_philosophers_ate(t_simulation *simulation);
int						start_simulation(t_simulation *simulation);
long long				time_of_philo(void);
int						start_simulation(t_simulation *simulation);
bool					all_philosophers_ate(t_simulation *simulation);
void					*monitor_death(void *arg);
void					*philo_routine(void *arg);
void					thinking_philo(t_philosophers *philo);
void					eating_philo(t_philosophers *philo);
void					check_is_running(t_philosophers *philo);
void					lock_fork(t_philosophers *philo);
void					precise_sleep(long long start_time,
							long long duration_ms, t_philosophers *philo);

#endif

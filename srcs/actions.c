/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 19:55:40 by numussan          #+#    #+#             */
/*   Updated: 2022/11/24 20:57:27 by numussan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_check_death(void *tmp)
{
	t_global	*global;
	t_philo		*philo;
	int			i;

	global = tmp;
	philo = global->philo;
	while (1)
	{
		i = -1;
		while (++i < global->number_of_philos)
		{
			// pthread_mutex_lock(&global->c_eat);
			if (global->count_of_lunch)
			{
				if (philo->count_eat == global->count_of_lunch)
				{
					// pthread_mutex_unlock(&global->c_eat);
					return (NULL);
				}
			}
			// pthread_mutex_unlock(&global->c_eat);
			// pthread_mutex_lock(&global->c_eat);
			if (ft_current_time() - philo[i].last_eat > philo[i].time_to_die)
			{
				pthread_mutex_lock(&global->print_action);
				global->death = 1;
				printf("%lld %d is died\n", \
					ft_current_time() - philo->time_start, philo->id_philo);
				pthread_mutex_unlock(&global->print_action);
				// pthread_mutex_unlock(&global->c_eat);
				return (NULL);
			}
			// pthread_mutex_unlock(&global->c_eat);
		}
	}
	return (NULL);
}

void	ft_thinking(t_global *global, t_philo *philo)
{
	if (global->death)
		return ;
	ft_print(global, philo, "is thinking");
}

void	ft_sleeping(t_global *global, t_philo *philo)
{
	if (global->death)
		return ;
	ft_print(global, philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}


// check both fork available 
// lock left and id_right
// set status
// unlock both
// print_action
// sleeping
// lock
// change the status
// unlock
int	ft_eating(t_global *global, t_philo *philo)
{
	if (global->death)
		return (1);
	// if (philo->id_philo % 2 == 0)
		pthread_mutex_lock(&global->fork[philo->id_left]);

	// else
	// 	pthread_mutex_lock(&global->fork[philo->id_right]);

	ft_print(global, philo, "has taken a fork");
	if (global->number_of_philos == 1)
	{
		pthread_mutex_unlock(&global->fork[global->philo->id_left]);
		return (1);
	}
	// if (philo->id_philo % 2 == 0)
	pthread_mutex_lock(&global->fork[philo->id_right]);
	// else
	// 	pthread_mutex_lock(&global->fork[philo->id_left]);

	ft_print(global, philo, "has taken a fork");
	ft_print(global, philo, "is eating");
	// pthread_mutex_lock(&global->c_eat);
	philo->count_eat++;
	// pthread_mutex_unlock(&global->c_eat);
	philo->last_eat = ft_current_time();
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&global->fork[philo->id_left]);
	pthread_mutex_unlock(&global->fork[philo->id_right]);
	return (0);
}

void	ft_print(t_global *global, t_philo *philo, char *str)
{
	if (global->death)
		return ;
	pthread_mutex_lock(&global->print_action);
	if (global->death)
		return ;
	printf("%lld %d %s\n", \
		ft_current_time() - philo->time_start, philo->id_philo, str);
	pthread_mutex_unlock(&global->print_action);
}

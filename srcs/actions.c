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
			pthread_mutex_unlock(&global->c_eat);
			pthread_mutex_lock(&global->mut_last);
			if (ft_current_time() - philo[i].last_eat > philo[i].time_to_die)
			{
				pthread_mutex_unlock(&global->mut_last);
				pthread_mutex_lock(&global->mut_death);
				global->death = 1;
				pthread_mutex_unlock(&global->mut_death);
				pthread_mutex_lock(&global->print_action);
				global->death = 1;
				printf("%lld %d is died\n", \
					ft_current_time() - philo->time_start, philo->id_philo);
				pthread_mutex_unlock(&global->print_action);
				return (NULL);
			}
			pthread_mutex_unlock(&global->mut_last);
		}
	}
	return (NULL);
}

void	ft_thinking(t_global *global, t_philo *philo)
{
	pthread_mutex_lock(&global->mut_death);
	if (global->death)
	{
		pthread_mutex_unlock(&global->mut_death);
		return ;
	}
	pthread_mutex_unlock(&global->mut_death);
	ft_print(global, philo, "is thinking");
}

void	ft_sleeping(t_global *global, t_philo *philo)
{
	pthread_mutex_lock(&global->mut_death);
	if (global->death)
	{
		pthread_mutex_unlock(&global->mut_death);
		return ;
	}
	pthread_mutex_unlock(&global->mut_death);
	ft_print(global, philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

// lock left - lock right
//print forks
// unlock l - unlock r
// print eating
// sleep

int	ft_eating(t_global *global, t_philo *philo)
{
	pthread_mutex_lock(&global->mut_death);
	if (global->death)
	{
		pthread_mutex_unlock(&global->mut_death);
		return (1);
	}
	pthread_mutex_unlock(&global->mut_death);
	if (philo->id_philo % 2 == 0)
		pthread_mutex_lock(&global->fork[philo->id_left]);
	else
		pthread_mutex_lock(&global->fork[philo->id_right]);
	ft_print(global, philo, "has taken a fork");
	if (global->number_of_philos == 1)
	{
		pthread_mutex_unlock(&global->fork[global->philo->id_left]);
		return (1);
	}
	if (philo->id_philo % 2 == 0)
		pthread_mutex_lock(&global->fork[philo->id_right]);
	else
		pthread_mutex_lock(&global->fork[philo->id_left]);
	ft_print(global, philo, "has taken a fork");
	pthread_mutex_unlock(&global->fork[philo->id_left]);
	pthread_mutex_unlock(&global->fork[philo->id_right]);
	ft_print(global, philo, "is eating");
	// pthread_mutex_lock(&global->c_eat);
	philo->count_eat++;
	pthread_mutex_unlock(&global->c_eat);
	pthread_mutex_lock(&global->mut_last);
	philo->last_eat = ft_current_time();
	pthread_mutex_unlock(&global->mut_last);
	ft_usleep(philo->time_to_eat);
	return (0);
}

void	ft_print(t_global *global, t_philo *philo, char *str)
{
	pthread_mutex_lock(&global->mut_death);
	if (global->death)
	{
		pthread_mutex_unlock(&global->mut_death);
		return ;
	}
	printf("%lld %d %s\n", \
		ft_current_time() - philo->time_start, philo->id_philo, str);
	pthread_mutex_unlock(&global->mut_death);
}

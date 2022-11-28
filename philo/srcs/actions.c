/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 19:55:40 by numussan          #+#    #+#             */
/*   Updated: 2022/11/28 21:35:41 by numussan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_check_time_die(t_global *global, t_philo *philo, int i)
{
	pthread_mutex_lock(&global->mut_last);
	if (ft_current_time() - philo[i].last_eat > philo[i].time_to_die)
	{
		pthread_mutex_unlock(&global->mut_last);
		pthread_mutex_lock(&global->mut_death);
		global->death = 1;
		pthread_mutex_unlock(&global->mut_death);
		pthread_mutex_lock(&global->print_action);
		printf("%lld %d is died\n", \
			ft_current_time() - philo->time_start, philo->id_philo);
		pthread_mutex_unlock(&global->print_action);
		return (1);
	}
	pthread_mutex_unlock(&global->mut_last);
	return (0);
}

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
			pthread_mutex_lock(&global->c_eat);
			if (global->count_of_lunch)
				if (philo->count_eat == global->count_of_lunch)
					return (pthread_mutex_unlock(&global->c_eat), NULL);
			pthread_mutex_unlock(&global->c_eat);
			if (ft_check_time_die(global, philo, i))
				return (NULL);
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

int	ft_eating(t_global *global, t_philo *philo)
{
	pthread_mutex_lock(&global->mut_death);
	if (global->death)
		return (pthread_mutex_unlock(&global->mut_death), 1);
	pthread_mutex_unlock(&global->mut_death);
	pthread_mutex_lock(&global->fork[philo->id_left]);
	ft_print(global, philo, "has taken a fork");
	if (global->number_of_philos == 1)
		return (pthread_mutex_unlock(&global->fork[philo->id_left]), 1);
	pthread_mutex_lock(&global->fork[philo->id_right]);
	ft_print(global, philo, "has taken a fork");
	ft_print(global, philo, "is eating");
	pthread_mutex_lock(&global->c_eat);
	philo->count_eat++;
	pthread_mutex_unlock(&global->c_eat);
	pthread_mutex_lock(&global->mut_last);
	philo->last_eat = ft_current_time();
	pthread_mutex_unlock(&global->mut_last);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&global->fork[philo->id_right]);
	pthread_mutex_unlock(&global->fork[philo->id_left]);
	return (0);
}

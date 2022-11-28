/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 19:36:07 by numussan          #+#    #+#             */
/*   Updated: 2022/11/28 23:37:08 by numussan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philo_start(void *tmp)
{
	t_philo		*philo;
	t_global	*global;

	philo = (t_philo *)tmp;
	global = philo->arg;
	if (philo->id_philo % 2 == 0)
	{
		ft_print(global, philo, "is thinking");
		usleep(philo->time_to_eat);
	}
	while (1)
	{
		pthread_mutex_lock(&global->mut_death);
		if (global->death)
			return (pthread_mutex_unlock(&global->mut_death), NULL);
		pthread_mutex_unlock(&global->mut_death);
		if (global->count_of_lunch)
			if (philo->count_eat == global->count_of_lunch)
				return (NULL);
		if (ft_eating(global, philo))
			return (NULL);
		ft_sleeping(global, philo);
		ft_thinking(global, philo);
	}
	return (NULL);
}

int	ft_start(t_global *global)
{
	int			i;
	pthread_t	check;

	i = -1;
	global->time_start = ft_current_time();
	while (++i < global->number_of_philos)
	{
		global->philo[i].time_start = global->time_start;
		global->philo[i].last_eat = global->time_start;
	}
	i = -1;
	while (++i < global->number_of_philos)
		pthread_create(&global->thread[i], \
			NULL, &ft_philo_start, &global->philo[i]);
	pthread_create(&check, NULL, &ft_check_death, global);
	pthread_join(check, NULL);
	i = -1;
	while (++i < global->number_of_philos)
		pthread_join(global->thread[i], NULL);
	return (0);
}

int	ft_philo_init(t_global *global)
{
	int	i;

	i = 0;
	while (i < global->number_of_philos)
	{
		global->philo[i].id_philo = i + 1;
		global->philo[i].time_to_die = global->time_to_die;
		global->philo[i].time_to_eat = global->time_to_eat;
		global->philo[i].time_to_sleep = global->time_to_sleep;
		global->philo[i].count_eat = 0;
		global->philo[i].id_left = i;
		if (i < global->number_of_philos - 1)
			global->philo[i].id_right = i + 1;
		else
			global->philo[i].id_right = 0;
		global->philo[i].last_eat = 0;
		global->philo[i].arg = global;
		i++;
	}
	i = -1;
	while (i < global->number_of_philos)
		if (pthread_mutex_init(&global->fork[++i], NULL))
			return (1);
	return (0);
}

t_global	*ft_global_init(int i, char **s)
{
	t_global	*global;

	global = malloc(sizeof(t_global));
	if (!global)
		return (NULL);
	global->number_of_philos = ft_atoi(s[0]);
	global->time_to_die = ft_atoi(s[1]);
	global->time_to_eat = ft_atoi(s[2]);
	global->time_to_sleep = ft_atoi(s[3]);
	global->count_of_lunch = 0;
	if (i == 5)
		global->count_of_lunch = ft_atoi(s[4]);
	global->death = 0;
	global->time_start = 0;
	global->thread = NULL;
	global->fork = NULL;
	pthread_mutex_init(&global->print_action, NULL);
	pthread_mutex_init(&global->c_eat, NULL);
	pthread_mutex_init(&global->mut_death, NULL);
	pthread_mutex_init(&global->mut_last, NULL);
	return (global);
}

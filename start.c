/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 19:36:07 by numussan          #+#    #+#             */
/*   Updated: 2022/11/22 22:50:26 by numussan         ###   ########.fr       */
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
		usleep(50);
	}
	while (!global->death)
	{
		if (global->count_of_lunch)
		{
			if (philo->count_eat == global->count_of_lunch)
				return (NULL);
		}
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
		pthread_create(&global->thread[i], NULL, \
			&ft_philo_start, &global->philo[i]);
	pthread_create(&check, NULL, &ft_check_death, global);
	pthread_mutex_unlock(&global->print_action);
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
	i = 0;
	while (i < global->number_of_philos)
		if (pthread_mutex_init(&global->fork[i++], NULL))
			return (1);
	return (0);
}

t_global	*ft_global_init(int ac, char **av)
{
	t_global	*arg;

	arg = malloc(sizeof(t_global));
	if (!arg)
		return (NULL);
	arg->number_of_philos = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	arg->count_of_lunch = 0;
	if (ac == 6)
		arg->count_of_lunch = ft_atoi(av[5]);
	arg->death = 0;
	arg->time_start = 0;
	arg->thread = NULL;
	arg->fork = NULL;
	arg->philo = NULL;
	pthread_mutex_init(&arg->print_action, NULL);
	return (arg);
}

int	ft_parsing(int ac, char **s)
{
	if (ac != 5 && ac != 6)
	{
		printf("<<<<< ERROR! Input 4 or 5 arguments! >>>>>");
		return (1);
	}
	if (ft_atoi(s[1]) <= 0 || ft_atoi(s[2]) <= 0 || ft_atoi(s[3]) <= 0 \
		|| ft_atoi(s[4]) <= 0 || (ac == 6 && ft_atoi(s[5]) <= 0))
	{
		printf("<<<<< ERROR! Wrong arguments! >>>>>");
		return (1);
	}
	return (0);
}

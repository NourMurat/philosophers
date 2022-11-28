/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:08:06 by numussan          #+#    #+#             */
/*   Updated: 2022/11/24 19:11:11 by numussan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_mutex_destroy(t_global *global)
{
	int	i;

	i = -1;
	while (++i < global->number_of_philos)
	{
		if (pthread_mutex_destroy(&global->fork[i]))
			printf("ERROR destroy mutex %d!\n", i);
	}
	pthread_mutex_destroy(&global->print_action);
	pthread_mutex_destroy(&global->c_eat);
	pthread_mutex_destroy(&global->mut_death);
	pthread_mutex_destroy(&global->mut_last);
}

int	ft_free_global(t_global *global)
{
	if (global->philo)
		free(global->philo);
	if (global->fork)
		free(global->fork);
	if (global->thread)
		free(global->thread);
	free(global);
	return (1);
}

int	ft_global_malloc(t_global *global)
{
	global->philo = malloc(sizeof(t_philo) * global->number_of_philos);
	if (!global->philo)
		return (1);
	global->fork = malloc(sizeof(pthread_mutex_t) * global->number_of_philos);
	if (!global->fork)
		return (1);
	global->thread = malloc(sizeof(pthread_t) * global->number_of_philos);
	if (!global->thread)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_global	*global;
	char		**separate_nbrs;
	int			i;

	i = 0;
	if (ft_check_spaces(av))
		return (1);
	separate_nbrs = ft_separate_string(ac, av);
	if (ft_parsing(separate_nbrs))
		return (1);
	while (separate_nbrs[i] != NULL)
		i++;
	global = ft_global_init(i, separate_nbrs);
	ft_free_after_split(separate_nbrs);
	if (!global)
		return (ft_free_global(global));
	if (ft_global_malloc(global))
		return (ft_free_global(global));
	if (ft_philo_init(global))
		return (ft_free_global(global));
	ft_start(global);
	ft_mutex_destroy(global);
	ft_free_global(global);
	return (0);
}

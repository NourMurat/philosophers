/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 19:37:29 by numussan          #+#    #+#             */
/*   Updated: 2022/11/28 22:11:16 by numussan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <limits.h>

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
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

long long	ft_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	ft_usleep(long long time)
{
	long long	start;

	start = ft_current_time();
	while (ft_current_time() - start < time)
		usleep(1500);
}

int	ft_atoi(char *s)
{
	int					i;
	int					sign;
	unsigned long long	num;

	i = 0;
	sign = 1;
	num = 0;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == 45)
		sign = -1;
	if (s[i] == 43 || s[i] == 45)
		i++;
	while (s[i] >= 48 && s[i] <= 57)
	{
		num = num * 10 + s[i] - 48;
		if (sign == 1 && num > 2147483647)
			return (-1);
		if (sign == -1 && num > 2147483648)
			return (0);
		i++;
	}
	if (s[i] && (s[i] < 48 || s[i] > 57))
		return (-1);
	return ((int)num * sign);
}

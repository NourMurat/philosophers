/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:08:06 by numussan          #+#    #+#             */
/*   Updated: 2022/11/10 02:47:34 by numussan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#typedef pthread_mutex_t t_mutex;

void    *ft_run(void *data)
{
	struct t_data	*_data = data;
	pthread_mutex_lock(_data->p_mutex);
	while (*(_data->num) < 100000)
	{
		(*_data->num)++;
		ptread_mutex_unlock(_data->p_mutex);
		pthread_mutex_lock(_data->p_mutex);
	}
	pthread_mutex_unlock(_data->p_mutex);
	return (0);
}

int main(void)
{
	int				tmp;
	pthread_t		id;
	t_mutex			mutex;
	struct t_data	data;

	data.p_mutex = &mutex;
	data.num = &tmp;
	pthread_mutex_init(&mutex, 0);
	pthread_create(&id, 0, ft_run, data);
	pthread_mutex_lock(&mutex);
	while (tmp <= 100000)
	{
		printf("%d\n", tmp);
		pthread_mutex_unlock(_data->p_mutex);
		pthread_mutex_lock(_data->p_mutex);
	}
	pthread_mutex_unlock(_data->p_mutex);
	return (0);
}
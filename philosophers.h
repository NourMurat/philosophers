/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:08:25 by numussan          #+#    #+#             */
/*   Updated: 2022/11/10 02:35:12 by numussan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include "libft/libft.h"
#include <pthread.h>

#typedef pthread_mutex_t t_mutex;

struct t_data
{
	t_mutex	*p_mutex;
	int		*num;
};

void    *ft_run(void *data);

#endif

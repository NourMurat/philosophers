/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: numussan <numussan@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:36:07 by numussan          #+#    #+#             */
/*   Updated: 2022/11/27 17:28:42 by numussan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_eat;
	int				id_left;
	int				id_right;
	long long		time_start;
	long long		last_eat;
	struct s_global	*arg;
}				t_philo;

typedef struct s_global
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_of_lunch;
	int				death;
	long long		time_start;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_action;
	pthread_mutex_t	c_eat;
	pthread_mutex_t	mut_death;
	pthread_mutex_t	mut_last;
	t_philo			*philo;
}				t_global;

int			ft_parsing(char **s);
t_global	*ft_global_init(int ac, char **av);
int			ft_philo_init(t_global *global);
int			ft_start(t_global *global);
void		*ft_philo_start(void *tmp);

int			ft_atoi(char *s);
int			ft_free_global(t_global *global);
int			ft_global_malloc(t_global *global);
long long	ft_current_time(void);
void		ft_usleep(long long time);

char		**ft_split(const char *s, char c);
int			ft_counting_words(const char *s, char c);
char		*ft_pull_the_word(const char *s, char c);
char		*ft_strjoin(const char *s1, const char *s2);
void		ft_free_after_split(char **s);
int			ft_strlen(const char *s);

int			ft_check_spaces(char **s);
char		**ft_separate_string(int ac, char **s);

void		ft_print(t_global *global, t_philo *philo, char *str);
int			ft_eating(t_global *global, t_philo *philo);
void		ft_sleeping(t_global *global, t_philo *philo);
void		ft_thinking(t_global *global, t_philo *philo);
void		*ft_check_death(void *tmp);
int			ft_check_time_die(t_global *global, t_philo *philo, int i);
void		ft_mutex_destroy(t_global *global);

#endif

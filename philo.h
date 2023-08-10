/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 15:54:53 by okassimi          #+#    #+#             */
/*   Updated: 2023/08/07 23:21:57 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <strings.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				number;
	long int		death_time;
	long int		meal_finished;
	long int		last_meal;
	pthread_t		tid;
	pthread_mutex_t	*lock;
	pthread_mutex_t	last_meal_lock;
	struct s_args	*arg;
}	t_philo;

typedef struct s_args
{
	int				n_philo;
	long int		time_die;
	long int		time_eat;
	long int		start_time;
	long int		time_sleep;
	pthread_mutex_t	end_lock;
	pthread_mutex_t	print_lock;
	int				end;
	int				frequency;
	t_philo			*child;
	bool			check_death;
}	t_args;

void		ft_print_error(char *error);
int			ft_check_args(int argc, const char **argv, t_args *elem);
int			ft_isdigit(int para);
int			ft_atoi(const char *nptr);

void		ft_eat_sleep_and_think(t_philo *philo);
void		*ft_routine(void *elem);
void		ft_create_threads(t_args *elem);
void		ft_thread_status(t_args *elem);
void		ft_initialize(t_args *elem, pthread_mutex_t *mutex);

long int	get_time(void);
void		ft_usleep(long int time);
void		ft_message(char *act, t_philo *philo);
void		ft_detach(t_philo *philo);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 19:25:03 by okassimi          #+#    #+#             */
/*   Updated: 2023/08/07 00:33:21 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat_sleep_and_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock[(philo->number - 1) % philo->arg->n_philo]);
	ft_message("has taken a fork", philo);
	pthread_mutex_lock(&philo->lock[philo->number % philo->arg->n_philo]);
	ft_message("has taken a fork", philo);
	ft_message("is eating", philo);
	ft_usleep(philo->arg->time_eat);
	pthread_mutex_lock(&philo->last_meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal_lock);
	if (philo->meal_finished < philo->arg->frequency)
		philo->meal_finished++;
	pthread_mutex_unlock(&philo->lock[philo->number - 1 % philo->arg->n_philo]);
	pthread_mutex_unlock(&philo->lock[philo->number % philo->arg->n_philo]);
	ft_message("is sleeping", philo);
	ft_usleep(philo->arg->time_sleep);
	ft_message("is thinking", philo);
}

void	*ft_routine(void *elem)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)elem;
	i = 0;
	while (1)
	{
		if ((philo->arg->frequency && (philo->arg->n_philo
					* philo->meal_finished < philo->arg->frequency
					* philo->arg->n_philo)) || !philo->arg->frequency)
			ft_eat_sleep_and_think(philo);
		else if ((philo->arg->frequency
				&& ((philo->arg->n_philo * philo->meal_finished)
					>= (philo->arg->frequency * philo->arg->n_philo))))
			break ;
		i++;
	}
	ft_detach(philo);
	pthread_mutex_lock(&philo->arg->end_lock);
	philo->arg->end = 1;
	pthread_mutex_unlock(&philo->arg->end_lock);
	return (NULL);
}

void	ft_create_threads(t_args *elem)
{
	int				i;
	pthread_mutex_t	*mutex;

	elem->child = malloc(elem->n_philo * sizeof(t_philo));
	mutex = malloc(elem->n_philo * sizeof(pthread_mutex_t));
	elem->end = 0;
	i = 0;
	while (i < elem->n_philo)
	{
		pthread_mutex_init(&mutex[i], NULL);
		pthread_mutex_init(&elem->child[i].last_meal_lock, NULL);
		i++;
	}
	pthread_mutex_init(&elem->print_lock, NULL);
	pthread_mutex_init(&elem->end_lock, NULL);
	ft_initialize(elem, mutex);
	i = 0;
	while (i < elem->n_philo)
	{
		pthread_create(&elem->child[i].tid, NULL, &ft_routine, &elem->child[i]);
		usleep(100);
		i++;
	}
	ft_thread_status(elem);
	return ;
}

void	ft_thread_status(t_args *elem)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < elem->n_philo)
		{
			pthread_mutex_lock(&elem->end_lock);
			if (elem->end == 0)
			{
				pthread_mutex_lock(&elem->child[i].last_meal_lock);
				if (get_time() - elem->child[i].last_meal
					> elem->child[i].death_time)
				{
					ft_message("died", &elem->child[i]);
					return ;
				}
			}
			else
				return ;
			pthread_mutex_unlock(&elem->end_lock);
			pthread_mutex_unlock(&elem->child[i].last_meal_lock);
			i++;
		}
	}
}

void	ft_initialize(t_args *elem, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	elem->start_time = get_time();
	while (i < elem->n_philo)
	{
		elem->child[i].number = i + 1;
		elem->child[i].death_time = elem->time_die;
		elem->child[i].meal_finished = 0;
		elem->child[i].lock = mutex;
		elem->child[i].last_meal = elem->start_time;
		elem->child[i].arg = elem;
		i++;
	}
}

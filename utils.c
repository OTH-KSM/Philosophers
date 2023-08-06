/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:01:26 by okassimi          #+#    #+#             */
/*   Updated: 2023/08/07 00:33:36 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long int time)
{
	long int	current_time;

	current_time = get_time();
	while (get_time() - current_time < time)
	{
		usleep(99);
	}
}

void	ft_message(char *act, t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->print_lock);
	printf("%ld %d %s\n", get_time() - philo->arg->start_time,
		philo->number, act);
	if (strcmp(act, "died"))
		pthread_mutex_unlock(&philo->arg->print_lock);
}

void	ft_detach(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->arg->n_philo)
	{
		pthread_detach(philo->arg->child[i].tid);
		i++;
	}
	return ;
}

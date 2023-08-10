/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 23:27:38 by okassimi          #+#    #+#             */
/*   Updated: 2023/08/07 23:29:05 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char const *argv[])
{
	t_args	*elem;

	elem = malloc(sizeof(t_args));
	if (argc != 5 && argc != 6)
	{
		printf("Syntax: N_philo time_die time_eat time_sleep frequency\n");
		return (1);
	}
	if ((ft_check_args(argc, argv, elem)) == 1)
		return (1);
	if (elem->n_philo <= 0 || elem->time_die < 0 || elem->time_eat < 0
		|| elem->time_sleep < 0)
	{
		ft_print_error("Arguments are negative");
		return (1);
	}
	ft_create_threads(elem);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okassimi <okassimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 23:40:17 by okassimi          #+#    #+#             */
/*   Updated: 2023/08/06 23:58:25 by okassimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_error(char *error)
{
	printf("Error\n");
	printf("%s\n", error);
}

int	ft_isdigit(int para)
{
	if (para >= 48 && para <= 57)
		return (1);
	return (0);
}

int	ft_check_int(const char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			if ((arg[i] == '+' && arg[i + 1] == ' ') || (arg[i] == '-' && arg[i
						+ 1] == ' ') || ((arg[i] != 43 && arg[i] != 45
						&& arg[i] != ' ') && ((arg[i] > 32 && arg[i] < 48)
						|| (arg[i] > 57))) || (arg[i] == '+' && arg[i
						+ 1] == '+') || (arg[i] == '-' && arg[i + 1] == '-')
				|| (arg[i] == '+' && arg[i + 1] == '\0') || (arg[i] == '-'
					&& arg[i + 1] == '\0') || (arg[i] == '-' && arg[i
						+ 1] == '+') || (arg[i] == '+' && arg[i + 1] == '-'))
				return (1);
		}
		else
			if ((arg[i + 1] >= 58 && arg[i + 1] <= 126)
				|| (arg[i + 1] >= 33 && arg[i + 1] <= 47))
				return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int					i;
	int					signe;
	long long			nb;

	i = 0;
	nb = 0;
	signe = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-')
	{
		signe *= -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] && (nptr[i] >= 48 && nptr[i] <= 57))
	{
		if (nb > 9223372036854775807 && signe == -1)
			return (0);
		if (nb > 9223372036854775807 && signe == 1)
			return (-1);
		nb = nb * 10 + nptr[i++] - '0';
	}
	return (nb * signe);
}

int	ft_check_args(int argc, const char **argv, t_args *elem)
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (ft_check_int(argv[i]) == 1)
		{
			ft_print_error("Argument are not integers");
			return (1);
		}
		i++;
	}
	elem->n_philo = ft_atoi(argv[1]);
	elem->time_die = ft_atoi(argv[2]);
	elem->time_eat = ft_atoi(argv[3]);
	elem->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		elem->frequency = ft_atoi(argv[5]);
	else
		elem->frequency = 0;
	return (0);
}

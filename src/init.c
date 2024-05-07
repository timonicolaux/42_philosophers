/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:17:32 by tnicolau          #+#    #+#             */
/*   Updated: 2024/05/07 08:37:11 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philos	*init_struct(t_philos *philos, t_args *args, char **av,
		t_global *global)
{
	if (!init_args(args, av))
		return (NULL);
	global->args = args;
	philos = init_philos(args, philos, global);
	if (!philos)
		return (NULL);
	return (philos);
}

void	*init_args(t_args *args, char **av)
{
	args->philosophers = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		args->num_of_meals = ft_atoi(av[5]);
	else
		args->num_of_meals = -1;
	return (args);
}

void	link_last_lst(t_philos *philos)
{
	t_philos	*philos_cpy;

	philos_cpy = philos;
	while (philos->next)
		philos = philos->next;
	philos_cpy->prev = philos;
	philos = philos_cpy;
}

void	print_one_philo(t_philos *philos, t_args *args, char *message)
{
	print_msg(philos, "has taken a fork");
	printf("%zu %d %s\n", args->time_to_die, philos->id, message);
	free(philos);
	philos = NULL;
}

t_philos	*init_philos(t_args *args, t_philos *philos, t_global *global)
{
	int	i;

	i = 2;
	philos = new_philo(1, global);
	if (!philos)
		return (NULL);
	if (args->philosophers && args->num_of_meals == 0)
	{
		printf("No meals\n");
		return (free(philos), NULL);
	}
	if (args->philosophers && args->philosophers == 1)
	{
		philos->global->start_time = get_current_time();
		print_one_philo(philos, args, "died");
		return (NULL);
	}
	while (i < (args->philosophers + 1) && args->philosophers > 1)
	{
		if (!add_philo_to_lst(philos, i, global))
			return (NULL);
		i++;
	}
	link_last_lst(philos);
	return (philos);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:17:22 by tnicolau          #+#    #+#             */
/*   Updated: 2024/05/07 10:20:15 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_valid_args(char **av)
{
	if (ft_atoi(av[1]) <= 0)
		return (printf("Invalid number of philosophers\n"), -1);
	if (ft_atoi(av[2]) <= 0)
		return (printf("Invalid time to die\n"), -1);
	if (ft_atoi(av[3]) <= 0)
		return (printf("Invalid time to eat\n"), -1);
	if (ft_atoi(av[4]) <= 0)
		return (printf("Invalid time to sleep\n"), -1);
	if (av[5] && ft_atoi(av[5]) < 0)
		return (printf("Invalid number of meals\n"), -1);
	else
		return (0);
}

int	init_mutexes(t_philos *philos, t_global *global)
{
	if (pthread_mutex_init(&global->mutex, NULL) != 0)
	{
		printf("Error during mutex initialisation\n");
		destroy_all_threads(philos, global);
		return (-1);
	}
	if (pthread_mutex_init(&global->print, NULL) != 0)
	{
		printf("Error during mutex initialisation\n");
		destroy_all_threads(philos, global);
		return (-1);
	}
	if (pthread_mutex_init(&global->num_meals_mutex, NULL) != 0)
	{
		printf("Error during mutex initialisation\n");
		destroy_all_threads(philos, global);
		return (-1);
	}
	return (0);
}

int	init_prog(t_args *args, t_philos *philos, t_global *global, char **av)
{
	if (init_mutexes(philos, global) == -1)
		return (-1);
	if (check_valid_args(av) == -1)
	{
		destroy_all_threads(philos, global);
		return (-1);
	}
	philos = init_struct(philos, args, av, global);
	if (!philos)
	{
		destroy_all_threads(philos, global);
		clear_lst(philos);
		return (-1);
	}
	launch_threads(philos, global);
	destroy_all_threads(philos, global);
	clear_lst(philos);
	return (0);
}

int	main(int ac, char **av)
{
	t_args		args;
	t_philos	*philos;
	t_global	global;

	memset(&args, 0, sizeof(t_args));
	memset(&global, 0, sizeof(t_global));
	global.stop = false;
	global.ready = false;
	philos = NULL;
	if (ac < 5)
		return (printf("Not enough arguments\n"), -1);
	else if (ac > 6)
		return (printf("Too many arguments\n"), -1);
	else
		init_prog(&args, philos, &global, av);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:17:39 by tnicolau          #+#    #+#             */
/*   Updated: 2024/05/07 10:16:09 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*add_philo_to_lst(t_philos *philos, int id, t_global *global)
{
	t_philos	*new_lst;

	new_lst = new_philo(id, global);
	if (!new_lst)
	{
		printf("Error while allocating memory\n");
		return (NULL);
	}
	lstadd_back(philos, new_lst);
	return (philos);
}

t_philos	*new_philo(int id, t_global *global)
{
	t_philos	*new;

	new = malloc(sizeof(t_philos));
	if (!new)
		return (NULL);
	new->id = id;
	new->meals = 0;
	new->last_meal = 0;
	if (pthread_mutex_init(&new->fork_mutex, NULL) != 0)
	{
		printf("Error during mutex initialisation\n");
		free(new);
		return (NULL);
	}
	new->fork = true;
	new->has_fork = false;
	new->has_prev_fork = false;
	new->global = global;
	new->args = global->args;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	lstadd_back(t_philos *philos, t_philos *new)
{
	t_philos	*temp;

	temp = NULL;
	if (!philos)
	{
		philos = new;
		philos->prev = NULL;
		philos->next = NULL;
	}
	else
	{
		temp = philos;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
}

void	clear_lst(t_philos *lst)
{
	t_philos	*to_free;

	to_free = NULL;
	if (!lst)
		return ;
	while (lst)
	{
		to_free = lst;
		lst = lst->next;
		free(to_free);
	}
	lst = NULL;
}

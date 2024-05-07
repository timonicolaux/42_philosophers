/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnicolau <tnicolau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:17:51 by tnicolau          #+#    #+#             */
/*   Updated: 2024/05/07 10:20:46 by tnicolau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_args
{
	int		philosophers;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		num_of_meals;
}	t_args;

typedef struct s_global
{
	bool			ready;
	bool			stop;

	int				num_meals;

	size_t			start_time;

	pthread_mutex_t	mutex;
	pthread_mutex_t	print;
	pthread_mutex_t	num_meals_mutex;

	t_args			*args;

}	t_global;

typedef struct s_philos
{
	int				id;
	int				meals;

	size_t			last_meal;

	pthread_t		thread;

	pthread_mutex_t	fork_mutex;

	bool			fork;

	bool			has_fork;
	bool			has_prev_fork;

	t_global		*global;
	t_args			*args;

	struct s_philos	*next;
	struct s_philos	*prev;
}	t_philos;

/* INIT */

t_philos	*init_struct(t_philos *philos, t_args *args,
				char **av, t_global *global);
void		*init_args(t_args *args, char **av);
void		link_last_lst(t_philos *philos);
void		print_one_philo(t_philos *philos, t_args *args, char *message);
t_philos	*init_philos(t_args *args, t_philos *philos, t_global *global);

/* INIT UTILS */

void		*add_philo_to_lst(t_philos *philos, int id, t_global *global);
t_philos	*new_philo(int id, t_global *global);
void		lstadd_back(t_philos *philos, t_philos	*new);
void		clear_lst(t_philos *lst);

/* LAUNCH THREADS */

int			launch_threads(t_philos *philos, t_global *global);
void		*create_threads(t_philos *philos);
void		*join_threads(t_philos *philos);

/* DINNER */

void		*dine(void *pointer);
void		think(t_philos *philos);
int			sleeping(t_philos *philos);
int			eat(t_philos *philos);
int			grab_forks(t_philos *philos);

/* DINNER UTILS */

int			check_fork_availability(t_philos *philos);
int			check_prev_fork_availability(t_philos *philos);
int			release_forks(t_philos *philos);

/* CHECKERS */

int			check_num_meals(t_philos *philos);
int			check_if_dead(t_philos *philos, size_t param, size_t last_meal,
				size_t time);
int			check_if_ready(t_philos *philos);
int			check_if_stop(t_philos *philos);

/* UTILS */

void		print_msg(t_philos *philos, char *message);
size_t		get_current_time(void);
int			ft_usleep(size_t milliseconds);
void		mutex_checker(pthread_mutex_t *mutex, char *param);
void		destroy_all_threads(t_philos *philos, t_global *global);

/* MAIN */

int			check_valid_args(char **av);
int			init_prog(t_args *args, t_philos *philos, t_global *global,
				char **av);
int			init_mutexes(t_philos *philos, t_global *global);
int			ft_atoi(char *nptr);

#endif

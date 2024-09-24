/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:05:22 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/09/18 17:15:49 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	table_init(char **argv, t_table *table)
{
	table->count = ft_atoi(argv[1]);
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->n_meals = ft_atoi(argv[5]);
	else
		table->n_meals = -1;
	table->start = get_now();
	table->death = 0;
	table->ph_full = 0;
	if (table->t_die < 0 || table->t_sleep < 0 || table->t_eat < 0
		|| table->count <= 0 || (argv[5] && (table->n_meals <= 0)))
	{
		ft_error ("Arguments aren't valid\n");
		return (1);
	}
	mutex_init(table);
	return (0);
}

void	mutex_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->count)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->print, NULL);
}

int	thread_init(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < table->count)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) < 0)
		{
			ft_error("fail creating threads\n");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < table->count)
	{
		if (pthread_join(philo[i].thread, NULL) < 0)
		{
			ft_error("fail creating threads\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	philo_init(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->count)
	{
		philos[i].table = table;
		philos[i].nb = i;
		philos[i].last_food = table->start;
		philos[i].times_eat = 0;
		if (i == table->count -1)
		{
			philos[i].own_fork = &table->forks[(i + 1) % (table->count)];
			philos[i].r_fork = &table->forks[i];
		}
		else
		{
			philos[i].own_fork = &table->forks[i];
			philos[i].r_fork = &table->forks[(i + 1) % (table->count)];
		}
		i++;
	}
}

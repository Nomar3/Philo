/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:53:14 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/09/13 20:22:56 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int ft_waiting(t_philo * philo, int time)
{
	int	start;

	start = get_now();
	while ((get_now() - start) < time)
	{
		if (check_death(philo))
			return (1);
		usleep(100);
	}
	return (0);
}

int	ph_eat(t_philo *philo)
{
	if (check_death(philo))
		return (1);
	ft_wdoing(philo, EAT);
	ft_waiting(philo, philo->table->t_eat);
	philo->last_food = get_now;
	if (philo->table->n_meals >= 0)
		philo->times_eat + 1;
	pthread_mutex_unlock(philo->own_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

void	*routine(void *param) //¿necesitara el philo especifico?
{
	t_philo *philo;

	philo = (t_philo *)param;

	ft_wdoing(philo, EAT);
	while(1)
	{
		check_death(philo);
		ft_wdoing(philo, FORK);
		pthread_mutex_lock(philo->own_fork);
		pthread_mutex_lock(philo->r_fork);
		if (ph_eat(philo))
			return (1);
		check_death(philo);
		ft_wdoing(philo, SLEEP);
		ft_waiting(philo, philo->table->t_sleep);
		ft_wdoing(philo, THINK);

	}
	
	//if (ft_comen(t_eat)) tiene q chekear  los tenedore,si no  puede comer pasa  a  pensar;
		//usleep(50); ta pensando
	
	//usleep(table->t_sleep);//duerme, necesita algo  mas?
	//ft_printeacion(table->text);
	return(NULL);
}

 t_table	*table_init(char **argv)
{
	t_table *table;

	table = malloc(sizeof(t_table));
	if (!table)
		ft_error("fail malloc of the table struct\n");


	table->count = ft_atoi(argv[1]);

	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	table->start = get_now();
	table->death = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->count);
	if (!table->forks)
		ft_error("fail during malloc of the forks\n");
	if (table->t_die < 0 || table->t_sleep < 0 || table->t_eat < 0 || table->count < 2)
		ft_error ("Arguments aren't valid\n");

	if (argv[5])
	{
		if ((table->n_meals = ft_atoi(argv[5])) < 0)
			ft_error("Arguments can`t be negative\n");
	}
	else
		table->n_meals = -1;

	mutex_init(table);
	return (table);
}

void	mutex_init(t_table *table)
{
	int	i;

	i = table->count;
	while (i > 0)
	{

		pthread_mutex_init(&table->forks[i], NULL);
		i--;
	}

	pthread_mutex_init(&table->print, NULL);
	
}

void	thread_init(t_table * table, t_philo * philo)
{
	int i;

	i = 0;

	i = 0;
	while (i < table->count)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) < 0)
			ft_error("fail creating threads\n");
		i++;
	}

	i = 0;
	while (i < table->count)
	{
		if (pthread_join(philo[i].thread, NULL) < 0)
			ft_error("fail joining the threads\n");
		i++;
	}
}

t_philo	*philo_init(t_table *table)
{
	int	i;
	t_philo *philos;
	
	i = 0;
	philos = malloc(sizeof(t_philo) * table->count);
	if (!philos)
		ft_error("fail during philo malloc\n");

	while (i < table->count)
	{

		philos[i].nb = i;

		philos[i].times_eat = table->n_meals;
		philos[i].own_fork = table->forks[i];
		philos[i].r_fork = table->forks[(i + 1) % (table->count)];
		philos[i].table = table;

		i++;
	}
	return (philos);
}

int	main(int argc, char **argv)
{
	t_table *table;
	t_philo *philo;
	//table = NULL;
	//philo = NULL;
	(void) argc;
	//if(argc == 5 || argc == 6)
		//if (!check_argvs(argv));
			//mensaje error;

		table = table_init(argv);
		printf("count: %i\n", table->count);

		philo = philo_init(table);

		thread_init(table, philo);
/* 	else
		ft_error("argument count is not correct\n"); */
	return (0);
}
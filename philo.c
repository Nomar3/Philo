/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:53:14 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/09/18 17:16:48 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_eat(t_philo *philo)
{
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->own_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	if (ft_wdoing(philo, EAT))
		return (1);
	if (ft_waiting(philo, philo->table->t_eat))
	{
		pthread_mutex_unlock(philo->own_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	philo->last_food = get_now();
	if (check_full(philo))
		return (1);
	pthread_mutex_unlock(philo->own_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int	ph_life(t_philo *philo)
{
	pthread_mutex_lock(philo->own_fork);
	if (ft_wdoing(philo, FORK))
	{
		pthread_mutex_unlock(philo->own_fork);
		return (1);
	}
	pthread_mutex_lock(philo->r_fork);
	if (ft_wdoing(philo, FORK))
	{
		pthread_mutex_unlock(philo->own_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	if (ph_eat(philo))
		return (1);
	if (ft_wdoing(philo, SLEEP))
		return (1);
	if (ft_waiting(philo, philo->table->t_sleep))
		return (1);
	if (ft_wdoing(philo, THINK))
		return (1);
	return (0);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (philo->table->count == 1)
	{
		ft_wdoing(philo, FORK);
		ft_waiting(philo, philo->table->t_die);
		ft_wdoing(philo, DEAD);
		return (NULL);
	}
	if (philo->nb % 2 == 0)
	{
		if (ft_waiting(philo, philo->table->t_eat))
			return (NULL);
	}
	while (1)
	{
		if (check_death(philo))
			break ;
		if (ph_life(philo))
			break ;
		if (philo->table->count % 2 == 1)
			ft_waiting(philo, philo->table->t_eat);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_philo	philo[200];

	if (argc == 5 || argc == 6)
	{
		if (check_argvs(argv))
		{
			ft_error("arguments must be only digits\n");
			return (0);
		}
		if (table_init(argv, &table))
			return (0);
		philo_init(&table, philo);
		if (thread_init(&table, philo))
			return (0);
	}
	else
		ft_error("argument count is not correct\n");
	return (0);
}

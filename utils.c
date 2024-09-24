/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:13:50 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/09/23 16:57:03 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *text)
{
	int	i;

	i = 0;
	while (text[i])
		i++;
	write(2, text, i);
}

int	check_argvs(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] == '\0')
			return (1);
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	long	nb;
	int		i;

	nb = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			ft_error("ft_atoi fail\n");
		else
			nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb < INT_MIN || nb > INT_MAX)
		ft_error("number too long\n");
	return ((int) nb);
}

int	ft_wdoing(t_philo *philo, char *doing)
{
	long	time;

	if (check_death(philo))
		return (1);
	time = time_diff(philo->table->start, get_now());
	pthread_mutex_lock(&philo->table->print);
	if (philo->table->death == 0)
		printf("[%li] Philo %i %s", time, (philo->nb + 1), doing);
	pthread_mutex_unlock(&philo->table->print);
	return (0);
}

int	check_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	if (philo->table->n_meals >= 0)
	{
		philo->times_eat += 1;
		if (philo->times_eat == philo->table->n_meals)
			philo->table->ph_full += 1;
	}
	if (philo->table->ph_full == philo->table->count)
	{
		philo->table->death = 1;
		pthread_mutex_unlock(philo->own_fork);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(&philo->table->print);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->print);
	return (0);
}

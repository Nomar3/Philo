/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:53:24 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/09/16 17:19:04 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_now(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	//printf("segundos: %ld\n", tv.tv_sec);
	//printf("microsegundos: %ld\n", tv.tv_usec);
	return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

 long	time_diff(long past, long now)
 {
 	return(now - past);
 }

  int	check_death(t_philo *philo)
 {
	long	time;

	time = time_diff(philo->table->start, get_now());
 	pthread_mutex_lock(&philo->table->print);
 	if(philo->table->death == 1)
 	{
 		pthread_mutex_unlock(&philo->table->print);
 		return(1);
 	}
 	pthread_mutex_unlock(&philo->table->print);
 	if ((get_now() - philo->last_food) >= philo->table->t_die)//revisar
 	{
 		pthread_mutex_lock(&philo->table->print);
 		philo->table->death = 1;
		printf("[%li] Philo %i %s", time, philo->nb,  DEAD);
 		pthread_mutex_unlock(&philo->table->print);
 	}
 	return(0);
 }
 

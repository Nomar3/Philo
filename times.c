/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 17:53:24 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/09/06 12:25:15 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_now(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	printf("segundos: %ld\n", tv.tv_sec);
	printf("microsegundos: %ld\n", tv.tv_usec);
	return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	time_diff(long past, long now)
{
	return(now - past);
}

/* int	check_death(t_table *table)
{
	if(table->death == 1)
		return(1);
	else
		return(0);
} */

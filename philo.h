/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:33:49 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/09/06 13:05:03 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>


typedef struct s_table
{
	int	t_eat;
	int	t_sleep;
	int	t_die;
	int	count;
	int death;
	long	start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;

}	t_table;

typedef struct s_philo
{
	int	nb;
	int	last_food;
	int	times_eat;
	pthread_mutex_t	own_fork;
	pthread_mutex_t	r_fork;
	pthread_t	thread;
	t_table *table;

}	t_philo;


/*----------philo----------*/
long	get_now(void);

/*----------utils----------*/
int		ft_atoi(const char *str);
void	ft_error(char *text);

#endif
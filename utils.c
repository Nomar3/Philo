/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:13:50 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/09/06 13:04:52 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void	ft_error(char *text)
{
	perror(text);
	exit(EXIT_FAILURE);
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
		if (str[i] < '0' || str[i] > '9')
			ft_error("ft_atoi fail\n");
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (nb > INT_MAX)
		ft_error("number too long\n");
	return ((int) nb);
}
void	ft_wdoing(t_philo *philo, char *doing)
{
	long	time;

	time = time_diff(philo->table->start, get_now());
	printf("[%i] Philo %i %s\n", time, philo->nb,  doing);
}

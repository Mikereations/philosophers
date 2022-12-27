/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aba-nabi <aba-nabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:38:37 by aba-nabi          #+#    #+#             */
/*   Updated: 2022/12/26 15:19:57 by aba-nabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_simulation(t_program *prog)
{
	int	i;

	i = 0;
	while (i < prog->philos)
	{
		pthread_join(prog->philosophers[i].philo, NULL);
		i++;
	}
	i = 0;
	while (i < prog->philos)
	{
		pthread_mutex_destroy(&(prog->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(prog->writing));
	pthread_mutex_destroy(&(prog->eating));
	if (prog->forks)
		free(prog->forks);
	if (prog->philosophers)
		free(prog->philosophers);
}

void	ft_error(void)
{
	printf("Error, Invalid input\n");
	exit(1);
}
// exit found here ... forbidden function
// philo not working at all!!

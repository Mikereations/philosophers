/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aba-nabi <aba-nabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:15:01 by aba-nabi          #+#    #+#             */
/*   Updated: 2022/07/12 23:15:48 by aba-nabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philosopher *p)
{
	long long	start;

	start = get_time();
	while (!p->prog->died)
	{
		if ((int)(get_time() - start) >= p->prog->eat_time)
			break ;
		usleep(50);
	}
	return ;
}

void	rest(t_philosopher *p)
{
	long long	start;

	start = get_time();
	while (!p->prog->died)
	{
		if ((int)(get_time() - start) >= p->prog->sleep_time)
			break ;
		usleep(50);
	}
	return ;
}

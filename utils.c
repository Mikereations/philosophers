/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aba-nabi <aba-nabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:18:44 by aba-nabi          #+#    #+#             */
/*   Updated: 2022/12/26 17:51:14 by aba-nabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	printer(t_philosopher *p, char *str)
{
	long long	current_time;

	pthread_mutex_lock(&p->prog->writing);
	if (!p->prog->died)
	{
		current_time = get_time() - p->prog->start_time;
		printf("%llu %d %s", current_time, p->id + 1, str);
		if (str[0] == 'd')
			p->prog->died = 1;
	}
	pthread_mutex_unlock(&p->prog->writing);
}

int	check_fed(t_program *prog)
{
	int	i;

	i = 0;
	if (prog->meal_goal == -1)
		return (0);
	while (i < prog->philos)
	{
		pthread_mutex_lock(&prog->eating);
		if (prog->philosophers[i].meal_count < prog->meal_goal)
		{
			pthread_mutex_unlock(&prog->eating);
			return (0);
		}
		pthread_mutex_unlock(&prog->eating);
		i++;
	}
	pthread_mutex_lock(&prog->eating);
	prog->fed = 1;
	pthread_mutex_unlock(&prog->eating);
	return (1);
}

static void	unlocking(t_program *prog)
{
	int				i;
	int				pid;
	t_philosopher	*p;

	i = 0;
	while (i < prog->philos)
	{
		p = &prog->philosophers[i];
		pid = p->id;
		pthread_mutex_unlock(&p->prog->forks[pid]);
		pid = (pid + 1) % p->prog->philos;
		pthread_mutex_unlock(&p->prog->forks[pid]);
		i++;
	}
}

void	check_dead(t_program *prog)
{
	int			i;
	long long	since_last;

	while (!check_fed(prog))
	{
		i = 0;
		while (i < prog->philos && !(prog->died))
		{
			pthread_mutex_lock(&prog->eating);
			since_last = (get_time() - prog->philosophers[i].last_meal);
			if (since_last >= prog->death_time)
			{
				printer(&prog->philosophers[i], "died\n");
				prog->died = 1;
			}
			pthread_mutex_unlock(&prog->eating);
			usleep(100);
			i++;
		}
		if (prog->died)
			break ;
	}
	unlocking(prog);
}

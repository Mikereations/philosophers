/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aba-nabi <aba-nabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:08:40 by aba-nabi          #+#    #+#             */
/*   Updated: 2022/12/26 19:41:59 by aba-nabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_pid(t_philosopher	*p, int against)
{
	int	pid;

	pid = p->id;
	if (pid % 2 == against)
		pid = (pid + 1) % p->prog->philos;
	return (pid);
}

void	*philosophy(t_philosopher	*p)
{
	int	pid;

	pid = get_pid(p, 0);
	if (p->prog->lasts[pid] == p->id)
		return (NULL);
	pid = get_pid(p, 1);
	if (p->prog->lasts[pid] == p->id)
		return (NULL);
	p->prog->lasts[pid] = p->id;
	pthread_mutex_lock(&p->prog->forks[pid]);
	printer(p, "has taken a fork\n");
	pid = get_pid(p, 0);
	p->prog->lasts[pid] = p->id;
	pthread_mutex_lock(&p->prog->forks[pid]);
	printer(p, "has taken a fork\n");
	pthread_mutex_lock(&p->prog->eating);
	p->last_meal = get_time();
	printer(p, "is eating\n");
	p->meal_count += 1;
	pthread_mutex_unlock(&p->prog->eating);
	eat(p);
	pthread_mutex_unlock(&p->prog->forks[pid]);
	pid = get_pid(p, 1);
	pthread_mutex_unlock(&p->prog->forks[pid]);
	return (NULL);
}

void	printstuff(t_philosopher	*p)
{
	printer(p, "is sleeping\n");
	rest(p);
	printer(p, "is thinking\n");
}

void	*d_c(void *philosopher)
{
	t_philosopher	*p;

	p = (t_philosopher *)philosopher;
	if (p->id % 2)
		usleep(p->prog->sleep_time * 500);
	while (1)
	{
		pthread_mutex_lock(&p->prog->eating);
		if (p->prog->died)
		{
			pthread_mutex_unlock(&p->prog->eating);
			break ;
		}
		pthread_mutex_unlock(&p->prog->eating);
		philosophy(p);
		pthread_mutex_lock(&p->prog->eating);
		if (p->prog->fed)
		{
			pthread_mutex_unlock(&p->prog->eating);
			break ;
		}
		pthread_mutex_unlock(&p->prog->eating);
		printstuff(p);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_program	prog;
	int			i;

	if (argc != 5 && argc != 6)
	{
		printf("Invalid number of arguments %d\n", argc);
		return (1);
	}
	if (program(&prog, argv))
	{
		printf("Error initialising variables for the program\n");
		return (1);
	}
	prog.start_time = get_time();
	i = 0;
	while (i < prog.philos)
	{
		prog.philosophers[i].last_meal = get_time();
		if (pthread_create(&prog.philosophers[i].philo, NULL, &d_c,
				&prog.philosophers[i]))
			return (1);
		i++;
	}
	check_dead(&prog);
	end_simulation(&prog);
}

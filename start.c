/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aba-nabi <aba-nabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:15:53 by aba-nabi          #+#    #+#             */
/*   Updated: 2022/12/26 18:29:11 by aba-nabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex(t_program *prog)
{
	int	i;

	i = 0;
	prog->died = 0;
	prog->forks = NULL;
	prog->start_time = get_time();
	prog->forks = (pthread_mutex_t *)
		malloc(sizeof(*(prog->forks)) * prog->philos);
	if (!(prog->forks))
		return (1);
	prog->lasts = (int *)malloc(sizeof(*(prog->forks)) * prog->philos);
	if (!(prog->lasts))
		return (1);
	while (i < prog->philos)
	{
		if (pthread_mutex_init(&(prog->forks[i]), NULL))
			return (1);
		i++;
		prog->lasts[i] = -1;
	}
	if (pthread_mutex_init(&(prog->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(prog->eating), NULL))
		return (1);
	return (0);
}

int	ft_atoi(char const *str)
{
	int		n;
	size_t	sum;

	sum = 0;
	n = 1;
	while ((*str == ' ' || (*str >= 9 && *str <= 13)) && *str)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			n = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if ((long long)(sum * n) > INT_MAX || (long long)(sum * n) < INT_MIN)
			ft_error();
		sum = sum * 10 + *str++ - '0';
	}
	if (sum * n <= 0)
		ft_error();
	return (sum * n);
}

int	philospher(t_program *prog)
{
	int	i;

	i = 0;
	prog->fed = 0;
	prog->philosophers = NULL;
	prog->philosophers = (t_philosopher *)
		malloc(sizeof(*(prog->philosophers)) * prog->philos);
	if (!prog->philosophers)
		return (1);
	while (i < prog->philos)
	{
		prog->philosophers[i].id = i;
		prog->philosophers[i].ate = 0;
		prog->philosophers[i].meal_count = 0;
		prog->philosophers[i].last_meal = 0;
		prog->philosophers[i].prog = prog;
		i++;
	}
	return (0);
}

int	is_numeric(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	count_args(char **argv)
{
	int		i;
	int		j;
	char	c;

	i = 1;
	while (argv[i])
	{
		j = 0;
		c = argv[i][j];
		while (c)
		{
			if (!is_numeric(c) && !(c == '-' && j == 0))
				ft_error();
			if (c == '-' && j == 0 && argv[i][j + 1] == 0)
				ft_error();
			j++;
			c = argv[i][j];
		}
		i++;
	}
	return (i - 1);
}

int	program(t_program *prog, char **argv)
{
	count_args(argv);
	prog->philos = ft_atoi(argv[1]);
	prog->death_time = ft_atoi(argv[2]);
	prog->eat_time = ft_atoi(argv[3]);
	prog->sleep_time = ft_atoi(argv[4]);
	prog->meal_goal = -1;
	if (prog->philos < 1 || prog->death_time < 0 || prog->eat_time < 0
		|| prog->sleep_time < 0 || prog->philos > 250)
		return (1);
	if (argv[5])
	{
		prog->meal_goal = ft_atoi(argv[5]);
		if (!ft_atoi(argv[5]))
			return (1);
	}
	if (mutex(prog))
		return (2);
	if (philospher(prog))
	{
		if (prog->forks == NULL)
			free(prog->forks);
		return (3);
	}
	return (0);
}

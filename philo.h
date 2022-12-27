/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aba-nabi <aba-nabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:12:56 by aba-nabi          #+#    #+#             */
/*   Updated: 2022/12/26 18:22:30 by aba-nabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>

struct	s_program;

typedef struct s_philospher {
	int					id;
	int					ate;
	int					meal_count;
	long long			last_meal;
	pthread_t			philo;
	struct s_program	*prog;
}	t_philosopher;

typedef struct s_program {
	int				philos;
	int				eat_time;
	int				death_time;
	int				sleep_time;
	int				meal_goal;
	long long		start_time;
	int				died;
	int				fed;
	pthread_mutex_t	*forks;
	int				*lasts;
	pthread_mutex_t	writing;
	pthread_mutex_t	eating;
	t_philosopher	*philosophers;
}	t_program;

int			ft_atoi(const char *str);
int			program(t_program *prog, char **argv);
long long	get_time(void);
void		printer(t_philosopher *p, char *str);
void		check_dead(t_program *prog);
void		eat(t_philosopher *p);
void		rest(t_philosopher *p);
void		end_simulation(t_program *prog);
void		ft_error(void);

#endif

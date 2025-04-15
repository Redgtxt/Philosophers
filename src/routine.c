#include "philo.h"

static int print_philo(t_worker worker,char *msg)
{
	printf("%lu Philosofer:%d %s\n",get_time(), worker.id,msg);
	return 0;
}

static void ft_usleep(long int time)
{
	usleep(time * 1000);
}

static int eat(t_worker worker)
{
	print_philo(worker,EAT_MSG);
	ft_usleep(worker.time_to_eat);
	return 0;
}

static int my_sleep(t_worker worker)
{
	print_philo(worker,SLEEP_MSG);
	ft_usleep(worker.time_to_sleep);
	return 0;
}

static int think(t_worker worker)
{
	print_philo(worker,THINK_MSG);
	return 0;
}

void* routine(void *rec)
{
	t_worker worker;
	worker = *(t_worker *)rec;
	while (1)
	{
		eat(worker);
		my_sleep(worker);
		think(worker);
	}

	return NULL;
}
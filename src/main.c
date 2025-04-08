#include "philo.h"


long int my_gettimeofday(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return(tv.tv_sec * MILISECONDS + tv.tv_usec / MILISECONDS);
}

unsigned long int get_time(void)
{
	static unsigned long int start_time;

	if(!start_time)
	{
		start_time = my_gettimeofday();
		return(0);
	}
	else
	{
		return(my_gettimeofday() - start_time );
	}
}
int print_philo(t_worker worker,char *msg)
{
	printf("%lu Philosofer:%d %s\n",get_time(), worker.id,msg);
	return 0;
}

void ft_usleep(long int time)
{
	usleep(time * 1000);
}
int eat(t_worker worker)
{
	print_philo(worker,EAT_MSG);
	ft_usleep(worker.time_to_eat);
	return 0;
}

int my_sleep(t_worker worker)
{
	print_philo(worker,SLEEP_MSG);
	ft_usleep(worker.time_to_sleep);
	return 0;
}

int think(t_worker worker)
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


int storing_philos(t_philo *philo)
{

    int p_num;

    p_num = 0;
    while(philo->num_of_philos > p_num)
    {
    	if(pthread_create(&philo->philo_storage[p_num],NULL,&routine, &(philo->workers[p_num])) != 0)
		{
			//TENHO DE DAR FREE E MATAR OS PHILOS
			return -1;
		}
		p_num++;
	}

    return 0;
}


int main(int  argc,char *argv[])
{
	t_philo philo;

	if(inicialize_program(argc,argv,&philo) == -1)
		return -1;

	int i;

	i = 0;
	while (philo.num_of_philos > i)
	{
		pthread_join(philo.philo_storage[i],NULL);
		i++;
	}

	return 0;
}


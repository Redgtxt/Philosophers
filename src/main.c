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

void ft_usleep(long int time)
{
	usleep(time * 1000);
}
int eat(t_worker philo)
{

	return 0;
}

int my_sleep(t_worker philo)
{

}

int think(t_worker philo)
{

}
static void* routine()
{                                                                                                    
	printf("Test for phtread\n");
	sleep(1);
	printf("Exiting for phtread\n");
	return NULL;
}


int storing_philos(t_philo *philo)
{

    int p_num;

    p_num = 0;
    while(philo->num_of_philos > p_num)
    {
    	if(pthread_create(&philo->philo_storage[p_num],NULL,&routine,NULL) != 0)
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


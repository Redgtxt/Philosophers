#include "philo.h"

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


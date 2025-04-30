#include "philo.h"


pthread_mutex_t *create_mutex(int num)
{
	int i;
	pthread_mutex_t *mutex_arr;

	mutex_arr = malloc(sizeof(pthread_mutex_t) * num);
	if(!mutex_arr)
		return NULL;
	i = 0;
	while(num > i)
	{
		pthread_mutex_init(&mutex_arr[i],NULL);
		i++;
	}

	return mutex_arr;
}


void cleanup_mutex(pthread_mutex_t *arr,int size)
{
	if(!arr)
		return;

	int i;

	i = 0;
	while (size > i)
	{
		pthread_mutex_destroy(&arr[i]);
		i++;
	}
	free(arr);
}

/*
	[] criar 

*/


int main(int  argc,char *argv[])
{
	t_philo philo;
	bool a = true;
	bool b = false;
	printf(" %B :: %B\n\n\n\n", a, b);
	if(inicialize_program(argc,argv,&philo) == -1)
		return -1;

	int i;

	i = 0;
	printf("FINISHED\n");
	while (philo.num_of_philos > i)
	{
		pthread_join(philo.philo_storage[i],NULL);
		i++;
	}
	cleanup_mutex(philo.mutex_arr,philo.num_of_philos);
	free(philo.philo_storage);
	free(philo.workers);
	return 0;
}


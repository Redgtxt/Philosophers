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

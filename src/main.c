#include "philo.h"

// static init_values()
// {

// }
// //4 argumentos obrigatorios
// //grab values
// static grab_values(int argc)
// {

// }
static void debug_values_philo(	t_philo philo)
{
	printf("DEBUG MODE\n");
	printf("Number of Philos: %d\n",philo.num_of_philos);
	printf("time_to_die: %d\n",philo.time_to_die);
	printf("time_to_eat: %d\n",philo.time_to_eat);
	printf("time_to_sleep: %d\n",philo.time_to_sleep);
	if(philo.num_of_times_each_philo_eat != -1)
		printf("num_of_times_each_philo_eat: %d\n",philo.num_of_times_each_philo_eat);
	
}

int main(int argc,char *argv[])
{
	(void)argv;
	if(argc < 5 || argc >= 7)
	{
		return -1;
	}
	t_philo philo;
	memset(&philo,0,sizeof(t_philo));//Meto todos os valores a 0
	if(argc == 6)
	{
		//talvez possa apanhar os valores aqui com o atoi
		printf("Opa tenho um parametro opcional\n");
	}else
	{
		philo.num_of_times_each_philo_eat = -1;
	}
	debug_values_philo(philo);
	return 0;
}


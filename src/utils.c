
#include "philo.h"
void debug_values_philo(	t_philo philo)
{
    printf("DEBUG MODE\n");
    printf("Number of Philos: %d\n",philo.num_of_philos);
    printf("time_to_die: %d\n",philo.time_to_die);
    printf("time_to_eat: %d\n",philo.time_to_eat);
    printf("time_to_sleep: %d\n",philo.time_to_sleep);
    if(philo.num_of_times_each_philo_eat != -1)
        printf("num_of_times_each_philo_eat: %d\n",philo.num_of_times_each_philo_eat);
}

static int is_digit(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

static int	ft_atoi(const char *str)
{
    int	i;
    int	neg;
    long	num;

    i = 0;
    neg = 1;
    num = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            neg = -1;
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9')
    {
        num = (str[i] - '0') + (num * 10);
        i++;
    }
    num = num * neg;
    if (num > INT_MAX || num < INT_MIN)
        return -1;

    return (int)num;
}

int do_parsing(char *argv[])
{
    int i;
    int j;
    i = 1;
    while(argv[i])
    {
        j = 0;
        while(argv[i][j])
        {
            if(!is_digit(argv[i][j]))
            {
                printf("Error: Argument %d is not a number\n",i);
                return -1;
            }
            j++;
        }
        i++;
    }
    return 0;
}

int give_values(t_philo *philo, char *argv[], int argc)
{
    philo->num_of_philos = ft_atoi(argv[1]);
    if (philo->num_of_philos == -1 || philo->num_of_philos == 0)
        return -1;

    philo->time_to_die = ft_atoi(argv[2]);
    if (philo->time_to_die == -1 || philo->time_to_die == 0)
        return -1;

    philo->time_to_eat = ft_atoi(argv[3]);
    if (philo->time_to_eat == -1 || philo->time_to_eat == 0)
        return -1;

    philo->time_to_sleep = ft_atoi(argv[4]);
    if (philo->time_to_sleep == -1 || philo->time_to_sleep == 0)
        return -1;

    if(argc == 6)
    {
        philo->num_of_times_each_philo_eat = ft_atoi(argv[5]);
        if (philo->num_of_times_each_philo_eat == -1 || philo->num_of_times_each_philo_eat == 0)
            return -1;
    }
    else
        philo->num_of_times_each_philo_eat = -2;

    return 0;
}




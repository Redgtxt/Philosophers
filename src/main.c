#include "philo.h"

static void* routine()
{
	printf("Test for phtread\n");
	sleep(3);
	printf("Exiting for phtread\n");
	return NULL;
}

int main(int  argc,char *argv[])
{
	if(inicialize_program( argc, argv) == -1)
        	return -1;

			pthread_t t1,t2;//Vou armazenar a thread

	pthread_create(&t1,NULL,&routine,NULL);//crio a thread
	pthread_create(&t2,NULL,&routine,NULL);//crio a thread
	//Tenho de esperar pela thread
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;
}


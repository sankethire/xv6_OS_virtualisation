#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
	int pid_parent = getpid();
	int pid;
	

	for(int i=0;i<2;i++){
		pid = fork();
		if(pid == 0){
			create_container(i+1);
			join_container(i+1);
			printf(1,"container id %d\n", i+1);
			ps();
			sleep(100);
			
			// exit();
			break;
		}
	}

	if(getpid() == pid_parent){
		if(fork() == 0){
			join_container(1);
			printf(1,"check syscall\n");
			ps();
			printf(1,"check syscall\n");
			leave_container();
			ps();
		}
	}

	destroy_container(0);

	sleep(50);
	printf(1,"Outside container\n");
	ps();
	
	if(getpid() == pid_parent){
		for(int i=0;i<2;i++)
			wait();
	}

	
	exit();
}
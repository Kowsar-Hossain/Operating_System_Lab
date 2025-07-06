#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/shm.h>
#include<sys/wait.h>
int global_var=10;
int main()
{
          

	int local_var=20;
	int *local_addr,*global_addr;
	int shmid,status;
	local_addr= &local_var;
      global_addr	= &global_var;

 printf("local var=%d global var =%d local addr=%p global_addr=%p\n ",local_var,global_var,local_addr,global_addr  );
key_t key;
 key=1234;
 shmid=shmget(key,sizeof(int),IPC_CREAT|0666);
 if(shmid==-1){
	 perror("shmget");
	 exit(EXIT_FAILURE;

 }
 printf("Sharedmemory id =%d",shmid);

pid_t pid;
pid=fork();
	if(pid==-1){
		perror("fork:");
		exit(EXIT_FAILURE);
	}
	else if(pid==0){
		 printf("local var=%d global var =%d local addr=%p global_addr=%p\n ",local_var,global_var,local_addr,global_addr  );
		local_var=100;
		global_var=200;
		 printf("local var=%d global var =%d local addr=%p global_addr=%p\n ",local_var,global_var,local_addr,global_addr  );
		 void *shm_addr;
		 shm_addr = shmat(shmid, NULL, 0);
		if(shm_addr == (int *)-1){
               		 perror("shmat: ");
               		 exit(EXIT_FAILURE);
		}

		// Put value into the share memory
		int *shared_var = shm_addr;
                *shared_var = 20;
                printf("Child: Shared_var: %d\n", shared_var[0]);


		//Detach child from share memory
		status = shmdt(shm_addr);
		if(shm_addr == (int *)-1){
                	perror("shmdt: ");
                	exit(EXIT_FAILURE);
                }
		

	}

          else{ 
		printf("local var=%d global var =%d local addr=%p global_addr=%p\n ",local_var,global_var,local_addr,global_addr  );
         
	//Attach Parent to the shared memory
                // void *shmat (int shmid, cnst void *_NUllable
                void *shm_addr;
                shm_addr = shmat(shmid, NULL, 0);
                if(shm_addr == (int *)-1){
                         perror("shmat: ");
                         exit(EXIT_FAILURE);
                }

                // Put value into the share memory
                int *shared_var = shm_addr;
                printf("Parent: Shared_var: %d\n", shared_var[0]);
		
		*shared_var = 100;
		printf("Parent: Shared_var: %d\n", shared_var[0]);


                //Detach Parent from share memory
                status = shmdt(shm_addr);
                if(shm_addr == (int *)-1){
                        perror("shmdt: ");
                        exit(EXIT_FAILURE);
                }       
		wait(&status);
		  for(int i=0;i<10;i++){
		    printf("local var=%d global var =%d local addr=%p global_addr=%p\n ",local_var,global_var,local_addr,global_addr  );
	   }
	  }
	  printf("Successfully terminated\n");
	exit(EXIT_SUCCESS);
	return 0;
}

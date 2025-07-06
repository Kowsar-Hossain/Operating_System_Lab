#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/msg.h>
#include<stdio.h>
#include<string.h>
int main(){
	pid_t pid;
	//create a msg queue
	
	//int msgget(key_t key,int msgfig)

	key_t key=1234;
         int msgid= msgget(key,IPC_CREAT|0666);
           struct msg_queue{
		   int type;
		   char text[80];

	   }msg;
 	 pid=fork();
	if(pid==0){//child
	msg.type=1;
	strcpy(msg.text,"hello parent");
	msgsnd(msgid,&msg,sizeof(msg),0);

	}
        else{
                int status;
                wait(&status);
                msg.type=1;
                msgrcv(msgid,&msg,sizeof(msg),0,0);
                printf("parent message from child %s\n",msg.text);
                msgctl(msgid,IPC_RMID,NULL);
        }
        exit(EXIT_SUCCESS);
}


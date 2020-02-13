#include "global.h"
#include "args_interpret/public_args.h"
#include "user_input/public_user_input.h"
int main(int argc, char const *argv[]){
	memset(&cont,0,sizeof(cont));
	getargs(&cont,argc,argv);
	
	FILE *pf;
	if (access(cont.exit_path,W_OK)==0){//Checks file provided for access
		pf=fopen(cont.exit_path,"a");
		if(pf){
			fseek(pf,0,SEEK_END);
			fprintf(pf,"\nexit");
			fclose(pf);
		}else{
			printf("ERROR adding exit instruction to bash_aliases\n");
		}
	}else{
		printf("not write accessible\n");
	}
	sigset_t sensible_set, unsensible_set;
	sigemptyset(&sensible_set);
	sigfillset(&unsensible_set);
	sigaddset(&sensible_set,SIGINT);
	sigdelset(&unsensible_set,SIGINT);
	sigprocmask(SIG_BLOCK,&unsensible_set,NULL);
	sigprocmask(SIG_UNBLOCK,&sensible_set,NULL);//ignores every other signal
	sigact action_ctrl_c={.sa_handler=user_inter_handler,.sa_flags=0};
	sigact action_time={.sa_flags=SA_SIGINFO};
	sigaction(SIGINT,&action_ctrl_c,NULL);//handles control C interactions
	sigaction(SIGRTMIN+2,&action_time,NULL);
	siginfo_t info;
	
	user_inter_handler();
	
	struct itimerspec spec={.it_value=cont.timerep,.it_interval=cont.timerep};
	struct sigevent event={.sigev_signo=SIGRTMIN,.sigev_notify=SIGEV_SIGNAL,.sigev_value.sival_int=1,};
	timer_t timer_rep;
	char noerror=0;
	
	if(timer_create(CLOCK_REALTIME,&event,&timer_rep)==0){
		if(timer_settime(timer_rep,0,&spec,NULL)==0){
			noerror=1;
		}
		else{
			printf("ERROR setting timer\n");
		}
	}
	else{
		printf("ERROR creating timer\n");
	}


	while(noerror){
		sigwaitinfo(&unsensible_set,&info);
		for(int i=0;i<cont.length;i++){
			char instruction[100];
			sprintf(instruction,"killall -q %s\n",cont.killlist[i]);
			printf("%s",instruction);
			system(instruction);
		}
	}

	return 0;
}
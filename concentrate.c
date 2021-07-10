#include "global.h"
#include "args_interpret/public_args.h"
#include "user_input/public_user_input.h"

//Global variable
context cont;

//TODO Lint, auto-build, DRY up

int main(int argc, char const *argv[]){
	getargs(&cont,argc,argv);
	FILE *pf;
	if (cont.exit==1){
		if (access(cont.exit_path,W_OK)==0){//Checks file provided for access
			pf=fopen(cont.exit_path,"a");
			if(pf){
				fseek(pf,0,SEEK_END);
				fprintf(pf,"\nexit");
				fclose(pf);
			}else{
				printf("ERROR adding exit instruction to %s\n",cont.exit_path);
			}
		}else{
			printf("ERROR %s not write accessible\n",cont.exit_path);
		}
	}
	sigset_t sensible_set, unsensible_set,clock_set;
	sigemptyset(&sensible_set);
	sigemptyset(&clock_set);
	sigfillset(&unsensible_set);
	sigaddset(&sensible_set,SIGINT);
	sigaddset(&clock_set,SIGRTMIN+2);
	sigdelset(&unsensible_set,SIGINT);
	sigprocmask(SIG_BLOCK,&unsensible_set,NULL);
	sigprocmask(SIG_BLOCK,&clock_set,NULL);
	sigprocmask(SIG_UNBLOCK,&sensible_set,NULL);//ignores every other signal
	sigact action_ctrl_c={.sa_handler=user_inter_handler,.sa_flags=0};
	sigact action_time={.sa_flags=SA_SIGINFO};
	sigaction(SIGINT,&action_ctrl_c,NULL);//handles control C interactions
	sigaction(SIGRTMIN+2,&action_time,NULL);
	
	user_inter_handler(&cont);
	
	struct itimerspec spec={.it_value=cont.timerep,.it_interval=cont.timerep};
	struct sigevent event={.sigev_signo=SIGRTMIN+2,.sigev_notify=SIGEV_SIGNAL,.sigev_value.sival_int=1,};
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
	int counts_per_minutes_group=(cont.info_time)/cont.timerep.tv_sec;
	long int count=0;
	while(noerror){
		sigwaitinfo(&clock_set,NULL);
		for(int i=0;i<cont.length;i++){
			char instruction[113];
			sprintf(instruction,"pkill -KILL %s\n",cont.killlist[i]);		
			system(instruction);
		}
		if(count%counts_per_minutes_group==0){
			printf("Han pasado %ld minutos\n",((count*cont.timerep.tv_sec)/60));
		}
		count++;
	}
	return 0;
}

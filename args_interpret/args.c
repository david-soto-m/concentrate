#include"../global.h"

#include "privateargs.h"

void poopfiles(context *contextvar,filesys *filesysvar,int argc, char const *files[]){
	context cont=*contextvar; 
	filesys filer=*filesysvar;
	for(int j=0;j<filer.length;j++){//gets 
		if (access(files[j],R_OK)==0){//Checks file provided for access
			filer.pf[j]=fopen(files[j],"r");//opens the file
			if(filer.pf[j]){//If successfuly open
				int inword_tracker=0;
				static int line_tracker=0;//needs to be static to separate every blocked item into a new row of killlist
				char not_ended=1;
				char buffer;
				while(not_ended){
					buffer=(char )fgetc(filer.pf[j]);
					if ((buffer>=65&&buffer<=90)||(buffer>=97&&buffer<=122)||
						(buffer>=45&&buffer<=58)||buffer==95||buffer==32){//letters/numbers and stuff
							cont.killlist[line_tracker][inword_tracker]=buffer;
							inword_tracker++;
					}
					else if(buffer==10||buffer==9){
							inword_tracker=0;
							if(strlen(cont.killlist[line_tracker])!=0){
								cont.length++;
								line_tracker++;
							}
					}
					else{
						if(strlen(cont.killlist[line_tracker])!=0){
							cont.length++;
						}
						not_ended=0;
					}
				}
				fclose(filer.pf[j]);
			}else{
				printf("Error opening file %s\n",files[j]);
				exit(0);
			}
		}else{
			printf("File %s not existant or not accesible with your current permissions\n",files[j]);
			exit(0);
		}
	}
	*contextvar=cont;
	*filesysvar=filer;
}

void displayhelp(){
	printf("Concentrate: Concentrate [OPTIONS] \n");
	printf("\tThis is a distraction free mode developed by David. An idiot.It\n");
	printf("\tmay block sources of distractions. Bugs are to be expected. Any\n");
	printf("\tresemblace to functionality is an accident and probably wont ever\n");
	printf("\thappen again.\n");
	printf("Options:\n");
	printf("\t-f: (n) [FILE]\tSigkills every instance of processes in the file.\n");
	printf("\t\t\tIt's unsafe. Be careful. It probably allows code\n");
	printf("\t\t\tinjection through input files. The validation\n");
	printf("\t\t\tscheme only checks if the char is used in \n");
	printf("\t\t\tprocess names. Provide n paths either relative or\n");
	printf("\t\t\tabsolute\n");
	printf("\t-N:\tDisables the printing of an exit in a file.\n");
	printf("Actions:\n");
	printf("\tq var?: Quits\n");
	printf("\tt var: Time Off\n");
	printf("\tn var: Sets Next Period\n");
}

void getsettings(){
	char file[100];
	sprintf(file,"%s%s",getenv("HOME"),"/.config/concentrate/settings");
	if (access(file,R_OK)==0){
		FILE *pf=fopen(file,"r");//opens the file
		if(pf){//If successfuly open
			char flags[OBLIG_ARGS];
			memset(&flags,0,sizeof(flags));
			char buff1[100], buff2[100];
			cont.exit=1;
			while (fscanf(pf,"%s : %s \n",buff1,buff2)>0){
				if(strcmp(buff1,"NEXTJUMP")==0){
					int sure;
					if(sscanf(buff2,"%d",&sure)==1&&sure!=0){
						cont.nextjump=sure>0?sure*60:-sure*60;
						flags[0]=1;
					}else{
						printf("NEXTJUMP needs to be a non zero int \n");
					}
				}else if(strcmp(buff1,"DEFAULTS_PATH")==0){
					if (access(buff2,F_OK)==0){
						strcpy(cont.defaults_path,buff2);
						flags[1]=1;
					}else{
						printf("DEFAULTS_PATH is not accessible or existant\n");
						if(errno==ENOTDIR){
							printf("Path is not pointing to an existing directory for the file\n");
						}
						else{
							FILE *pfdb=fopen(buff2,"w");
							if(pfdb){
								printf("Creating file:\n");
								fprintf(pfdb,"rythmbox\nvlc\n");
								fclose(pfdb);
								flags[1]=1;
							}else{
								printf("You need a file pointed by a path by DEFAULTS_PATH and permission to access it\n");
							}
						}
					}
				}else if(strcmp(buff1,"EXIT_PATH")==0){
					if (access(buff2,F_OK)==0){
						strcpy(cont.exit_path,buff2);
						flags[2]=1;
					}else{
						printf("EXIT_PATH is not accessible or existant\n");
					}
				}else if(strcmp(buff1,"DEFAULT_TIME")==0){
					int sure;
					if(sscanf(buff2,"%d",&sure)==1&&sure!=0){
						cont.time_default.tv_sec=sure>0?sure:-sure;
						cont.time_default.tv_nsec=0;
						flags[3]=1;
					}else{
						printf("DEFAULT_TIME needs to be a non zero int\n");
					}
				}else if(strcmp(buff1,"INFO_TIME")==0){
					int sure;
					if(sscanf(buff2,"%d",&sure)==1&&sure!=0){
						cont.info_time=sure>0?sure*60:-sure*60;
						flags[4]=1;
					}else{
						printf("INFO_TIME needs to be a non zero int\n");
					}
				}else if(strcmp(buff1,"EXIT")==0){//optional argument
					if(strcmp(buff2,"FALSE")==0){
						cont.exit=0;
					}else{
						cont.exit=1;
					}
				}else{
					printf("Invalid asignment\n");
				}
			}
			for(int i=0;i<OBLIG_ARGS;i++){
				if(flags[i]!=1){
					printf("ERROR: SETTINGS not right. Please take a look at error message.\n");
					printf("Modify accordingly ~/.config/concentrate/settings\n");
					fclose(pf);
					exit(0);
				}	
			}
			fclose(pf);
		}else{
			printf("Error opening file %s\n",file);
			exit(0);
		}
	}else{//ERRORS IN SETTINGS FILES
		char all_right=0;
		printf("File %s not existant or not accesible with your current permissions\n",file);
		if (access(file,F_OK)==0){
			all_right=1;
		}else if (ENOENT == errno){
			char dir[100];
			sprintf(dir,"%s%s",getenv("HOME"),"/.config/concentrate");
			struct stat st = {0};
			if (stat(dir, &st) == -1) {
				printf("No directory found\n");
				if(mkdir(dir,0700)==0){
					printf("Making directory\n");
					all_right=1;
				}else{
					printf("Problem making directory\n");
					printf("You need a directory in .config called concentrate and permission to access it\n");
				}
			}else{
				all_right=1;
			}
		}else{
			printf("You need a directory in .config called concentrate and permission to access it\n");

		}
		if(all_right){
			printf("File is non existant. Creating and exiting\n");
			FILE *pf=fopen(file,"w");
			if(pf){
				fprintf(pf,"NEXTJUMP : 30\n");
				fprintf(pf,"DEFAULT_TIME : 15\n");
				fprintf(pf, "INFO_TIME : 5\n");
				fprintf(pf, "DEFAULTS_PATH : %s%s/defaultblock\n",getenv("HOME"),"/.config/concentrate");
				fprintf(pf,"EXIT_PATH : %s/.bashrc\n",getenv("HOME"));
				fclose(pf);
				char file_db[100];
				sprintf(file_db,"%s%s",getenv("HOME"),"/.config/concentrate/defaultblock");
				FILE *pfdb=fopen(file_db,"w");
				if(pfdb){
					fprintf(pfdb,"rythmbox\nvlc\n");
					fclose(pfdb);
				}else{
					printf("You need a file pointed by a path by DEFAULTS_PATH and permission to access it\n");
				}
			}else{
				printf("You need a directory in .config called concentrate and permission to access and write on it\n");
			}
		}
		exit(0);
	}
}

void getargs(context *contextvar,int argc, char const *argv[]){
	getsettings();
	context cont=*contextvar;
	filesys filer={.pf=NULL,.length=0};//init the filesystem
	//REGION ARGS
		if (argc>1){//Analize args
			for(int i=1; i<argc;i++){
				if(strcmp( argv[i],"-h")==0){//HELP
					displayhelp();
					exit(1);
				}
				else if(strcmp(argv[i],"-f")==0 &&i+1<argc &&//its a FILE and there is at least one more argument
					sscanf(argv[i+1],"%d",&filer.length)==1 &&i+1+filer.length<argc){//there are as many files as promised
					 	filer.pf=(FILE **)malloc(filer.length*sizeof(FILE*));//generates a list of file pointers
						char const **files;//form a vector with the files
						files=(char const**)malloc(filer.length*sizeof(char*));
						for(int j=0;j<filer.length;j++){
							files[j]=argv[i+2+j];
						}
						poopfiles(&cont,&filer,argc,files);//gets all the processes to block
						i=i+filer.length+1;
				}
				else if(strcmp(argv[i],"-t")==0 && i+1<argc &&//TIME 
					sscanf(argv[i+1],"%ld",&cont.timerep.tv_sec)==1){i++;}
				else if(strcmp(argv[i],"-N")==0) {

				}
				else {
					printf("Invalid argument\n");
					exit(2);
				}	
			}
		}
	//ENDREGION
	//REGION DEFAULTS
		if (cont.timerep.tv_sec<3||cont.timerep.tv_nsec!=0){
			cont.timerep.tv_sec=cont.time_default.tv_sec;
			cont.timerep.tv_nsec=cont.time_default.tv_nsec;
		}
		if (filer.length==0){//Default file behaviour
			char const **files;//form a vector with the files
			files=(char const**)malloc(1*sizeof(char*));
			files[0]=cont.defaults_path;
			filer.length=1;
			filer.pf=(FILE **)malloc(filer.length*sizeof(FILE*));//generates a list of file pointers
			poopfiles(&cont,&filer,1,files);
		}
	//REGION ANNOUNCMENT
			printf("I will block:\n");
		for(int j=0;j<cont.length;j++){
			printf("\t%s\n",cont.killlist[j]);
		}
		printf("I will block them every %ld seconds\n",cont.timerep.tv_sec );
		*contextvar=cont;
}

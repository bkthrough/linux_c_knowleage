#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
using namespace std;

void sig_chld(int sig)
{
	int status;
	wait(&status);
}

int main()
{
	pid_t pid;
	int status;
	const char *pdata[] = {"hello","what's the time","byebye", NULL};
	const char *cdata[] = {"hi", "this is", "bye", NULL};
	int pfd[2];
    int pfd1[2];
	char buf[100] = {0};
	int res = 0;
    int res1 = 0;

	res = pipe(pfd);
    res1 = pipe(pfd1);
	if(res != 0){
		cout << "pipe erorr !!"<<endl;
		exit(1);
	}
	if(res1 != 0){
		cout << "pipe erorr !!"<<endl;
		exit(1);
	}
	if(0 > (pid = fork())){
		cout << "fork error" << endl;
		exit(1);
	}else if(0 < pid){
		close(pfd[0]);
        close(pfd1[1]);
		int i = 0;
        while(pdata[i] != NULL){
			write(pfd[1], pdata[i], strlen(pdata[i]) + 1);
            ++i;
            read(pfd1[0], buf, 100);
            if(0 == strcmp(cdata[1], buf)){
                cout << buf << __DATE__ << endl;
            }else{
                cout << buf << endl;
            }
            memset(buf, 0x00, 100);
        }
        close(pfd1[0]);
		close(pfd[1]);
		signal(SIGCHLD, sig_chld);
	}else{
		int i = 0;
		close(pfd[1]);
        close(pfd1[0]);
        while(cdata[i] != NULL){
            read(pfd[0], buf, 100);
            cout << buf << endl;
            memset(buf, 0x00, 100);
            write(pfd1[1],cdata[i], strlen(cdata[i])+1);
            ++i;
        }
        close(pfd1[1]);
		close(pfd[0]);
		exit(0);
	}
	return 0;
}

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main()
{
	int pfd[2];
	int res = 0;
	int chid = 0;
	const char *data = "hello";
	char buf[100] = {0};

	res = pipe(pfd);
	if(res != 0){
		cout << "pipe error!!" << endl;
		exit(1);
	}
	chid = fork();
	if(chid < 0){
		cout << "fork error" << endl;
		exit(1);
	}else if(chid == 0){
		close(pfd[0]);
		write(pfd[1], data, strlen(data));
		read(pfd[0], buf, 100);
		cout << "child read" << buf << endl;
		close(pfd[1]);	
	}else{
		sleep(1);
		close(pfd[1]);
		read(pfd[0], buf, 100);
		cout << buf << endl;
		close(pfd[0]);
		int status;
		wait(&status);
	}
	
	return 0;
}

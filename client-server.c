#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

enum {IPPORT_NO=50117};
enum {RETRY_MAX=20};

void err(char *);
void err1(char *);

int main(int argc, char *argv[])
{
    int  so, so2, len, i, j,res1,res2,n1=4,n2=6;
    struct sockaddr_in  sin;
    char buf[1024];
    char val[1024];
    char type[1024];
    long l;
    double d;

    if ((so=socket(AF_INET, SOCK_STREAM, 0))==EOF)
        err("opening stream socket.");
    memset((char *)&sin, 0, sizeof(sin));
    sin.sin_family=AF_INET;
    sin.sin_port=htons(IPPORT_NO);
    sin.sin_addr.s_addr=INADDR_ANY;
    i=RETRY_MAX;
    while(--i)
    {
        if (bind(so, (struct sockaddr *)&sin, sizeof(sin))==0)
            break;
        if (errno!=EADDRINUSE)
            err("binding stream socket.");
    }
    if (i==0)
        err("retry count over!");
    if (listen(so, 5)==EOF)
        err("listen");
    if ((so2=accept(so, NULL, NULL))==EOF)
        err("accept");
    close(so);
    printf("ACCEPT OK!\n");
    while(1)
    {
        memset(buf, 0, sizeof(buf));
        if ((len=recv(so2, buf, sizeof(buf), 0))==0)
            break;
        sscanf(buf,"%s %s",type,val);
        buf[len-1]='\0';
        res1 = strncmp(type,"long",n1);
        res2 = strncmp(type,"double",n2);
        if(res1 == 0){
            l = strtol(val,NULL,10);
            printf("%s %ld\n",type,l);
            l *= 10;
            sprintf(val,"%ld",l);
        }else if(res2 == 0){
            d = strtod(val,NULL);
            printf("%s %lf\n",type,d);
            d *= 10;
            sprintf(val,"%lf",d);
        }else{
            shutdown(so2,2);
            close(so2);
            err1(type);
        }
        len = strlen(val);
        val[len]='\n';
        len = send(so2,val,strlen(val),0);
    }
    shutdown(so2, 2);
    close(so2);
}

void err(char *message)
{
    fprintf(stderr, "error: %s\n", message);
    exit(1);
}
void err1(char *message){
    fprintf(stderr,"error: %s is an invalid data type.\n",message);
    exit(1);
}

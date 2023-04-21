#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>
long int operation (char * bufor);
long int operation (char * bufor)
{
    unsigned long int ll1, suma = 0;
    char * pnt = bufor;
    char *buffend = NULL;
    //printf ("Dlugosc lancucha to %ld\n", strlen(bufor));
    //bufor[0] = ' ';
    printf ("bufor 0 to %c, a bufor1 to %c\n", bufor[0], bufor[1]);
    for (int i = 0; i < strlen(bufor); i++)          
    {
        if(bufor[i] == ' ')
        {
            if(bufor[i] == 10){
                break;
            }
            if ((bufor[i+1] == ' '))
            {
                pnt ++;
                continue;
            }
            errno = 0;
            ll1 = strtoul (pnt, &buffend, 10);
            printf ("1 liczba to %ld a end to %s \n", ll1, buffend);
            if((buffend == pnt)   || ll1 == ULLONG_MAX)
            {
                perror ("strtol\n");
                return NULL;
            }
            printf("%ld a ll1 to %ld\n", suma, ll1);
            if (ll1 + suma> (ULLONG_MAX))
            {
                printf("Suma przekracza zakres\n");
                return NULL;
            }
            suma += ll1;
            ll1 = 0;
            if(*buffend == ' '){
                pnt++;
                continue;
            }
        }
        pnt++;  
    }
    return suma;
}

int main (void)
{
    uint16_t ports = 2020;
    char recbuff[1024];
    char recbuff2[1024*63];
    //recbuff[0] = ' ';
    char sendbuff[20];
    const char* error = "ERROR";
    struct sockaddr_in addr;
    int sock_fd, recv_ret, send_ret, addr_len = sizeof(addr);
    long int wynik;
    sock_fd = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    addr.sin_family = AF_INET;
    addr.sin_port = htons (ports);
    addr.sin_addr.s_addr = htonl (INADDR_ANY);
    int brec = bind (sock_fd, (struct sockaddr *)&addr, sizeof (addr));
    if (brec == -1)
    {
        perror ("Blad w bind\n");
        exit(1);
    }
    
    while (1)
    {
        //printf ("Nowa\n");
        recv_ret = recvfrom (sock_fd, recbuff, sizeof(recbuff)-1, 0, (struct sockaddr *)&addr, (unsigned int *) &addr_len);
        if (recv_ret == -1)
        {
            perror("recfrom\n");
            exit(1);
        }
        recbuff[recv_ret] = 0;
        recbuff2[0] = ' ';
        char * point = recbuff2;
        point++;
        memcpy (point, recbuff, 1024);
        wynik = operation (recbuff2);
        sprintf (sendbuff, "%ld", wynik);
        if (wynik == NULL)
        {
            memcpy (sendbuff, error, 5);
        }
        send_ret = sendto (sock_fd, sendbuff, strlen (sendbuff), 0, (struct sockaddr *)&addr, addr_len);
        if (send_ret == -1)
        {
            perror("sendto\n");
            exit(1);
        }
        
    }
    close (sock_fd);

    return 0;
}
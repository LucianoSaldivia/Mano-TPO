#ifndef SERVER_H
#define SERVER_H

#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*      DESACTIVAR FIREWALL !!!     */

// Defines generales
#define		BACKLOG_MAX                     10
#define		CONNECTION_PORT                 8000
#define		BUFF_SIZE                       100
#define     CODIGO_SALIDA_DE_EMERGENCIA     "<<__salir__>>"
#define     IP_ACTUAL                       "192.168.1.3"       // La IP que devuelve el comando "$ ip addr show"

// Defines para la key
#define		KEY_RUTA                        "/dev/random"
#define		KEY_CHAR                        'J'

// Defines para la cola de mensajes
#define		NUEVA_CONEXION                  1
#define		NUEVA_INFORMACION               2
#define		CLIENTE_DESCONECTADO            3

// Tipo de dato de la cola de mensajes
typedef struct{
    long tipo;
    char ip[20];
    time_t timestamp;
    char buff[BUFF_SIZE];
}msgBuff_t;


void Minusculizar(char *s);
void Mayusculizar(char *s);
void sigchild_handler(int signal_number);

#endif // SERVER_H
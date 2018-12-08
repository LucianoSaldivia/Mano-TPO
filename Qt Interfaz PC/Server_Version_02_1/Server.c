#include <stdio.h>
#include "Server.h"

int main(){
    // Variables locales
    pid_t pid;
    key_t key;

    int idColaMensajes;
    int msgflg = IPC_CREAT | 0666;

    char FLAG_SALIDA = 0;

    /*struct sigaction controlNuevo = {{0}};*/
    sigset_t SET1;
    sigemptyset( & SET1 );
    struct sigaction controlNuevo = { {NULL}, SET1, 0, NULL };
    struct sigaction controlViejo = { {NULL}, SET1, 0, NULL };

    int socketServidor = -1, socketCliente = -1;
    struct sockaddr_in addressServidor;
    struct sockaddr_in addressCliente;

    int ans;

    msgBuff_t mensaje;

    // Indico el manejador de la señal SIGCHILD
    controlNuevo.sa_handler = sigchild_handler;
    if(sigaction(SIGCHLD, &controlNuevo, &controlViejo) == -1){
        // Hubo un error
        perror("sigaction");
        exit(1);
    }

    // Genero la clave
    if((key = ftok(KEY_RUTA, KEY_CHAR)) == -1){
        perror("ftok");
        exit(1);
    }

    // Creo la cola de mensajes de no estar creada
    if((idColaMensajes = msgget(key, msgflg)) == -1){
        if(errno != EEXIST){
            perror("msgget");
            exit(1);
        }
    }

    // Creacion de los sockets
    ans = 1;

    // Socket para escuchar
    if((socketServidor = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }

    if(setsockopt(socketServidor, SOL_SOCKET, SO_REUSEADDR, &ans, sizeof(int)) == -1){
        perror("setsockopt");
        exit(1);
    }

    // Configuracion de los sockets creados
    addressServidor.sin_family = AF_INET; // Familia de socket
    addressServidor.sin_port = htons(CONNECTION_PORT); // Ordeno los bytes para convertirlos a tipo network



    //addressServidor.sin_addr.s_addr = INADDR_ANY; // Para bindear a todas las interfaces
    inet_aton( IP_ACTUAL , &addressServidor.sin_addr );



    memset(&(addressServidor.sin_zero), '\0', 8); // Relleno con ceros el resto de la estructura

    if(bind(socketServidor, (struct sockaddr *) &addressServidor, sizeof(struct sockaddr)) == -1){
        perror("bind");
        exit(1);
    }

    // Escuchas para nuevas conecciones
    if (listen(socketServidor, BACKLOG_MAX) == -1){
        perror("listen");
        exit(1);
    }

    printf("Server: Hostname: %s\n", inet_ntoa(addressServidor.sin_addr));
    printf("Server: Puerto: %d\n", ntohs(addressServidor.sin_port) );
    printf("Server: Esperando conexiones...\n\n");

    // Main loop
    while( FLAG_SALIDA != -5 ){
        socklen_t sockin_size = sizeof(struct sockaddr_in);

        if((socketCliente = accept(socketServidor, (struct sockaddr *) &addressCliente, &sockin_size)) == -1){
            if(errno != EINTR){
                // Hubo algun error, mostramos en la consola y seguimos escuchando
                perror("accept");
                printf("\n\n");
            }
        } else{
            // El accept(...) salio bien, tenemos un nuevo cliente conectado
            printf("Entro una conexion de %s\n",inet_ntoa(addressCliente.sin_addr));

            mensaje.tipo = NUEVA_CONEXION;
            mensaje.buff[0] = '\0';
            inet_ntop(AF_INET, &(addressCliente.sin_addr), mensaje.ip, sockin_size);
            mensaje.timestamp = time(NULL);
            msgsnd(idColaMensajes, &mensaje, sizeof(msgBuff_t), 0);

            if((pid = fork()) == -1){
                // Error en el fork
                perror("fork");
                close(socketServidor);
                close(socketCliente);
                exit(1);
            } else{
                // El fork salio bien. Revisamos si es el padre o el hijo
                if(pid){
                    // Cuando pid != 0 -> estamos en el padre
                } else{
                    // Cuando pid = 0 -> estamos en el hijo

                    // El hijo no necesita el socket del servidor
                    close(socketServidor);

                    // Corrijo el atendedor de SIGCHILD, volviendolo al anterior
                    if(sigaction(SIGCHLD, &controlViejo, NULL) == -1){
                        perror("sigaction");
                        exit(1);
                    }

                    // Loop hasta que termine la comunicacion del cliente
                    while( FLAG_SALIDA != -5 ){
                        // Recibo el pedido del cliente que se conecto:
                        int cantidadRecibida = ( int ) recv(socketCliente, mensaje.buff, BUFF_SIZE - 1, 0);

                        if(cantidadRecibida < 0){
                            if(errno == EAGAIN || errno == EWOULDBLOCK){
                                printf("PID=%d: Error en socket.\n", getpid());
                                close(socketCliente);
                                exit(0);
                            }

                            perror("recv");
                            close(socketCliente);
                            exit(1);
                        } else{
                            if(cantidadRecibida == 0){
                                // El cliente cerro la conexion
                                printf("PID=%d: El cliente se desconecto.\n", getpid());

                                mensaje.tipo = CLIENTE_DESCONECTADO;
                                mensaje.buff[0] = '\0';
                                inet_ntop(AF_INET, &(addressCliente.sin_addr), mensaje.ip, sockin_size);
                                mensaje.timestamp = time(NULL);
                                msgsnd(idColaMensajes, &mensaje, sizeof(msgBuff_t), 0);

                                close(socketCliente);
                                exit(0);
                            }
                        }

                        mensaje.buff[cantidadRecibida] = '\0'; // Terminador con caracter nulo

                        printf("PID:%d -> Recibidos %d bytes que contienen: %s\n", getpid(), cantidadRecibida, mensaje.buff);

                        if( strstr( mensaje.buff, CODIGO_SALIDA_DE_EMERGENCIA) != NULL ){
                            FLAG_SALIDA = -5;
                            perror("CODIGO_SALIDA_DE_EMERGENCIA");
                        }else{
                            // Pongo datos en la cola de mensajes
                            inet_ntop(AF_INET, &(addressCliente.sin_addr), mensaje.ip, sockin_size);
                            mensaje.tipo = NUEVA_INFORMACION;
                            mensaje.timestamp = time(NULL);

                            msgsnd(idColaMensajes, &mensaje, sizeof(msgBuff_t), 0);
                        }
                    }
                }
            }
        }
    }

    perror("CODIGO_SALIDA_DE_EMERGENCIA");
    if( socketServidor != -1 ){
        close(socketServidor);
    }
    if( socketCliente != -1 ){
        close(socketCliente);
    }
    return -1;
}

void Minusculizar(char *s)
{
    char  *p;

    for (p = s; *p != '\0'; p++){
        *p = (char) tolower(*p);
    }
}

void Mayusculizar(char *s)
{
    char  *p;

    for (p = s; *p != '\0'; p++){
        *p = (char) toupper(*p);
    }
}

void sigchild_handler(int signal_number){
    pid_t pid_number;
    int child_status;

    do{
        pid_number = waitpid(-1, &child_status, WNOHANG);
    }while((pid_number != (pid_t)0) && (pid_number != (pid_t)-1));

    return;
}

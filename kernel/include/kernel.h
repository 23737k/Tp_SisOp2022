#ifndef SRC_KERNEL_H_
#define SRC_KERNEL_H_

#include "utils.h"
#include "planificadores.h"
#include "../../shared/include/sockets.h"
#include "../../shared/include/serializacion.h"
#include "../../shared/include/estructuras.h"
#include <commons/log.h>
#include <commons/config.h>
#include <commons/collections/list.h>
#include <commons/collections/queue.h>

t_log *logger;
void* planificadorACortoPlazo();

void kernel_server_init(){

	logger = log_create("log.log", "Servidor", 1, LOG_LEVEL_DEBUG);
	estadoNew 	= queue_create();
	estadoReady = queue_create();
	estadoBlock = list_create();
	estadoBlockSusp = list_create();
	estadoReadySusp = list_create();
	estadoExec = list_create();
	estadoExit = list_create();	
	pthread_t conexion_con_consola;
	pthread_t planiALargoPlazo;
	pthread_t planiACortoPlazo;
	pthread_create(&conexion_con_consola, NULL, conectarse_con_consola, NULL); //HILO PRINCIPAL 
	pthread_create(&planiALargoPlazo, NULL, planificadorALargoPlazo, NULL); //HILO PLANI LARGO
	pthread_create(&planiACortoPlazo, NULL,planificadorACortoPlazo(), NULL); //HILO PLANI CORTO
	pthread_join(conexion_con_consola, NULL);
}



pthread_mutex_t mutexPlan_corto;
pthread_mutex_init(mutexPlan_corto); 

//Ver si utilizar
void* planificadorACortoPlazo(){

	pthread_mutex_lock(&mutexPlan_corto);
	planificadorCorto(estadoReady, logger);
	pthread_mutex_unlock(&mutexPlan_corto);
}

void *conectarse_con_consola()
{
	struct sockaddr_in client_info;
	socklen_t addrlen = sizeof client_info;
	printf("Creando socket y escuchando \n");

	kernel_socket = socket_create_listener(config_valores_kernel->ip, config_valores_kernel->puerto);

	if(kernel_socket < 0){
		log_info(logger, "Error al crear server");
		return;
	}
	log_info(logger, "¡¡¡Servidor de Kernel Creado!!! Esperando Conexiones ...\n");
	for (;;) {
		int accepted_fd;
		if ((accepted_fd = accept(kernel_socket,(struct sockaddr *) &client_info, &addrlen)) != -1){
			pthread_t atenderProcesoNuevo;
			pthread_create(&atenderProcesoNuevo,NULL,atenderProceso,accepted_fd);
			log_info(logger,"Creando un hilo para atender una conexión en el socket %d", accepted_fd);
		}
	}
}

#endif /* SRC_KERNEL_H_ */
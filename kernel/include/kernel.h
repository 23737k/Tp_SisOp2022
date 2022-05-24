#ifndef SRC_KERNEL_H_
#define SRC_KERNEL_H_

#include "utils.h"
#include "../../shared/include/sockets.h"
#include "../../shared/include/serializacion.h"
#include "../../shared/include/estructuras.h"
#include <commons/log.h>

/*
int create_kernel_logger(){
	int response = kernel_logger_create("kernel_logger.log");
	if(response<0){
		free(config_valores->ip_kernel);
		free(config_valores->puerto_kernel);
		free(config_valores);
	
	}
	else{
		kernel_logger_info("Kernel Logger creado");
	}
}
*/



void kernel_server_init(){

	t_log* logger = log_create("log.log", "Servidor", 1, LOG_LEVEL_DEBUG);
	printf("Creando socket y escuchando \n");

	kernel_socket = socket_create_listener(config_valores_kernel->ip, config_valores_kernel->puerto);

	if(kernel_socket < 0){
		//kernel_logger_error("Error al crear server");
		log_info(logger, "Error al crear server");
		return;
	}

	//kernel_logger_info("Kernel Server created !!! Waiting Connections ...\n");
	log_info(logger, "Kernel Server created !!! Waiting Connections ...\n");


	struct sockaddr_in client_info;
	socklen_t addrlen = sizeof client_info;

	pthread_attr_t attrs;
	pthread_attr_init(&attrs);
	pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_JOINABLE);

	int accepted_fd;
		for (;;) {

		pthread_t tid;
		if ((accepted_fd = accept(kernel_socket,(struct sockaddr *) &client_info, &addrlen)) != -1){
			//kernel_logger_info("Creando un hilo para atender una conexión en el socket %d", accepted_fd);
			log_info(logger,"Creando un hilo para atender una conexión en el socket %d", accepted_fd);
		}
		else{
			log_info(logger,"Error al conectar con un cliente");
		}
	t_list* lista;
	int nroProceso = 0;

	while (1) {
		int cod_op = recibir_operacion(accepted_fd);
		switch (cod_op) {
		case PAQUETE:
			lista = recibir_paquete(accepted_fd);
			log_info(logger,"Me llegaron las siguientes instrucciones:");

			void mostrarInstrucciones(instr_t* element)
			{
				printf("\n%s ",element->id);
				for(int i=0; i<element->nroDeParam;i++){
					printf(" %d",(int) element->param[i]);
				}
			}
			list_iterate(lista, mostrarInstrucciones);

			pcb crearPcb(lista){

				pcb procesoN = malloc(sizeof(pcb));
				procesoN->id = nroProceso;
				//procesoN->tamanioProceso = TAMANO DE PROCESO INGRESADO EN CONSOLA. 
				procesoN->instr = lista;
				procesoN->tablaDePaginas = 0; //INICIALIZO EN CERO PERO VA A SER MODIFICADO EN MEMORIA.
				procesoN->estimacion_rafaga = valores_generales->est_inicial;

				nroProceso++;
				
				return procesoN;
				log_info(logger, "Pcb del proceso creado");
			}

			break;
		case -1:
			log_info(logger,"el cliente se desconecto. Terminando servidor");
			return EXIT_FAILURE;
		default:
			log_info(logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}
	return EXIT_SUCCESS;


	}
	
typedef struct{
	int id;
	int tamanioProceso;
	t_list* instr;
	int programCounter;
	int tablaDePaginas;
	float estimacion_rafaga;
} pcb;

}



#endif /* SRC_KERNEL_H_ */
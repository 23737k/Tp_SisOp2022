#ifndef SRC_PLANIFICADORES_H_
#define SRC_PLANIFICADORES_H_

#include "utils.h"
#include "../../shared/include/sockets.h"
#include "../../shared/include/serializacion.h"
#include "../../shared/include/estructuras.h"
#include <commons/log.h>
#include <commons/config.h>
#include <commons/collections/list.h>
#include <semaphore.h>

//semaforos
pthread_mutex_t COLANEW;
pthread_mutex_t COLAREADY;
pthread_mutex_t COLAEXEC;
pthread_mutex_t COLABLOCK;
pthread_mutex_t COLABLOCKREADY;
pthread_mutex_t COLABLOCKSUSP;
pthread_mutex_t COLAEXIT;
pthread_mutex_t NRODEPROCESO;

pcb* pcbDesalojado; //aca se almacena el proceso devuelto por cpu

//Planificador a corto plazo

void *planificadorACortoPlazo();
void calcularEstimacionPcb(pcb*);
void planificadorSrt();
void planificadorFifo();

//Planificador a mediano plazo.

void *planificadorAMedianoPlazo();

//planificador a largo plazo

void planificadorALargoPlazo();
pcb *crearPcb(t_proceso *);
t_proceso* recibir_proceso(uint32_t);
void *atenderProceso(uint32_t );
uint32_t obtenerTablaDePagina(pcb *);
void enviarProcesosAReady();
void terminarProcesos();
#endif /* SRC_PLANIFICADORES_H_ */
#ifndef SRC_MEMORIA_H_
#define SRC_MEMORIA_H_
#include "../../shared/include/sockets.h"
#include "utils.h"
#include <math.h>
#include <stdint.h>
#include <commons/config.h>
#include <sys/mman.h>
#include <commons/log.h>
#include <commons/collections/list.h>

uint32_t id_tabla_primer_nivel;
uint32_t id_tabla_segundo_nivel;
uint32_t tamanioBitmap;


//INICIALIZAR MEMORIA COMO SERVIDOR DE KERNEL Y CPU
memoria_init_server(){

}

void crear_memoria_principal(){

    
    uint32_t cantidad_de_marcos = valores_generales_memoria->tamMemoria / valores_generales_memoria->tamPagina;

    if(valores_generales_memoria->tamMemoria % valores_generales_memoria->tamPagina != 0){
        cantidad_de_marcos ++;
    }

    tamanioBitmap = cantidad_de_marcos;

    *memoria_principal = malloc(sizeof(uint8_t) * valores_generales_memoria->tamMemoria);
    memoria_principal[valores_generales_memoria->tamMemoria];
    puntero_a_bits = malloc(cantidad_de_marcos);
    bitmap_memoria = bitarray_create_with_mode(puntero_a_bits,cantidad_de_marcos, LSB_FIRST);
    msync(bitmap_memoria->bitarray, cantidad_de_marcos, MS_SYNC);

    for(int i=0; i<cantidad_de_marcos; i++){
        bitarray_clean_bit(bitmap_memoria, i);
    }

    printf("\nMemoria Principal Creada\n");

}

















#endif /* SRC_MEMORIA_H_ */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SIM_H
#define __SIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "core.h"


/***
 *  Inicia el modulo sim. Hardware UART y pines para conmutar la alimentacion.
*/
void sim_init();


/**
 * Deshabilito el modulo sim. Sin apargar UART, solo envio comando para apagar sim 
 * y deshabilito alimentacion
*/
void sim_deinit();


/**
 * Envio un comando al modulo sim, checkeou respuesta. Si respuesta es correcta 1, sino 0.
 * @param string_cmd: Comando a enviar
 * @param response_expected: Respuesta esperada
 * @param timeout: Tiempo de espera maximo (utilizado en las funciones uart)
*/
uint8_t sim_send_command(uint8_t* string_cmd,uint8_t* response_expected,uint32_t timeout, uint8_t print_flag);




 /**
  * Obtengo la version del firmware del Sim
  * 
 */
 void sim_version();
 
 
 /**
  * Deshabilito el eco del sim 
  * 
 */
 void sim_echo_off();
 
 
 /**
  * Conecto con la red 4G 
  * 
 */
 void sim_4g_connect();
 
 
 /**
  *  Conecto con el servidor mqtt
  * 
 */
 void sim_mqtt_connect();
 
 
 /**
  * Mando el sim a dormir 
  * 
 */
 void sim_sleep();
 
 
 /**
  * Despierto el micro del modo sleep.
  * 
 */
 void sim_resumen();




  /**
   * Enciende el GPS del sim. 
   * Obtener datos GPS puede llevar entre 30s y 1 minuto 
   * 
  */
  void sim_gps_on();


 /**
  * Apago el GPS 
  * 
 */
 void sim_gps_off();



/***
 *  Obtener datos de gps. Se debe encender el gps y esperan entre 30 s y 1 minuto
*/
 void sim_gps_get_info(uint8_t* gps_buffer,size_t len);


/***
 * Obtengo el buffer donde se almacena la trama GPS
*/
 uint8_t*   sim_get_gps_data();



/**
 *  Publico un mensaje por MQTT
 * @param topic: Topic o canal donde se envia el mensaje
 * @param payload:Buffer de datos para publicar 
 * @param len_payload: tamanio del buffer da datos enviado
*/
void sim7000g_mqtt_publish(uint8_t* topic, uint8_t* payload, uint8_t len_payload);


/**
 *  Subcripcion a un topico MQTT
 * @param topic: Topico
*/
void sim7000g_mqtt_subscription(uint8_t* topic);



/**
 *  Dessubcripcion a un topico MQTT
 * @param topic: Topico
*/
void sim7000g_mqtt_unsubscription(uint8_t* topic);





#ifdef __cplusplus
}
#endif

#endif /* __SIM_H */


#include "core.h"

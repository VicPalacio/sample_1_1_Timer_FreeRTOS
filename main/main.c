/* File:   sample_1_1_Timer_FreeRTOS
 *
 * Author: Victor Adolfo Palacio Bastidas
 *
 * Este proyecto es creado
 *
 * Created on 22 de Agosto de 2026
 */

#include <stdio.h>
#include "driver/gpio.h" // Encontrado en: C:\ESP32_ESPRESSIF\v5.2.1\esp-idf\components\driver\gpio\include\driver
#include "freertos/FreeRTOS.h" //Encontrado en: C:\ESP32_ESPRESSIF\v5.2.1\esp-idf\components\freertos\FreeRTOS-Kernel\include\freertos
#include "freertos/task.h" // Encontrado en:   // C:\ESP32_ESPRESSIF\v5.2.1\esp-idf\components\freertos\FreeRTOS-Kernel\include\freertos
#include "esp_log.h" // Encontrado en: C:\ESP32_ESPRESSIF\v5.2.1\esp-idf\components\log\include\esp_log.h
#include "freertos/timers.h" //Encontrado en: // C:\ESP32_ESPRESSIF\v5.2.1\esp-idf\components\freertos\FreeRTOS-Kernel\include\freertos
#define led_2 5

uint8_t led_level = 0, cuenta_blink_Led_2 = 0;
uint8_t cuenta_app_main = 0;
static const char *tag = "Main"; // Main es el módulo donde se está usando la librería
TimerHandle_t xTimers;           // Este tipo de variable existe dentro del timers.h
int interval = 1000;             // Intervalo de tiempo para el timer, o el evento
int timerId = 1;                 // Identificador del timer

/*Funciones creadas*/
esp_err_t init_led(void);
esp_err_t blink_led(void);
esp_err_t set_timer(void);

/* vTimerCallback
* timers.h: línea 161: Each timer calls the same callback when it expires.
Define una función de devolución de llamada que será utilizada por varias
instancias del temporizador.
La función de devolución de llamada no hace nada más que contar la cantidad de
veces que el temporizador asociado expira y lo detiene una vez que ha expirado
10 veces, este control solo aplica cuando se usa la variable
xMaxExpiryCountBeforeStopping, en esta aplicación NO se está usando
*/
void vTimerCallback(TimerHandle_t pxTimer) {
    ESP_LOGI(tag, "Event was called from timer");
    blink_led();
}
/* app_main
 *Configura los pin(es) a usar
 *Configura el timer*/
void app_main(void) {
    init_led();
    set_timer();
}
/* init_led
Resetea, define el pin a usar y el modo de uso del pin
(entrada o salida) */
esp_err_t init_led(void) {
    gpio_reset_pin(led_2);
    gpio_set_direction(led_2, GPIO_MODE_OUTPUT);
    return ESP_OK;
}
/* blink_led
/// @brief Hace un toggle al pin pasado parámetro
/// @param Recibe un número de pin
/// @return ok
*/
esp_err_t blink_led(void) {
    led_level = !led_level;
    gpio_set_level(led_2, led_level);
    cuenta_blink_Led_2++;
    ESP_LOGI(tag, "Cuenta Blink LED azul: %u", cuenta_blink_Led_2);
    return ESP_OK;
}
/* set_timer
/// @brief Configura el timer así:
* Función xTimerCreate crea y configura el timer
* "Timer": es el nombre, no es usado por el Kernel
* (pdMS_TO_TICKS(interval)): función que pasa de ms a ticks para definir
el PERIODO de duración del timer.
* vTimerCallback: función definida en la librería "timers.h"
* pdTRUE: Este parámetro afirma que se debe recargar el timer
/// @param No recibe nada
/// @return ok
*/
esp_err_t set_timer(void) {
    ESP_LOGW(tag, "Timer init configuration");
    xTimers =
        xTimerCreate("Timer",                   // Solo es un nombre, no es usado por el kernel.
                     (pdMS_TO_TICKS(interval)), // Conversión de ms a Ticks.
                     // pdFALSE,
                     // El parámetro pdFALSE hace que solo se ejecute una vez y se validó operación
                     pdTRUE,
                     // El timer se autorrecargará cuando expire. linea nueva 10082024
                     (void *)timerId, // Asigna un único ID para igual para indice del array
                     vTimerCallback); // Cada timer llama la misma función callback cuando termina
    // Aquí sería muy interesante saber que valor recibe xTimers
    if (xTimers == NULL) {
        ESP_LOGE(tag, "The timer was not created.");
    } else {
        if (xTimerStart(xTimers, 0) != pdPASS) {
            ESP_LOGE(tag, "The timer could not be set into the active state");
        }
    }
    return ESP_OK;
}
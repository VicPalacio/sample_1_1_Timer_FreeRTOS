/* File:   sample_1_1_Timer_FreeRTOS
 *
 * Author: Victor Adolfo Palacio Bastidas
 *
 * Este proyecto es creado
 *
 * Created on 22 de Agosto de 2026
 */

#include <stdio.h> // /home/victor/.espressif/v6.1/esp-idf/components/esp_libc/platform_include
#include "driver/gpio.h" // En: /home/victor/.espressif/v6.1/esp-idf/components/esp_driver_gpio/include/driver
#include "freertos/FreeRTOS.h" //En: /home/victor/.espressif/v6.1/esp-idf/components/freertos/FreeRTOS-Kernel/include/freertos
#include "freertos/task.h" //En: /home/victor/.espressif/v6.1/esp-idf/components/freertos/FreeRTOS-Kernel/include/freertos
#include "freertos/timers.h" //En: /home/victor/.espressif/v6.1/esp-idf/components/freertos/FreeRTOS-Kernel/include/freertos
#include "esp_log.h" // En: /home/victor/.espressif/v6.1/esp-idf/components/log/include
#define led_rojo 5

uint8_t led_level = 0, cuenta_blink_led_rojo = 0;
static const char *tag = "Main";           // Main es el módulo donde se está usando la librería
TimerHandle_t xTimers;                     // Este tipo de variable existe dentro del timers.h
int periodo_intervalo_de_tiempo_ms = 1000; // Periodo_de_tiempo para el timer, o evento
int timerId = 1;                           // Identificador del timer

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
    ESP_LOGW(tag, "Event was called from timer");
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
    gpio_reset_pin(led_rojo);
    gpio_set_direction(led_rojo, GPIO_MODE_OUTPUT);
    return ESP_OK;
}
/* blink_led
/// @brief Hace un toggle al pin pasado parámetro
/// @param Recibe un número de pin
/// @return ok
*/
esp_err_t blink_led(void) {
    led_level = !led_level;
    gpio_set_level(led_rojo, led_level);
    cuenta_blink_led_rojo++;
    ESP_LOGI(tag, "Cuenta Blink LED Rojo: %u", cuenta_blink_led_rojo);
    return ESP_OK;
}
/* set_timer
/// @brief Configura el timer así:
* Función xTimerCreate crea y configura el timer
* "Timer": es el nombre, no es usado por el Kernel
* (pdMS_TO_TICKS(periodo_intervalo_de_tiempo_ms)): función que pasa de ms a ticks para definir
el PERIODO de duración del timer.
* vTimerCallback: función definida en la librería "timers.h"
* pdTRUE: Este parámetro afirma que se debe recargar el timer
/// @param No recibe nada
/// @return ok
*/
esp_err_t set_timer(void) {
    ESP_LOGW(tag, "Timer init configuration");
    xTimers =
        xTimerCreate("Timer", // Solo es un nombre, no es usado por el kernel.
                     (pdMS_TO_TICKS(periodo_intervalo_de_tiempo_ms)), // Conversión de ms a Ticks.
                     // pdFALSE,
                     // El parámetro pdFALSE hace que solo se ejecute una vez y se validó operación
                     pdTRUE,
                     // El timer se autorrecargará cuando expire. linea nueva 10082024
                     (void *)timerId, // Asigna un único ID para igual para indice del array
                     vTimerCallback); // Cada timer llama la misma función callback cuando termina
    if (xTimers == NULL) {
        ESP_LOGE(tag, "The timer was not created.");
    } else {
        if (xTimerStart(xTimers, 0) != pdPASS) {
            ESP_LOGE(tag, "The timer could not be set into the active state");
        }
    }
    return ESP_OK;
}
/* File:   sample_1_1_Timer_FreeRTOS
 *
 * Author: Victor Adolfo Palacio Bastidas
 *
 * Este proyecto es creado para ilustrar el uso de timers en su forma más básica, hace un toggle
 * sobre un pin y representa una cuenta a traves de una salida por consola, usando para esto la
 * librería incluida en ESP-IDF, la librería es esp_log.h
 * Created on 22 de Agosto de 2026  
*/

#include <stdio.h> // /home/victor/.espressif/v6.1/esp-idf/components/esp_libc/platform_include
#include "freertos/FreeRTOS.h" //En: /home/victor/.espressif/v6.1/esp-idf/components/freertos/FreeRTOS-Kernel/include/freertos
#include "freertos/task.h" //En: /home/victor/.espressif/v6.1/esp-idf/components/freertos/FreeRTOS-Kernel/include/freertos
#include "freertos/timers.h" //En: /home/victor/.espressif/v6.1/esp-idf/components/freertos/FreeRTOS-Kernel/include/freertos
#include "esp_log.h" // En: /home/victor/.espressif/v6.1/esp-idf/components/log/include
#include "led.h"

static const char *tag = "Main";           // Main es el módulo donde se está usando la librería
TimerHandle_t xTimers;                     // Este tipo de variable existe dentro del timers.h
int periodo_intervalo_de_tiempo_ms = 1000; // Periodo_de_tiempo para el timer, o evento
int timerId = 1;                           // Identificador del timer

esp_err_t set_timer(void);

/**
 * @brief vTimerCallback en timers.h: línea 161: Each timer calls the same
 * callback when it expires.
 * Define una función de devolución de llamada que será utilizada por varias
 * instancias del temporizador.
 * La función de devolución de llamada no hace nada más que contar la cantidad de
 * veces que el temporizador asociado expira y lo detiene una vez que ha expirado
 * 10 veces, este control solo aplica cuando se usa la variable
 * xMaxExpiryCountBeforeStopping, en esta aplicación NO se está usando
 */
void vTimerCallback(TimerHandle_t pxTimer) {
    ESP_LOGW(tag, "Event was called from timer");
    blink_led();
}
/**
 * @brief app_main
 * Configura los pin(es) a usar
 * Configura el timer
 */
void app_main(void) {
    init_led();
    set_timer();
}

esp_err_t init_led(void);
esp_err_t blink_led(void);

/**
 * @brief set_timer() Configura el timer así:
 * Función xTimerCreate crea y configura el timer
 * "Timer": es el nombre, no es usado por el Kernel
 * (pdMS_TO_TICKS(periodo_intervalo_de_tiempo_ms)): función que pasa de ms a ticks para definir
 * el PERIODO de duración del timer.
 * vTimerCallback: función definida en la librería "timers.h"
 * pdTRUE: Este parámetro afirma que se debe recargar el timer
 * @return ok
 */
esp_err_t set_timer(void) {
    ESP_LOGW(tag, "Timer init configuration");
    xTimers =
        xTimerCreate("Timer", // Solo es un nombre, no es usado por el kernel.
                     (pdMS_TO_TICKS(periodo_intervalo_de_tiempo_ms)), // Conversión de ms a Ticks.
                     // pdFALSE,
                     // El parámetro pdFALSE hace que solo se ejecute una vez y se validó operación
                     pdTRUE,          // pdTRUE, El timer se autorrecargará cuando expire.
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
# Timers !!

+ Este proyecto fue construido con: 
    + S.O: Ubuntu 26.04.1 LTS 
    + Visual Studio Code: 1.141.0
    + ESP-IDF: V6.1.0

+ En este ejemplo se crea un timer que pretende demostrar el uso he implementacion del timer


## Para mas información consultar la documentación oficial:

 [ESP32 Getting Started Guide TIMERS](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos_idf.html?highlight=xtimercreate#_CPPv412xTimerCreatePCKcK10TickType_tK10BaseType_tPCv23TimerCallbackFunction_t)


## Funciones

#### xTimerCreateStatic(): 

* El escritor del código tendrá que proporcionar la cantidad de memoria requerida por la aplicación.

#### xTimerCreate():
 
* Hace un uso dinámico de la memoria requerida esto implica que el escritor del código no tendrá que especificar la memoria que se requiera.

+ Esta es la función que se usa en este código de aplicación.
    + En la función timers.c está contenida esta función 
                TimerHandle_t xTimerCreate( const char * const pcTimerName,
                                    const TickType_t xTimerPeriodInTicks,
                                    const BaseType_t xAutoReload,
                                    void * const pvTimerID,
                                    TimerCallbackFunction_t pxCallbackFunction )
                
    #### pcTimerName: 
    Es solo para facilitar la depuración, el Kernel solo referencia al timper por el handle 
    ##### xTimerPeriodInTickc: 
    Es el periodo del timer. El periodo siempre tiene que ser mayor que 0, se pueden usar funciones como pdMS_TO_TICKS(interval) para convertir ticks a milisegundos.   
    #### xAutoReload:
    Si este parámetro se configura con pdTRUE entonces el timer expirará con una frecuencia configurada por el parámetro xTimerPeriodInTickc si se configura con un parámetro como pdFALSE entonces el timer solo se ejecutará una vez.
    #### pvTimerID:
    Es un identificador para saber cual timer ha expirado cuando se usan varios timers, cuando estos llaman la misma función callback al expirar.
    #### pxCallbackFunction:  
    Se llama esta función cuando el timer expira. Esta función tiene que tener el prototipo definido por TimerCallbackFunction_t 

### Otras funciones usadas en el código:
 
 #### pdMS_TO_TICKS(xTimeInMs)
 Conversión de milisegundos a ticks, la variable xTimeInMs puede ser por ejemplo una variable tipo entero (int) también existe otra función que hace la operación inversa, la función es: pdTICKS_TO_MS( xTicks ) en el archivo projdefs.h 
    

+ Cuando se crea un timer se crea en estado inactivo y es necesaria otra función para activarlas, dichas funciones son:

    + xTimerStart(), 
    + xTimerReset(), 
    + xTimerStartFromISR(), 
    + xTimerResetFromISR(),  
    + xTimerChangePeriod(), 
    + xTimerChangePeriodFromISR()
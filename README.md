# Timers !!

En este ejemplo se crea un timer que pretende demostrar el uso he implementacion del timer


## Para mas información consultar la documentación oficial:

 [ESP32 Getting Started Guide TIMERS](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos_idf.html?highlight=xtimercreate#_CPPv412xTimerCreatePCKcK10TickType_tK10BaseType_tPCv23TimerCallbackFunction_t)


## Funciones

#### xTimerCreateStatic(): 

* El escritor del código tendrá que proporcionar la cantidad de memoria requerida por la aplicación.

#### xTimerCreate():
 
* Hace un uso dinámico de la memoria requerida esto implica que el escritor del código no tendrá que especificar la memoria que se requiera.

+ Cuando se crea un timer se crea en estado inactivo y es necesaria otra función para activarlas, dichas funciones son:

    + xTimerStart(), 
    + xTimerReset(), 
    + xTimerStartFromISR(), 
    + xTimerResetFromISR(),  
    + xTimerChangePeriod(), 
    + xTimerChangePeriodFromISR()
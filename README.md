## Código de Ejemplo (main)
Para ejecutar el main primero debemos compilar (en la carpeta raíz)
````
gcc tdas/*.c main.c -Wno-unused-result -o main
````

Y luego ejecutar:
````
./main
````

## TDAs
En la carpeta `tdas` se encuentran implementados distintos TDAs que puedes utilizar (lista, pila, cola, cola con prioridad y mapas). 

Las implementaciones no son las más eficientes (todas usan como estructura de datos una **lista enlazada**), por lo que puedes reemplazarlas por las que has realizado en los labs.

## FUNCIONES
Para la realizacion del codigo, se crean diferentes funciones que ayudan a la creacion del proyecto. Existen diversas y estas son:

**registrar_paciente** : Funcion que cumple la funcion de añadir un paciente a nuestra lista.

**registrar_prioridad** : Funcion que cambia la prioridad de un paciente (ya que se inicializa en 1).

**buscar_paciente** : Funcion que busca a un paciente en especifico comparando el nombre.

**compararPrioridad** : Funcion que compara la prioridad del paciente que se le cambia la prioridad para poder ordernarlo en la lista.

**mostrar_lista_pacientes** : Funcion que muestra por orden de prioridad y llegada a todos los pacientes registrados.

**atender_paciente** : Funcion que muestra los datos del paciente atendido y luego lo elimina de la lista.

**mostrar_lista_prioridad** : Funcion que muestra a los pacientes de una prioridad en especifico.

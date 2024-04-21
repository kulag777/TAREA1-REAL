#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char nombre[50];
  int edad;
  char sintoma[100];
  int prioridad;
  int id;   // numero de orden de llegada
} paciente; // definir el struct de un paciente

// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}

void registrar_paciente(List *lista, size_t contador) {

  paciente *nuevo = (paciente *)malloc(sizeof(paciente));
  if (nuevo == NULL)
    return;

  limpiarPantalla();
  printf("Ingrese el nombre del paciente: ");
  scanf(" %[^\n]", nuevo->nombre);

  limpiarPantalla();
  printf("Ingrese la edad del paciente: ");
  scanf("%d", &nuevo->edad);

  limpiarPantalla();
  printf("Ingrese el/los sintoma(s) del paciente: ");
  scanf(" %[^\n]", nuevo->sintoma);
  nuevo->prioridad = 1;
  nuevo->id = contador++; // se registra el numero de orden de llegada y se le
                          // suma 1 al contador
  list_pushBack(lista, nuevo); // se agrega el paciente a la lista al final
}
void mostrar_lista_pacientes(List *lista) {
  limpiarPantalla();
  paciente *pacienteActual = list_first(lista);
  if (pacienteActual == NULL) {
    printf("No hay pacientes en la lista.\n");
    return;
  }
  puts("========================================");
  puts("NOMBRE - EDAD - SINTOMAS");
  puts("========================================");
  while (pacienteActual != NULL) { // se utiliza un while para recorrer la lista
    printf("  %s  -  %d  -  %s  \n", pacienteActual->nombre,
           pacienteActual->edad, pacienteActual->sintoma);
    pacienteActual = list_next(lista);
  }
  puts("========================================");
}
int comparar_prioridad(void *data1, void *data2) {
  paciente *ptr1 = (paciente *)data1;
  paciente *ptr2 = (paciente *)data2;
  if (ptr1->prioridad > ptr2->prioridad) { // se comparan prioridades, si la
                                           // primera es mayor se retorna 1
    return 1;
  } else if (ptr1->prioridad <
             ptr2->prioridad) { // si la primera es menor se retorna -1
    return 0;
  } else {
    // Si las prioridades son iguales, comparar por ID
    if (ptr1->id < ptr2->id) {
      return 1;
    } else {
      return 0;
    }
  }
}

void buscar_paciente(List *lista, char *nombre) {
  limpiarPantalla();
  int contador = 0;
  paciente *pacienteActual = list_first(lista);
  while (pacienteActual != NULL) { // se utiliza un while para recorrer la lista
    if (strcmp(pacienteActual->nombre, nombre) ==
        0) { // si el nombre del paciente es igual al nombre ingresado
      contador++;
      printf("Ingrese la prioridad del paciente (1-3): ");
      scanf("%d", &pacienteActual->prioridad);
      list_popCurrent(lista);
      list_sortedInsert(lista, pacienteActual, comparar_prioridad);
      break;
    }
    pacienteActual = list_next(lista);
  }
  if (contador == 0) { // si no hay ningun paciente con ese nombre
    puts("Paciente no encontrado");
  }
}

void registrar_prioridad(List *lista) {
  limpiarPantalla();
  printf("Ingrese el nombre del paciente: ");
  char nombre[50];
  scanf(" %[^\n]", nombre);
  buscar_paciente(lista, nombre); // funcion que sirve para buscar el paciente y
                                  // registrar su prioridad
}

void atender_paciente(List *lista) {
  limpiarPantalla();
  if (list_first(lista) == NULL) {
    puts("No hay pacientes en la lista");
  } else {
    paciente *paciente = list_popFront(lista);
    printf("Nombre: %s\n", paciente->nombre);
    printf("Años: %d\n", paciente->prioridad);
    printf("Sintomas: %s\n", paciente->sintoma);
    free(paciente);
  }
}
void mostrar_lista_prioridad(List *lista) {
  limpiarPantalla(); // para una visualizacion mas clara
  int contador = 0;
  int prioridadVer;
  printf("Ingrese la prioridad a mostrar (1-3): ");
  scanf("%d", &prioridadVer);
  limpiarPantalla();

  puts("========================================");
  puts("NOMBRE - EDAD - SINTOMAS");
  puts("========================================");
  paciente *pacienteActual = list_first(lista);

  while (pacienteActual != NULL) { // while que recorre la lista
    if (pacienteActual->prioridad ==
        prioridadVer) { // si tiene la misma prioridad
                        // que se quiere ver, se printea
      contador++;
      printf("  %s  -  %d  -  %s  \n", pacienteActual->nombre,
             pacienteActual->edad, pacienteActual->sintoma);
    }
    pacienteActual = list_next(lista);
  }
  puts("========================================");
  if (contador ==
      0) { // si no hay pacientes con la prioridad, se imprime que no hay
    limpiarPantalla();
    puts("No hay pacientes con esa prioridad");
  }
}
int main() {
  char opcion;
  size_t contador = 0; // contador para poder registrar el numero de pacientes
                       // por orden de llegada
  List *pacientes =
      list_create(); // puedes usar una lista para gestionar los pacientes

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_paciente(pacientes,
                         contador); // funcion que sirve para añadir pacientes
      break;
    case '2':
      registrar_prioridad(
          pacientes); // funcoin que sirve para añadir prioridad a un paciente
      break;
    case '3':
      mostrar_lista_pacientes(
          pacientes); // funcion que sirve para mostrar la lista de pacientes
      break;
    case '4':
      atender_paciente(
          pacientes); // funcion que sirve para atender al siguiente paciente
      break;
    case '5':
      mostrar_lista_prioridad(pacientes); // funcion que sirve para mostrar la
                                          // lista de pacientes por prioridad
      break;
    case '6':
      limpiarPantalla();
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(pacientes);

  return 0;
}

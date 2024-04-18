#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char nombre[50];
  int edad;
  char sintoma[100];
  int prioridad;

} paciente;

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

void registrar_paciente(List *lista) {

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

  list_pushBack(lista, nuevo);
}

void mostrar_lista_pacientes(List *lista) {
  limpiarPantalla();
  puts("========================================");
  puts("NOMBRE - EDAD - SINTOMAS");
  puts("========================================");
  for (paciente *paciente = list_first(lista); paciente != NULL;
       paciente = list_next(lista)) {
    printf("Nombre: %s, Edad: %d, Prioridad: %d \n", paciente->nombre,
           paciente->edad, paciente->prioridad);
  }
  puts("========================================");
}
/*
void ordenar_prioridad(List *lista) {
  paciente *aux = (paciente *)malloc(sizeof(Node));
  if (aux == NULL) {
    return;
  }
  aux = lista->current;
  list_popCurrent(lista);
  list_pushCurrent(lista, aux);
}

void buscar_paciente(List *lista, char *nombre) {
  limpiarPantalla();
  lista->current = lista->head;

  while (lista->current != NULL) {
    if (strcmp(lista->current->nombre, nombre) == 0) {
      printf("Ingrese la prioridad del paciente (1-3): ");
      scanf("%d", &lista->current->prioridad);
      ordenar_prioridad(lista);
      break;
    }
    lista->current = lista->current->next;
  }
  puts("Paciente no encontrado");
}

void registrar_prioridad(List *lista) {
  limpiarPantalla();
  printf("Ingrese el nombre del paciente: ");
  char nombre[50];
  scanf(" %[^\n]", nombre);
  buscar_paciente(lista, nombre);
} */
int main() {
  char opcion;
  List *pacientes = list_create(); // puedes usar una lista para gestionar los pacientes

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_paciente(pacientes);
      break;
    case '2':
      registrar_prioridad(pacientes); // Lógica para asignar prioridad
      break;
    case '3':
      mostrar_lista_pacientes(pacientes);
      break;
    case '4':
      // Lógica para atender al siguiente paciente
      break;
    case '5':
      // Lógica para mostrar pacientes por prioridad
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

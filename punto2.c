#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea
{
    int TareaID; // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
} typedef Tarea;

void iniciarEnNull(Tarea **TPendientes, int cantidad);
void CargarTarea(Tarea **TPendientes, int cantidad, char *buff);
void checkTareas(Tarea **TPendientes, int cantidad, Tarea **TRealizadas);
void listarTareas(Tarea **Tareas, int cantidad);
Tarea *BuscaTareaPorPalabra(Tarea **TPendientes, int cantidad, Tarea **TRealizadas, char *palabra);
void listarTareas(Tarea **Tareas, int cantidad);
Tarea *BuscaTareaPorId(Tarea **TPendientes, int cantidad, Tarea **TRealizadas, int id);
void mostrarBusqueda(Tarea *tarea);
void liberarMemoria(Tarea **Tarea, int cantidad);

int main(void)
{
    int cantTareas, duracion, id;
    Tarea **tareasPendientes;
    Tarea **tareasRealizadas;
    Tarea *busqueda;
    int opcion;
    char *buff = (char *)malloc(sizeof(char) * 100);
    printf("ingrese la cantidad de tareas a relizar\n");
    scanf("%d", &cantTareas);

    //reservo memoria
    tareasPendientes = (Tarea **)malloc(sizeof(Tarea *) * cantTareas); // esto no es una matriz (creo) 
                                                                       //porque en cada pocicion los puntero, de este arre de punteros
                                                                       //van a apuntar a una sola variable estructurada
                                                                       //entonces seria un vector de una sola dimension 
    iniciarEnNull(tareasPendientes, cantTareas);
    tareasRealizadas = (Tarea **)malloc(sizeof(Tarea *) * cantTareas);
    iniciarEnNull(tareasRealizadas, cantTareas);

    //carfo tareas
    CargarTarea(tareasPendientes, cantTareas, buff);

    do
    {
        puts("\t\t\t(1)- controlar tareas");
        puts("\t\t\t(2)- listar tareas");
        puts("\t\t\t(3)- Buscar Tareas por Id");
        puts("\t\t\t(4)- Buscar Tareas por palabra clave");
        puts("\t\t\t(5)- salir");
        fflush(stdin);
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            checkTareas(tareasPendientes, cantTareas, tareasRealizadas);
            break;
        case 2:
            puts("\tTareas Realizadas");
            listarTareas(tareasRealizadas, cantTareas);
            puts("\tTareas Pendientes");
            listarTareas(tareasPendientes, cantTareas);
            break;
        case 3:
            puts("\n\tBusqueda por id\n");
            fflush(stdin);
            scanf("%d", &id);
            busqueda = BuscaTareaPorId(tareasPendientes, cantTareas, tareasRealizadas, id);
            mostrarBusqueda(busqueda);
            break;
        case 4:
            puts("\n\tbusqueda por palabra clave");
            fflush(stdin);
            gets(buff);
            busqueda = BuscaTareaPorPalabra(tareasPendientes, cantTareas, tareasRealizadas, buff);
            mostrarBusqueda(busqueda);
            break;
        }

    } while (opcion != 5);
    liberarMemoria(tareasPendientes,cantTareas); // en el primer parametro estoy pasando la direccion de memoria
                                                //de la primera componente del arreglo de puntero, entonces como es un vector
                                                //de una dimencion la direccion de la par será la otra posicion del arre
                                                //entonces me va a permitir recorrelo desde la funcion
    liberarMemoria(tareasRealizadas, cantTareas);
    liberarMemoria(tareasRealizadas,cantTareas);
    free(tareasPendientes); //acá libero los punteros "no lo que contienen los puntero" eso lo hago en la linea anterior
    free(tareasRealizadas);
    free(buff);
    return 0;
}

void iniciarEnNull(Tarea **TPendientes, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        TPendientes[i] = NULL; // estoy accediendo al contenido del puntero o sea lo estoy haciendo apuntar a null
                               // es lo mismo que *TPendientes=NULL;
    }
}

void CargarTarea(Tarea **TPendientes, int cantidad, char *buff)
{
    for (int i = 0; i < cantidad; i++)
    {
        TPendientes[i] = (Tarea *)malloc(sizeof(Tarea));
        printf("ingrese la descripcion de la tarea N %d\n", i + 1);
        fflush(stdin);
        gets(buff);
        TPendientes[i]->Descripcion = (char *)malloc((strlen(buff) + 1) * sizeof(char));
        strcpy(TPendientes[i]->Descripcion, buff);
        TPendientes[i]->Duracion = rand() % (100 - 10) + 1;
        TPendientes[i]->TareaID = i;
    }
}
void checkTareas(Tarea **TPendientes, int cantidad, Tarea **TRealizadas)
{

    puts("\n\n\tchequeo de tareas\n");
    char yes_not;
    int j = 0;
    for (int i = 0; i < cantidad; i++)
    {
        printf("Tarea Id= %d\n", TPendientes[i]->TareaID);
        printf("Decripcion: %s\n", TPendientes[i]->Descripcion);
        printf("Duracion: %d min\n", TPendientes[i]->Duracion);
        printf("Realizo esta tarea (s o n)\n");
        fflush(stdin);
        scanf("%c", &yes_not);
        if (yes_not == 's')
        {
            TRealizadas[j] = TPendientes[i];
            TPendientes[i] = NULL;
            j++;
        }
        printf("\n\n");
    }
    puts("===============================");
}
void listarTareas(Tarea **Tareas, int cantidad)
{
    puts("===============================");
    for (int i = 0; i < cantidad; i++)
    {
        if (Tareas[i] != NULL)
        {
            printf("Tarea Id= %d\n", Tareas[i]->TareaID);
            printf("Decripcion: %s\n", Tareas[i]->Descripcion);
            printf("Duracion: %d min\n", Tareas[i]->Duracion);
        }
    }
    puts("===============================");
}
Tarea *BuscaTareaPorPalabra(Tarea **TPendientes, int cantidad, Tarea **TRealizadas, char *palabra)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (TPendientes[i] != NULL && strstr(TPendientes[i]->Descripcion, palabra) != NULL)
        {
            return (TPendientes[i]);
        }
        if (TRealizadas[i] != NULL && strstr(TRealizadas[i]->Descripcion, palabra))
        {
            return (TRealizadas[i]);
        }
    }
    return NULL;
}

Tarea *BuscaTareaPorId(Tarea **TPendientes, int cantidad, Tarea **TRealizadas, int id)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (TPendientes[i] != NULL && TPendientes[i]->TareaID == id)
        {
            return (TPendientes[i]);
        }
        if (TRealizadas[i] != NULL && TRealizadas[i]->TareaID == id)
        {
            return (TRealizadas[i]);
        }
    }
    return NULL;
}
void mostrarBusqueda(Tarea *tarea)
{
    if (tarea != NULL)
    {
        printf("\tTAREA ENCONTRADA\n");
        printf("id buscado: %d\n", tarea->TareaID);
        printf("descripcion: %s\n", tarea->Descripcion);
        printf("duracion: %d min\n", tarea->Duracion);
    }
    else
    {
        printf("No hay concidencias con el Id o palabra ingresado/a\n");
    }
}
void liberarMemoria(Tarea **Tarea, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (Tarea[i]!= NULL)
        {
            free(Tarea[i]->Descripcion); // estoy accediendo a los campos de una direccion de memoria de una variable estructurada 
                                         //a traves del puntero ubicado en una i posicion del arreglo y que apunta a dicha variabale estructurada.
            free(Tarea[i]); // estoy accediendo a la direccion de memoria a la que apunta un puntero de una posicion i
                            //  del arreglo, entoces la fn free efectivamente esta recibiendo una dir de memoria.
        }
        
    }
    
}
//una vez que tengo la direccion de memoria de una var del tipo struc ya puedo usar flecha para acceder a los datos
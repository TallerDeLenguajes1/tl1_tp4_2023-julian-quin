#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int iteracion = 0;
struct Tarea
{
    int TareaID;       // Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} typedef Tarea;

typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

Nodo *inicilizarLista();
Nodo *CrearNodoTarea(char *buff);
void controlarTareas(Nodo **tareasPendientes, Nodo **tareasRealizadas);
void agregarTareaAlinicio(Nodo **tarea, char *buff);
void listarTareas(Nodo *tareas);
void AgregarTareaRealizada(Nodo **tareasRealizadas, Nodo *tarea);
Nodo *BuscaTareaPorPalabra(Nodo *tareasPendientes, Nodo *tareasRealizadas, char *buff);
Nodo *BuscaTareaPorId(Nodo *tareasPendientes, Nodo *tareasRealizadas);
void mostraTareaUnica(Nodo *tarea);
void liberMemoria(Nodo *tarea);

int main(void)
{
    char *buff = (char *)malloc(sizeof(char) * 100);
    int opcion;
    Nodo *tareasPendientes = inicilizarLista();
    Nodo *tareasRealizadas = inicilizarLista();
    Nodo *busquedaID;
    Nodo *busquedaWord;
    do
    {
        puts("\n\n\t\t\t(1)- Agreagar una nueva tarea");
        puts("\t\t\t(2)- controlar tareas");
        puts("\t\t\t(3)- listar tareas");
        puts("\t\t\t(4)- Buscar Tareas por Id");
        puts("\t\t\t(5)- Buscar Tareas por palabra clave");
        puts("\t\t\t(6)- salir");
        fflush(stdin);
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            do
            {
                agregarTareaAlinicio(&tareasPendientes, buff);
                puts("Desea agregar otra persona (ok=1 o 0=No)");
                fflush(stdin);
                scanf("%d", &opcion);

            } while (opcion == 1);

            break;
        case 2:
            controlarTareas(&tareasPendientes, &tareasRealizadas);
            break;
        case 3:
            puts("\tTAREAS PENDIENTES\n");
            listarTareas(tareasPendientes);
            puts("\n\n\tTAREAS REALIZADAS\n\n");
            listarTareas(tareasRealizadas);
            break;
        case 4:
            busquedaID = BuscaTareaPorId(tareasPendientes, tareasRealizadas);
            mostraTareaUnica(busquedaID);

            break;
        case 5:

            busquedaWord = BuscaTareaPorPalabra(tareasPendientes, tareasRealizadas, buff);
            mostraTareaUnica(busquedaWord);
            break;
        }

    } while (opcion != 6);
    liberMemoria(tareasPendientes);
    liberMemoria(tareasRealizadas);
    free(buff);
    return 0;
}

Nodo *inicilizarLista()
{
    return (NULL);
}

Nodo *CrearNodoTarea(char *buff)
{
    puts("AGREGANDO TAREA");
    Nodo *aux;
    aux = (Nodo *)malloc(sizeof(Nodo));
    puts("ingrese la descripcion de la tarea: ");
    fflush(stdin);
    gets(buff);
    aux->T.Descripcion = (char *)malloc((strlen(buff) + 1) * sizeof(char));
    strcpy(aux->T.Descripcion, buff);
    aux->T.Duracion = rand() % (100 - 10) + 10;
    aux->T.TareaID = iteracion;
    aux->Siguiente = NULL;
    iteracion++;
    return aux;
}

void agregarTareaAlinicio(Nodo **tarea, char *buff)
{
    Nodo *nuevatarea;
    nuevatarea = CrearNodoTarea(buff);
    nuevatarea->Siguiente = *tarea;
    *tarea = nuevatarea;
}

void controlarTareas(Nodo **tareasPendientes, Nodo **tareasRealizadas)
{
    Nodo *tareaActual = *tareasPendientes;
    Nodo *tareaAnterior = *tareasPendientes;
    int ID;

    puts("\nCONTEROL DE TAREAS REALIZADAS\t");
    puts("Indique un ID:\n\n");
    listarTareas(*tareasPendientes);
    fflush(stdin);
    scanf("%d", &ID);

    while (tareaActual != NULL && tareaActual->T.TareaID != ID)
    {
        tareaAnterior = tareaActual;
        tareaActual = tareaActual->Siguiente; // actual nunca quedará con el null
    }

    if (*tareasPendientes == tareaActual) // cuando el dato buscado es el primero
    {
        *tareasPendientes = tareaActual->Siguiente;
        AgregarTareaRealizada(tareasRealizadas, tareaActual);
        free(tareaActual);
    }
    else
    {

        if (tareaActual != NULL) // si el dato buscado no es el primero, tambien vale para el ultimo
        {
            tareaAnterior->Siguiente = tareaActual->Siguiente;
            AgregarTareaRealizada(tareasRealizadas, tareaActual);
            free(tareaActual);
        }
    }
}

void listarTareas(Nodo *tareas)
{
    Nodo *auxTareas = tareas;

    while (auxTareas != NULL)
    {
        printf("\nID tarea: %d\n", auxTareas->T.TareaID);
        printf("Descripcion: %s\n", auxTareas->T.Descripcion);
        printf("Duracion: %d min\n", auxTareas->T.Duracion);
        auxTareas = auxTareas->Siguiente;
        puts("===============================");
    }
}
void AgregarTareaRealizada(Nodo **tareasRealizadas, Nodo *tarea)
{
    Nodo *NuevaRealizada = (Nodo *)malloc(sizeof(Nodo)); // si yo le asigno "tarea" lo voy a perder porque despues hago el free()
                                                        //tengo que copiar campo por campo
    NuevaRealizada->T.Descripcion = (char *)malloc((strlen(tarea->T.Descripcion) + 1) * sizeof(char));
    strcpy(NuevaRealizada->T.Descripcion, tarea->T.Descripcion);
    NuevaRealizada->T.Duracion = tarea->T.Duracion;
    NuevaRealizada->T.TareaID = tarea->T.TareaID;
    // aqui modifico las direcciones
    NuevaRealizada->Siguiente = *tareasRealizadas;
    *tareasRealizadas = NuevaRealizada;
}
Nodo *BuscaTareaPorId(Nodo *tareasPendientes, Nodo *tareasRealizadas)
{
    Nodo *auxPendientes = tareasPendientes;
    Nodo *auxRealizadas = tareasRealizadas;
    int id;
    printf("\nIgrese un id: ");
    fflush(stdin);
    scanf("%d", &id);

    while (auxPendientes != NULL)
    {
        if (id == auxPendientes->T.TareaID)
        {
            return (auxPendientes);
        }
        auxPendientes = auxPendientes->Siguiente;
    }

    while (auxRealizadas != NULL)
    {
        if (auxRealizadas->T.TareaID == id)
        {
            return (auxRealizadas);
        }
        auxRealizadas = auxRealizadas->Siguiente;
    }
    return (NULL);
}
Nodo *BuscaTareaPorPalabra(Nodo *tareasPendientes, Nodo *tareasRealizadas, char *buff)
{
    Nodo *auxPendientes = tareasPendientes;
    Nodo *auxRealizadas = tareasRealizadas;
    puts("\ningrese la una palabra clave: ");
    fflush(stdin);
    gets(buff);

    while (auxPendientes != NULL)
    {
        if (strstr(auxPendientes->T.Descripcion, buff) != NULL)
        {
            return (auxPendientes);
        }
        auxPendientes = auxPendientes->Siguiente;
    }

    while (tareasRealizadas != NULL)
    {
        if (strstr(tareasRealizadas->T.Descripcion, buff) != NULL)
        {
            return (tareasRealizadas);
        }
        tareasRealizadas = tareasRealizadas->Siguiente;
    }
    return (NULL);
}

void mostraTareaUnica(Nodo *tarea)
{
    if (tarea != NULL)
    {
        printf("\n\tTarea encontrada\n");
        printf("ID: %d\n", tarea->T.TareaID);
        printf("Descripcion: %s\n", tarea->T.Descripcion);
        printf("Duracion: %d min\n", tarea->T.Duracion);
    }
    else
    {
        puts("\nID o Palabra clave no encontrada/o\n");
    }
}

void liberMemoria(Nodo *tarea)
{
    Nodo *auxTarea=tarea;
    Nodo *TareaAnterior=tarea;
    Nodo *TareaActual=tarea;
    while (auxTarea!=NULL)
    {
        free(auxTarea->T.Descripcion);
        auxTarea=auxTarea->Siguiente;
    }

    while (TareaActual!=NULL)
    {
        TareaAnterior=TareaActual;
        TareaActual=TareaActual->Siguiente;
        free(TareaAnterior);
    }
    
}
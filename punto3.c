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
Tarea  NuevaTarea(char *buff);
void controlarTareas(Nodo **tareasPendientes, Nodo **tareasRealizadas);
void agregarTareaAlinicio(Nodo **tarea, Tarea newTarea);//
void listarTareas(Nodo *tareas);
void AgregarTareaRealizada(Nodo **tareasRealizadas, Nodo *tarea);
Nodo *BuscaTareaPorPalabra(Nodo *tareasPendientes, Nodo *tareasRealizadas, char *buff);
Nodo *BuscaTareaPorId(Nodo *tareasPendientes, Nodo *tareasRealizadas);
void mostraTareaUnica(Nodo *tarea);
void liberMemoria(Nodo *tarea);
void QuitarTarea(Nodo **TareaPendiente, Nodo *tarea);
Nodo *CrearNodo(Tarea newTarea); //
void menu(Nodo **tareasPendientess, Nodo **tareasRealizadass, char *buff);



//>>>>>>>>>>>>>>>>><<   AQUI MAIN >>>>>>>>>>>>>>>>>>>>>>>>>>>>

int main(void)
{
    char *buff = (char *)malloc(sizeof(char) * 100);
    int opcion;
    Nodo *tareasPendientes = inicilizarLista();
    Nodo *tareasRealizadas = inicilizarLista();
    menu(&tareasPendientes,&tareasRealizadas,buff);
    liberMemoria(tareasPendientes);
    liberMemoria(tareasRealizadas);
    free(buff);
    return 0;
}

// >>>>>>>>>>>>>>>>>> FIN MAIN >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


Nodo *inicilizarLista()
{
    return (NULL);
}

/////   FUNCIONES NUEVAS ////
void agregarTareaAlinicio(Nodo **tarea, Tarea newTarea)
{
    Nodo *NuevaTarea;
    NuevaTarea = CrearNodo(newTarea);
    NuevaTarea->Siguiente=*tarea;
    *tarea=NuevaTarea;
}

Nodo *CrearNodo(Tarea newTarea)
{
   Nodo *NuevoNodo;
   NuevoNodo = (Nodo *)malloc(sizeof(Nodo));
   NuevoNodo->T=newTarea;
   NuevoNodo->Siguiente=NULL;
   return NuevoNodo;
}

Tarea NuevaTarea (char *buff)
{
    Tarea NewTarea;
    puts("ingrese la descripcion de la tarea: ");
    fflush(stdin);
    gets(buff);
    NewTarea.Descripcion=(char *)malloc((strlen(buff) + 1) * sizeof(char));
    strcpy(NewTarea.Descripcion, buff);
    NewTarea.Duracion = rand() % (100 - 10) + 10;
    NewTarea.TareaID = iteracion;
    iteracion++;
    return NewTarea;
}

void controlarTareas(Nodo **tareasPendientes, Nodo **tareasRealizadas)
{
    Nodo *auxTareasPendientes = *tareasPendientes;
    Nodo *TareaMover;
    int seleccion;
    puts("\n\tCONTEROL DE TAREAS REALIZADAS");
    while (auxTareasPendientes!=NULL)
    {
        printf("id: %d\n",auxTareasPendientes->T.TareaID);
        printf("Descripcion: %s\n",auxTareasPendientes->T.Descripcion);
        printf("duracion: %d min\n",auxTareasPendientes->T.Duracion);
        puts("Indique si relizo esta tarea (si=1 no=0)");
        fflush(stdin);
        scanf("%d",&seleccion);
        
        if (seleccion==1)
        {
            QuitarTarea (tareasPendientes,auxTareasPendientes); //quito el nodo
            TareaMover=auxTareasPendientes; //auxilio la direccion  de la tarea actual
            auxTareasPendientes=auxTareasPendientes->Siguiente; //salto a la siguiente tarea, como la voy a mover a relizadas
                                                                //el campo siguiente de la tarea del momento se va a ver afectada desde la 
                                                                //funcion agregarTareaRealizada es por eso que salto a la sigueinte tarea
            AgregarTareaRealizada(tareasRealizadas,TareaMover);

        }else
        {
            auxTareasPendientes=auxTareasPendientes->Siguiente;
        }   
        
    }
    
}
void QuitarTarea (Nodo **TareaPendiente, Nodo *tarea)
{
    Nodo *AuxTareaActual=*TareaPendiente;
    Nodo *auxTareaAnterior=*TareaPendiente;

    while ( AuxTareaActual!= tarea )
    {
        auxTareaAnterior=AuxTareaActual;
        AuxTareaActual=AuxTareaActual->Siguiente;
    }

    if (*TareaPendiente==AuxTareaActual) // si el tarea a quitar es la primera
    {
        *TareaPendiente=AuxTareaActual->Siguiente;
    } else {
        auxTareaAnterior->Siguiente=AuxTareaActual->Siguiente; //si la tarea no es la primera
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
    tarea->Siguiente = *tareasRealizadas;
    *tareasRealizadas = tarea;
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
void menu(Nodo **tareasPendientess, Nodo **tareasRealizadass, char *buff)
{
    Nodo *tareasPendientes=*tareasPendientess; 
    Nodo *tareasRealizadas=*tareasRealizadass;
    Nodo *busquedaID;
    Nodo *busquedaWord;
    int opcion;
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
                Tarea newTarea=NuevaTarea(buff);
                agregarTareaAlinicio(&tareasPendientes, newTarea);
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
}
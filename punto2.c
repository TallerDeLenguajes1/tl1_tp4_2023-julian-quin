#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea
{
    int TareaID; // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
}typedef Tarea;

void iniciarEnNull(Tarea ** TPendientes, int cantidad);
void CargarTarea(Tarea ** TPendientes, int cantidad, char * buff);
void checkTareas(Tarea ** TPendientes, int cantidad, Tarea ** TRealizadas);
void listarTareas(Tarea ** Tareas, int cantidad); 

int main(void)
{
    int cantTareas,duracion;
    Tarea **tareasPendientes;
    Tarea **tareasRealizadas;
    char *buff= (char *)malloc(sizeof(char)*100);
    printf("ingrese la cantidad de tareas a relizar\n");
    scanf("%d",&cantTareas);
    tareasPendientes = (Tarea**) malloc (sizeof(Tarea*)*cantTareas);
    iniciarEnNull(tareasPendientes,cantTareas);
    CargarTarea(tareasPendientes,cantTareas,buff);

    tareasRealizadas=(Tarea**) malloc (sizeof(Tarea*)*cantTareas);
    iniciarEnNull(tareasRealizadas,cantTareas);
    checkTareas(tareasPendientes,cantTareas, tareasRealizadas);
   
   
    puts("\tTareas Realizadas");
    listarTareas(tareasRealizadas,cantTareas);
    puts("\tTareas Pendientes");
    listarTareas(tareasPendientes,cantTareas);

    free(buff);
    return 0;
}

void iniciarEnNull(Tarea ** TPendientes, int cantidad)
{
    for (int  i = 0; i < cantidad; i++)
    {
        TPendientes[i]=NULL;
    }
    
}

void CargarTarea(Tarea ** TPendientes, int cantidad, char *buff)
{
    for (int i = 0; i < cantidad; i++)
    {
        TPendientes[i]=(Tarea*)malloc(sizeof(Tarea));
        printf("ingrese la descripcion de la tarea N %d\n",i+1);
        fflush(stdin);
        gets(buff);
        TPendientes[i]->Descripcion = (char*)malloc((strlen(buff)+1) * sizeof(char));
        strcpy(TPendientes[i]->Descripcion,buff);
        TPendientes[i]->Duracion= rand () % (100-10)+1;
        TPendientes[i]->TareaID=i;
    }
    
}
void checkTareas (Tarea ** TPendientes, int cantidad, Tarea ** TRealizadas)
{
    
    puts("\n\n\tchequeo de tareas\n");
    char yes_not;
    int j=0;
    for (int i = 0; i < cantidad; i++)
    {
        printf("Tarea Id= %d\n",TPendientes[i]->TareaID);
        printf("Decripcion: %s\n",TPendientes[i]->Descripcion);
        printf("Duracion: %d\n",TPendientes[i]->Duracion);
        printf("Realizo esta tarea (s o n)\n");
        fflush(stdin);
        scanf("%c",&yes_not);
        if (yes_not=='s')
        {
            TRealizadas[j]=TPendientes[i];
            TPendientes[i]=NULL;
            j++;
        }
        printf("\n\n");
    }
    puts("===============================");
}
void listarTareas(Tarea ** Tareas, int cantidad)
{
    puts("===============================");
    for (int i = 0; i < cantidad; i++)
    {
        if (Tareas[i]!=NULL)
        {
            printf("Tarea Id= %d\n",Tareas[i]->TareaID);
            printf("Decripcion: %s\n",Tareas[i]->Descripcion);
            printf("Duracion: %d\n",Tareas[i]->Duracion);
        }
     
    }
    puts("===============================");
    
}
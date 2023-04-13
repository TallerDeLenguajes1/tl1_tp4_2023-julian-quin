#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea
{
    int TareaID; // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
}typedef Tarea;

int main(void)
{
    int cantTareas,duracion;
    Tarea **tareas;
    Tarea *tareasRealizadas;
    char *buff= (char *)malloc(sizeof(char)*100);
    printf("ingrese la cantidad de tareas a relizar\n");
    scanf("%d",&cantTareas);
    tareas= (Tarea**) malloc (sizeof(Tarea*)*cantTareas);
    
    for (int i = 0; i < cantTareas; i++)
    {
        tareas[i]=NULL;
        tareas[i]=(Tarea*)malloc(sizeof(Tarea));
    }
    
    for (int i = 0; i < cantTareas; i++)
    {
        printf("ingrese la descripcion de la tarea");
        fflush(stdin);
        gets(buff);
        tareas[i]->Descripcion = (char*)malloc((strlen(buff)+1) * sizeof(char));
        strcpy(tareas[i]->Descripcion,buff);
        puts("ingrese la duracion");
        scanf("%d",&duracion);
        tareas[i]->Duracion=duracion;
        tareas[i]->TareaID=i;
    }
    

    return 0;
}
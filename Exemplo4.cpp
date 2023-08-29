#include <stdio.h>

typedef struct {
    int id;
    int runtime;
    int priority;
} Task;

int main() {
    Task tasks[] = {
        {1, 10, 2},
        {2, 8, 1},
        {3, 6, 3}
    };
    
    int numTasks = sizeof(tasks) / sizeof(tasks[0]);
    
    for (int time = 0; numTasks > 0; time++) {
        Task *highestPriorityTask = NULL;
        int highestPriorityIndex = -1;
        
        // Encontrar a tarefa de maior prioridade ainda não concluída
        for (int i = 0; i < numTasks; i++) {
            if (tasks[i].runtime > 0) {
                if (highestPriorityTask == NULL || tasks[i].priority < highestPriorityTask->priority) {
                    highestPriorityTask = &tasks[i];
                    highestPriorityIndex = i;
                }
            }
        }
        
        // Se nenhuma tarefa está pronta para ser executada, avançar o tempo
        if (highestPriorityTask == NULL) {
            printf("Tempo %d: Nenhuma tarefa pronta\n", time);
        } else {
            printf("Tempo %d: Executando Tarefa %d (Prioridade %d)\n", time, highestPriorityTask->id, highestPriorityTask->priority);
            highestPriorityTask->runtime--;
            
            if (highestPriorityTask->runtime == 0) {
                printf("Tarefa %d concluída.\n", highestPriorityTask->id);
                // Remover tarefa concluída
                for (int i = highestPriorityIndex; i < numTasks - 1; i++) {
                    tasks[i] = tasks[i + 1];
                }
                numTasks--;
            }
        }
    }
    
    return 0;
}

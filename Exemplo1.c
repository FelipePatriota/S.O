#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NUM_TAREFAS 5

void tarefa(int id) {
    printf("Tarefa %d executada\n", id);
}

int main() {
    // Definindo os tempos de início das tarefas (em microssegundos)
    int tempos_inicio[NUM_TAREFAS] = {1000, 2000, 3000, 4000, 5000};

    struct timespec tempo_atual;
    clock_gettime(CLOCK_MONOTONIC, &tempo_atual);

    for (int i = 0; i < NUM_TAREFAS; i++) {
        // Calcula o tempo de espera até o início da próxima tarefa
        int tempo_espera = tempos_inicio[i] - (tempo_atual.tv_nsec / 1000);

        // Aguarda até o momento exato para iniciar a tarefa
        if (tempo_espera > 0)
            usleep(tempo_espera);

        // Executa a tarefa
        tarefa(i);

        // Atualiza o tempo atual após a conclusão da tarefa
        clock_gettime(CLOCK_MONOTONIC, &tempo_atual);
    }

    return 0;
}

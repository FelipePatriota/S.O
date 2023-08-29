#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
#include <thread>

struct Task {
    int id;
    int remainingTime;
};

int main() {
    std::deque<Task> taskQueue;
    taskQueue.push_back({1, 5});
    taskQueue.push_back({2, 3});

    const int quantum = 2;

    while (!taskQueue.empty()) {
        Task currentTask = taskQueue.front();
        taskQueue.pop_front();

        std::cout << "Executando Tarefa " << currentTask.id << " por " << quantum << " unidades de tempo." << std::endl;

        if (currentTask.remainingTime > quantum) {
            currentTask.remainingTime -= quantum;
            taskQueue.push_back(currentTask);
        } else {
            currentTask.remainingTime = 0;
            std::cout << "Tarefa " << currentTask.id << " concluída." << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simula o tempo de execução
    }

    std::cout << "Todas as tarefas foram concluídas." << std::endl;

    return 0;
}

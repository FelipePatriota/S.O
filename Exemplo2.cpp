#include <iostream>
#include <thread>
#include <chrono>

void tarefa1() {
    for (int i = 0; i < 5; ++i) {
        std::cout << "Tarefa 1 executando (" << i + 1 << "/5)\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void tarefa2() {
    for (int i = 0; i < 5; ++i) {
        std::cout << "Tarefa 2 executando (" << i + 1 << "/5)\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
    }
}

int main() {
    std::thread thread1(tarefa1);
    std::thread thread2(tarefa2);

    thread1.join();
    thread2.join();

    std::cout << "Todas as tarefas foram concluídas.\n";

    return 0;
}

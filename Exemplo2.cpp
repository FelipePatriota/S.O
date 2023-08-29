#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

std::mutex mtx;  // Mutex para sincronização
std::condition_variable cv;  // Variável de condição para sincronização
bool ready = false;

void tarefaPrioritaria() {
    // Tarefa prioritária
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready; });  // Aguarda até que ready seja verdadeiro
    std::cout << "Tarefa Prioritária executada." << std::endl;
}

void tarefaNormal() {
    // Tarefa normal
    std::cout << "Tarefa Normal executada." << std::endl;
}

int main() {
    std::thread threadPrioritaria(tarefaPrioritaria);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Simula alguma atividade

    // Preparando para executar a tarefa prioritária
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_one();  // Notifica a tarefa prioritária para iniciar

    std::thread threadNormal(tarefaNormal);

    threadPrioritaria.join();
    threadNormal.join();

    return 0;
}

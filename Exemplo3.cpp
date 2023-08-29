#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <csignal>

std::atomic<bool> stop(false);

void handleSignal(int signum) {
    stop = true;
}

void temperaturaMonitor() {
    int temperatura = 20; // Inicializa a temperatura

    while (!stop) {
        // Simula medição da temperatura
        temperatura = rand() % 40; // Temperatura entre 0 e 39 graus Celsius

        // Simula verificação de limite crítico
        if (temperatura > 35) {
            std::cout << "ALERTA: Temperatura crítica! " << temperatura << " graus Celsius.\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(1)); // Intervalo de medição
    }
}

int main() {
    signal(SIGINT, handleSignal); // Configura o tratamento da interrupção (Ctrl+C)

    std::thread monitorThread(temperaturaMonitor);

    // Aguarda até que o usuário interrompa (Ctrl+C)
    while (!stop) {
        std::this_thread::yield(); // Libera o processador para outras tarefas
    }

    monitorThread.join(); // Espera a thread do monitor terminar

    std::cout << "Programa encerrado." << std::endl;

    return 0;
}

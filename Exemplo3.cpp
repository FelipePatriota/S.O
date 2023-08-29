#include <iostream>
#include <csignal>
#include <thread>
#include <chrono>
#include <atomic>

std::atomic<bool> obstacleDetected(false);

void handleObstacleDetection(int signum) {
    obstacleDetected = true;
}

void detectObstacles() {
    signal(SIGUSR1, handleObstacleDetection); // Configura o tratamento da interrupção de detecção de obstáculos

    while (true) {
        if (obstacleDetected) {
            std::cout << "Obstáculo detectado! Parando o veículo imediatamente." << std::endl;
            // Lógica para parar o veículo
            obstacleDetected = false;
        }

        // Lógica de temporização para verificar as condições periodicamente
        std::cout << "Verificando obstáculos..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Verifica a cada 100 milissegundos
    }
}

int main() {
    std::thread obstacleThread(detectObstacles);

    // Simula a detecção de um obstáculo (gera interrupção)
    std::this_thread::sleep_for(std::chrono::seconds(2));
    raise(SIGUSR1); // Detecção de obstáculo

    obstacleThread.join(); // Espera a thread de detecção de obstáculos terminar

    return 0;
}

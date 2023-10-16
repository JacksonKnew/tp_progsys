/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Threads.cpp
 * c++ -std=c++20 Threads.cpp -o Threads -lpthread
 */

#include <iostream>
#include <thread>
 
 
#include "../Random.hpp"

#include "osyncstream.hpp"
#include "Producer.hpp"
#include "Consumer.hpp"
#include "MessageBox.hpp"
 
/*
 * Test avec 1 producteur et 1 consommateur
 */
void one_producer_one_consumer() {
    // TODO :
    // - Créer un générateur de nombres aléatoires
    // - Créer une boîte à lettres
    // - Créer un producteur et un consommateur
    // - Créer les threads correspondants
    // - Attendre la fin des threads
    
    Random random_engine{50}; 
    MessageBox box{};
    Producer producer{1, box, random_engine, 20};
    Consumer consumer{2, box, random_engine, 20};

    std::thread prod_thread(producer);
    std::thread cons_thread(consumer);

    prod_thread.join();
    std::cout << "joined prod thread" << std::endl;
    cons_thread.join();
    std::cout << "joined cons thread" << std::endl;
}

/*
 * Test avec plusieurs producteurs et consommateurs
 */
void several_producers_and_consumers() {
    // TODO :
    // - Créer un générateur de nombres aléatoires
    // - Créer une boîte à lettres
    // - Créer entre 10 et 20 consommateurs et 2 fois plus de producteurs 
    // - Créer les threads correspondants
    // - Attendre la fin des threads
 
}

int main() {
    one_producer_one_consumer();
    //several_producers_and_consumers();
    return 0;
}


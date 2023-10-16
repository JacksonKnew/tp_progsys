/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Consumer.hpp
 */

#pragma once

#include <iostream>
#include <thread>

#include "../ProdOrCons.hpp"
 
#include "osyncstream.hpp"
#include "MessageBox.hpp"


/*
 * Consommateur de messages
 */
class Consumer : public ProdOrCons< MessageBox > {
public:
    // Le constructeur de ProdOrCons sera utilisé comme constructeur de Consumer
    using ProdOrCons::ProdOrCons;
    using microseconds = std::chrono::duration< int, std::micro >;
 
    void operator()() override {
        std::cout << "entered cons operator" << std::endl;
        // TODO :retirer de box_ nb_messages_ entiers avec attente aléatoire avant
        // chaque retrait. Afficher des messages pour suivre l'avancement.
        // Afficher un message d'erreur si un nombre négatif est extrait.
        int message;

        for (int i = 0; i < nb_messages_; i++) {
            message = box_.get();
            if (message < 0) {
                perror("got negative number");
                exit(EXIT_FAILURE);
            }
            osyncstream{std::cout} << "Got message " << message << "\n";
            std::this_thread::sleep_for( microseconds{ random_engine_() });
        }
    }
};


/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Producer.hpp
 */

#pragma once

#include <iostream>
#include <thread>

#include "../ProdOrCons.hpp"
 
#include "osyncstream.hpp"
#include "MessageBox.hpp"

/*
 * Producteur de messages
 */
class Producer : public ProdOrCons< MessageBox > {
public:
    // Le constructeur de ProdOrCons peut être utilisé pour Producer
    using ProdOrCons::ProdOrCons;
    using microseconds = std::chrono::duration< int, std::micro >;
 
    void operator()() override {
        std::cout << "entered prod operator" << std::endl;
        // TODO : déposer dans box nb_messages nombres entiers positifs avec attente
        // aléatoire entre chaque. Afficher des messages pour suivre l'avancement.
        for (int i = 0; i < nb_messages_; i++) {
            int r = random_engine_();
            box_.put(r);
            osyncstream{std::cout} << "adding " << r << " integer to box\n";
            std::this_thread::sleep_for( microseconds{ random_engine_() });
        }
    }
};
 

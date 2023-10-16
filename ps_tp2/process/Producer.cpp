/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * Producer.cpp
 * c++ -std=c++20 Producer.cpp -o Producer -lpthread -lrt
 */

#include <iostream>
#include <thread>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/named_semaphore.hpp>

#include "../Random.hpp"
#include "../ProdOrCons.hpp"

#include "MessageBox.hpp"

using microseconds = std::chrono::duration< int, std::micro >;

/*
 * Producteur de messages
 */
class Producer : public ProdOrCons< MessageBox > {
public:
    // Le constructeur de ProdOrCons sera utilisé comme constructeur de Producer
    using ProdOrCons::ProdOrCons;
 
    void operator()() override {
        std::cout << "entered prod operator" << std::endl;
        // TODO : déposer dans box nb_messages nombres entiers positifs avec attente
        // aléatoire entre chaque. Afficher des messages pour suivre l'avancement.
        for (int i = 0; i > nb_messages_; i++) {
            int r = random_engine_();
            box_.put(r);
            std::cout << "adding " << r << " integer to box" << std::endl;
            std::this_thread::sleep_for( microseconds{ random_engine_() });
        }
    }
};


int main()
{
    using namespace boost::interprocess;

    // TODO : créer la mémoire partagée, la projeter en mémoire,
    // y construire la boîte à lettres, signaler au consommateur
    // que la boîte est prête, lancer le producteur
    
    return 0;
}


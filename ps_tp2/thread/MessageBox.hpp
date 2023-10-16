/*
 * Cursus CentraleSupélec - Dominante Informatique et numérique
 * 3IF1020 - Programmations système - TP n°2
 *
 * MessageBox.hpp
 */

#pragma once

#include <mutex>
#include <condition_variable>

#include "../BasicMessageBox.hpp"

/*
 * FIFO d'echange de messages entre producteurs et consommateurs
 * Version pour synchronisation entre threads
 */
class MessageBox : public BasicMessageBox {
public:
    void put( int message ) {
        // TODO :
        // - Ajouter les instructions de synchronisation
        // - Ne pas faire d'affichage dans cette méthode
        std::unique_lock<std::mutex> lock_put(matmut);
        while (data_available == box_size_) {status_empty.wait(lock_put);}
        basic_put( message );
        data_available += 1;
        status_full.notify_one();
    }
 
    int get() {
        // TODO :
        // - Ajouter les instructions de synchronisation
        // - Ne pas faire d'affichage dans cette méthode
        std::unique_lock<std::mutex> lock_get(matmut);
        while (data_available == 0) {status_full.wait(lock_get);}
        int message{ basic_get() };
        data_available -= 1;
        status_empty.notify_one();
        return message;
    }
private:
    // TODO : 
    // - Ajouter les objets de synchronisation
    std::mutex matmut;
    std::condition_variable status_full, status_empty;
    int data_available;
};
 

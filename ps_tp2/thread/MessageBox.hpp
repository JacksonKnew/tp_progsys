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
        basic_put( message );
    }
 
    int get() {
        // TODO :
        // - Ajouter les instructions de synchronisation
        // - Ne pas faire d'affichage dans cette méthode
        int message{ basic_get() };
        return message;
    }
private:
    // TODO : 
    // - Ajouter les objets de synchronisation
};
 

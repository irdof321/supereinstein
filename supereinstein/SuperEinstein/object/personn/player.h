#ifndef PLAYER_H
#define PLAYER_H

#include "personn.h"

/**
 * @class The Player class
 * is the class who be played by a player in the game
 */

class Player : public Personn
{
        Q_OBJECT
    /***************************************************
     * Player is an object that can be "alived"
     * this is the object that can be moved
     * *************************************************/
    private:
        QLabel* _labelLife;
    public:
        Player(QPoint& position);
        ~Player() override;
        QLabel* getLabel() override;
        bool isDead();
        QLabel* getHeart();
        /**
         * @brief getId
         * @return Einstein
         */
        element getId() override;
        void setIsTouch(bool b) override;


};

#endif // PLAYER_H

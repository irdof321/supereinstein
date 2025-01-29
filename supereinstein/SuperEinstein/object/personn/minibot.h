#ifndef MINIBOT_H
#define MINIBOT_H


#include "personn.h"
#include "Utility/Utility.h"


#define BOT_STATES 3
#define BOT_SIZE 50

/**
 * @class The MiniBot class
 * The MiniBot class is an IA class
 * MiniBot move right and left, it is all
 *
 * MiniBot has only three states :
 * walkright , walkleft and deadstate
 */

class MiniBot : public Personn
{
        Q_OBJECT
    private:
        bool _moveRight;
        Matrix* _posWorld;
    public:
        /**
         * @brief MiniBot
         * @param p is the position
         * @param posWorld is the matrix contains the relatives data
         * of how the BaseElem are placed in the world, important for
         * the IA
         */
        MiniBot(QPoint& p,Matrix* posWorld);
        /**
         * @brief getLabel
         * @return the label corresponding
         * to the states set
         */
        QLabel* getLabel() override;
        /**
         * @brief getMoveRight
         * get the value of _moveRight
         * @return true if the bot is moving
         * right
         */
        bool getMoveRight();
        /**
         * @brief setMoveRight
         * set the boolean value of _moveRight
         * @param b set the value true if bot is
         * moving right otherwise must be false
         * the user have to manage this
         */
        void setMoveRight(bool b);
        /**
         * @brief thereIsHole
         * @param dir mean in which direction the bot is going
         * it is the type of direction
         * @return true if there is hole in the next step in direction
         * of dir
         */
        bool thereIsHole(UtilityGame::direction dir);
        /**
         * @brief getId
         * @return element::Bot
         */
        element getId() override;

};

#endif // MINIBOT_H

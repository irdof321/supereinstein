#ifndef DATA_H
#define DATA_H

#include <QObject>
#include "object/personn/player.h"
#include "object/BaseElem/underfloor.h"
#include "object/BaseElem/box.h"
#include "object/BaseElem/floor.h"
#include "object/personn/newton.h"

#define L_MATRIX 1000
#define H_MATRIX 16



#include <vector>

/**
 * @brief The Data class
 *
 */

class Data : public QObject
{
        Q_OBJECT
    private:
        std::vector<BaseElem*>* _inGame;
        Player* _player;
        Matrix* _element;
        std::vector<MiniBot*>* _bots;

    public:
        Data(QObject* parent = nullptr);
        ~Data();
        /**
         * @brief getPlayer
         * @return _player of the game
         */
        Player* getPlayer();
        /**
         * @brief getBaseElem
         * @return all the BaseEleme in the world
         */
        std::vector<BaseElem*> getBaseElem() ;
        /**
         * @brief getBot
         * @return all the MiniBots in the world
         */
        std::vector<MiniBot*> getBot();
        /**
         * @brief playerFall
         * is called when player fall under a certain
         * limit and then player lose a life
         */
        void playerFall();
        /**
         * @brief BotIsDead
         * "kill" the Minibot in position i in _bots
         * @param i
         */
        bool BotIsDead(int i);


    public slots:
        void dataUpdate();
        /**
         * @brief reset all the ekement
         * _bots, _inGame, _player and _element
         */
        void reset();
        /**
         * @brief init the world
         * @param d
         */
        void init(UtilityGame::difficulty d);
    signals:
        void SigUpdate();
};

#endif // DATA_H

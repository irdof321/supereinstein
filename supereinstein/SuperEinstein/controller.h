#ifndef CONTROLLER_H
#define CONTROLLER_H
#define RANGE_X_BOT 300

#define INT_X_MOVE 1
#define INT_Y_MOVE 5
#define TIME_INTERVAL 5






#define HEIGHT_JUMP  200;


//define jump parameters


#include <QTimer>
#include "data.h"
#include "view/inputview.h"
#include "view/outputview.h"
#include "view/menu.h"
#include <QString>
#include <QSoundEffect>

using namespace UtilityGame;


class Controller : public QObject
{

        Q_OBJECT
    private:
        QSoundEffect* _music;               //backround music
        QTimer* _timer;                     // timer for call integrate()
        QTimer* _pTouchTimer;
        Data* _data;                        // all the datas in the game
        InputView* _inView;
        UiEvent _task;                    // which key from keyboard to execute next
        OutputView* _outView;
        /**
         * @brief executionOfTask
         * execute the next task _task
         */
        void executionOfTask();
        /**
         * @brief movePlayerLeft
         * @param move
         * move the personn to left of move if it is possible
         */
        void movePersonnLeft(int move);
        /**
         * @brief moveplayerRight
         * @param move
         * move the personn to right of move if it is possible
         */
        void movePersonnrRight(int move);
        /**
         * @brief jumpPlayer allow the player to jump
         * of each clock timwout of -Y_INT_MOVE until he reach
         * HEIGHT_JUMP
         */
        void jumpPlayer();
        /**
         * @brief PlayCanJump
         * @return true if player can jump
         */
        bool PlayCanJump();
        /**
         * @brief PersonnCanMove
         * @param p
         * @param keyMove
         * @return true if player can does keyMove effect
         */
        bool PersonnCanMove(Personn* p,UiEvent keyMove);
        /**
         * @brief canMoveCalc is the algo in personnCanMove
         *
         * @param xp position x of the personn
         * @param yp position y of the personn
         * @param xo position x of the object
         * @param yo position y of the object
         * @param pxSize x length of the personn
         * @param pySize y length of the personn
         * @param keyMove UiEvent who means wich action the player will do
         * @param p The personn
         * @param withBotint set true if the collision is with a MiniBot
         * @param oXsize x length of the object
         * @param oYsize y length of the object
         * @return true if personn can move false otherwise
         */
        bool canMoveCalc(int xp, int yp, int xo, int yo, int pxSize, int pySize, UiEvent keyMove, Personn* p,
                         bool withBotint,int  oXsize = DEFAULT_SIZE,int oYsize = DEFAULT_SIZE);
        /**
         * @brief BotHurtPlayer
         * @param xb position x of the bot
         * @param yb position y of the bot
         * @param xp position x of the player
         * @param yp position y of the player
         * @param pxSize x length of the personn
         * @param pySize y length of the personn
         * @param keyMove UiEvent who means wich action the player will do
         * @return true if a MiniBot in Game touch the player
         */
        bool BotHurtPlayer(int xb, int yb, int xp, int yp, int pxSize, int pySize, UiEvent keyMove);
        /**
         * @brief gravity simulate gravity on all personn
         * if a bot receive a player on himself, then he  lose a life
         */
        void gravity();
        /**
         * @brief IAControlBot control all the bot
         */
        void IAControlBot();
        float YMaxJump;                         // it is use in jump for perform a parabol jump
        bool _onMenu;
    public:
        Controller();
        ~Controller();
        void show();
    public slots:
        /**
         * @brief integrate is called on each timoeout and
         * integrate the game and all thing inside, it compute all
         * necessary things, like gravity
         */
        void integrate();
        /**
         * @brief setTask
         * set _task to task
         * @param task
         */
        void setTask(UiEvent task);
        /**
         * @brief start start the timer
         */
        void start();
        /**
         * @brief setVolume set Volumeof _music
         */
        void setVolume(int);
        /**
         * @brief playerIsNoTouch set isTouch of player to false
         * who means that player can be touched by a bot
         */
        void playerIsNoTouch();
        /**
         * @brief end
         * is the end of the game
         */
        void end();
    signals:
        /**
         * @brief sendUpdate signals that an update of displays must be done
         * to _outputView
         */
        void sendUpdate();
        /**
         * @brief showMenu signal to _outputView that the
         * menu must be shown
         */
        void showMenu();                         //show the menu in game
        /**
         * @brief gameOver is emit when player has no more life
         */
        void gameOver();
        void sigEnd();

};



#endif // CONTROLLER_H

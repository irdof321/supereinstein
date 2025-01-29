#ifndef PERSONN_H
#define PERSONN_H

#include "object/object.h"
#include "vector"
#include<QMovie>
#include <QMap>

#define NB_STATES 6
#define SCALE 0.5
#define X_SIZE_PLAYER SCALE*100
#define Y_SIZE_PLAYER SCALE*200

/**
 * @class The Personn class
 * is an object who can move
 * contain a QLabel for the texture
 */
class Personn : public Object
{

        protected:
        stateOfPersonn _state;
        /**
         * @brief _labelStates all states of the player
         * useful for fix the good label
         * This contain all the movie in label related to
         * a state of the personn, for each state used one label must
         * be define
         */
        QMap <stateOfPersonn,QLabel*>* _labelStates;
        /**
         * @brief closeAndHide
         * is called on each change state, all the movies that not correspond
         * to the current state are stopped
         * and the label are hide,
         */
        void closeAndHide();

        bool _isJumping;
        bool _isOnFloor;
        int _life;        
        bool _isTouch;

    public:
        Personn(QPoint& position);
        ~Personn() override;
        /**
         * @brief setStatePersonn
         * @param state change the current state of the personn
         */
        void setStatePersonn(stateOfPersonn state);
        /**
         * @brief setIsJumping
         *  this value must be true
         * if the personn is jumping, the user have to manage this
         * @param isJumping set the value of _isJumping
         */
        void setIsJumping(bool isJumping);
        /**
         * @brief getIsJumping
         * @return the value of _isJumping ,true if is jumping
         * false otherwise
         */
        bool getIsJumping();
        /**
         * @brief getIsOnFloor
         * @return the value of _isOnFloor ,true if is on a floor
         * false otherwise
         */
        bool getIsOnFloor();
        /**
         * @brief setIsOnFloor
         *  this value must be true
         * if the personn is on a floor, the user have to manage this
         * @param b set the value of _isJumping
         */
        void setIsOnFloor(bool b);
        /**
         * @brief getLabel
         * @return  the correct label depending on personn state
         */
        virtual QLabel* getLabel();
        /**
         * @brief movePersonn
         * move the personn, it changes the value of the QPoint _position
         * @param dx change the x coordinate on x axis
         * @param dy change the y coordinate on x axis
         */
        void movePersonn(int dx=0, int dy = 0);
        /**
         * @brief isDead
         * @return true if _life = 0
         */
        bool isDead();
        /**
         * @brief loseLife
         * decrease _life
         */
        void loseLife();
        /**
         * @brief getHeart
         * @return the label of the heart life icon
         */
        QLabel* getHeart();
        /**
         * @brief getLife
         * @return the value of _life
         */
        int getLife();
        /**
         * @brief setLife
         * @param life set the value of _life
         */
        void setLife(int life);
        /**
         * @brief getId
         * @return nothing, a virtual class do not return an ID
         */
        virtual element getId() override;
        /**
         * @brief setScaledSize
         * resize the containt of the movie for fit in a rectangle with size scale
         * @param scale is the new wanted size
         */
        void setScaledSize(QSize scale);
        /**
         * @brief getIsTouch
         * @return the value of _isTouch
         */

        bool getIsTouch();
        /**
         * @brief setIsTouch
         * if the personn is touched return true, the user have to manage this
         * ,this value not have to be necessary managed, depending of what the user need
         * @param b set the value of _isTouch
         */
        virtual void setIsTouch(bool b);
};

#endif // PERSONN_H

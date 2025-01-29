#ifndef MENU_H
#define MENU_H

#include "view.h"
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include<QCheckBox>
#include <QHBoxLayout>
#include "Utility/Utility.h"
#include <QMovie>

/**
 * @class The Menu class show a menu for the game
 */

class Menu : public View
{
    /****************************
     * It is a menu with some command
     * * **************************/
        Q_OBJECT
    private:
        QPushButton* _start;
        QPushButton* _showCommand;
        QPushButton* _reset;
        QSlider* _sound;
        QLabel* _difLab;
        QLabel*_mediumLab;
        QLabel* _hardLab;
        QCheckBox* _easy;
        QCheckBox* _medium;
        QCheckBox* _hard;
        bool _diffIsChoose;
        QLabel* _listCommand;
        QLabel* _endLab;
        bool _menuIsShow ;
    public:
        Menu(QWidget*parent = nullptr);
        /**
         * @brief setDiffIsChoose
         * @param b set menuIsShow , if the menu have to be show or not
         */
        void setDiffIsChoose(bool b);

    public slots:
        /**
         * @brief sloStart
         * when start is pushed hide
         * the menu and emit the sigStart()
         */
        void sloStart();
        /**
         * @brief volumeChanged
         * emit signal volume(int)
         */
        void volumeChanged();
        /**
         * @brief showMenu
         * show the menu and buttons
         */
        void showMenu();
        /**
         * @brief diffIschoose
         * @param d is the difficulty send with sigDiff and hide
         * the difficulty label _difLab
         */
        void diffIschoose(UtilityGame::difficulty d);
        /**
         * @brief easy set diff emit sigDiff(easy)
         */
        void easy();
        /**
         * @brief medium set diff emit sigDiff(medium)
         */
        void medium();
        /**
         * @brief hard set diff emit sigDiff(hard)
         */
        void hard();
        /**
         * @brief update the view of the menu
         * this method must be call each time when
         * the parent Window change size with param
         * between 0 and 1 of type double who indicate
         * the scale changed
         * @param sx is the scale changed in x
         * @param sy is the scale changed in y
         */
        void update(double sx = 1,double sy = 1);
        /**
         * @brief sloReset reset the _difLab
         * and emit sigReset
         */
        void sloReset();
        void end();

    signals:
        void sigStart();
        void volume(int);
        void sigDiff(UtilityGame::difficulty d);
        void sigReset();
};

#endif // MENU_H

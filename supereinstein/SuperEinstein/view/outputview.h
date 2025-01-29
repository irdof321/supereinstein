#ifndef OUTPUTVIEW_H
#define OUTPUTVIEW_H

#include "view.h"
#include "menu.h"
#include "../data.h"
#include <vector>
#include <QLabel>
#include <QPicture>
#include <QMap>
#include <QTimer>
#include <QPainter>


//#define gridOn true

#define SCREEN_X_SIZE 1000
#define SCREEN_Y_SIZE 800

#define DEFAULT_HEIGHT_FLOOR 400

/**
 * @brief The OutputView class
    *  displays all
    * the elements in data
    * and a font in background
 */
class OutputView : public View
{
    /**************************
    * OutputView displays all
    * the elements in data
    * and a font in background
    * ***********************/
        Q_OBJECT
    private:
        Data* _data;
        QPixmap* _Font;
        Menu* _menu;
        QPixmap* _heart;
        bool _onMenu;
        bool _showgameOver;
        QPixmap* _gameOverPixmap;
        QLabel* _touch;
        QTimer* _timer;
        double _scaleXFromBeg;
        double _scaleYFromBeg;
    public:
        OutputView( Data* data,QWidget* parent = nullptr);
        ~OutputView() override;
        void keyPressEvent(QKeyEvent* e) override;
        void keyReleaseEvent(QKeyEvent*e) override;

    public slots:
        /**
         * @brief sloStart for know if the game is started
         * in this case sloStart turn _onMenu false who indicates
         * that the menu must be hide
         */
        void sloStart();
        /**
         * @brief showMenu turn _onMenu true who indicates
         * that the menu must be showed
         */
        void showMenu();
        /**
         * @brief gameOver display gameOver sequence
         */
        void gameOver();

    signals:
        void sigKeyPressed(QKeyEvent*);
        void sigKeyRleased(QKeyEvent*);
        void sigStart();
        void volume(int);
        void sigShowMenu();
        void sigDiff(UtilityGame::difficulty d);
        void sigReset();
        void sigEnd();
    protected:
        void paintEvent(QPaintEvent* event) override;
};

#endif // OUTPUTVIEW_H

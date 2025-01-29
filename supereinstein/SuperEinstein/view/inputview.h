#ifndef INPUTVIEW_H
#define INPUTVIEW_H

#include "view.h"
#include <QKeyEvent>
#include"Utility/Utility.h"


using namespace UtilityGame;

/**
 * @brief The InputView class
 * manage all the input from the player
 */
class InputView : public View
{

    Q_OBJECT

    public:
        InputView(QWidget *parent = nullptr);
        ~InputView() override;

    private:
        void keyPressEvent(QKeyEvent* e) override;
        void keyReleaseEvent(QKeyEvent* e) override;

    public slots:
           void sloKeyPressed(QKeyEvent*e);
           void sloKeyReleased(QKeyEvent*e);
    signals:
           /**
         * @brief UpPushed
         * send the UiEvent who was pushed by player
         */
        void UpPushed(UiEvent);                         // send the current kexPressed as a UiEvent enum


};

#endif // INPUTVIEW_H

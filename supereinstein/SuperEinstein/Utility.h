#ifndef UTILITY_H
#define UTILITY_H


#include <QMap>
#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QMap>
#include <vector>
#include <ctime>
#include<QFile>

class Object;
class Player;

#define NB_UIEVENT 7


namespace UtilityGame {

    /**
     * @enum The UiEvent enum
     * contains all
     * actions needed that can be receive from
     * keyboard
     */
    enum UiEvent {a,d,A,D,space,esc,no};

    /**
     * @enum The stateOfPersonn contains
     * all state of a personn, each girl of personn class
     * doesnt nescessary have all states
     */
    enum stateOfPersonn {stay , walkRight, walkLeft, jumpRight, jumpLeft, jumpFace,deadSate};

    /**
     * @brief norm return the norm of the vector in 2D
     * @param p vector of type QPoint
     * @return a float equal to the norm
     */
    float norm(QPoint p);
    /**
     * @enum The element conatins all different type of object in game
     */
    enum element {Object,HoleElem,underFloorElem,FloorElem,BoxElem,Bot,Einstein,Newton};
    /**
     * @enum The difficulty contains the different name of difficulty
     */
    enum difficulty {easy,medium,hard};    
    /**
     * @enum The direction is left or right
     */
    enum direction {left,right};
}



class debugConsol: public QWidget
{

        /**
         * @brief The debugConsol class
         * it is a display of text
         */

        Q_OBJECT
    public:
        debugConsol();
        ~debugConsol() {}
        void sendMessage(QString& message);
    private:
        int NbWord;
        QHBoxLayout* _lay;
        QLabel* _log;
        QScrollArea* _scr;
};


/**
 * @class The Matrix class is a matrix of int
 */
class Matrix {

/*******************************************************
 *          l
 *      _________
 *      |       |
 *     h|       |
 *      |       |
 *      ---------
 *          MatrixElement contains a matrix h*l
 * *****************************************************/
    private:
        std::vector<std::vector<int>> _matrix;
        int _row;
        int _line;
    public:
        /**
         * @brief MatrixElement create a matrix
         * rxl with zero
         * @param l is row position
         * @param h is height is the line position
         */
        Matrix(int l, int r);
        /**
         * @brief setElem
         * @param r is the place in the row
         * @param l is the place in the line
         * @param nb is the new number
         */
        void setElem(int r, int l, int nb);
        /**
         * @brief getElem
         * @param r is the place in the row
         * @param l is the place in the line
         * @return the value in M_rxl
         */
        int getElem(int r,int l );
        /**
         * @brief setMatrixFromTxt
         * load a matrix from txt, make sure
         * that the txt have at least l*h parameters
         *if one parameter can t be read, it will
         * be replace with a zero, if all the lines
         * have not the same number of elements it could be a crach
         * the user must be careful about this
         * @param fileName
         * this is the filename of the txt for
         * loading matrix
         */
        void setMatrixFromTxt(QString fileName);
        /**
         * @brief operator []
         * return the l-th row
         * @param l
         * @return
         */
        std::vector<int>& operator[] (int l);
        /**
         * @brief size
         * @return a vector contains the size of row and the size of line
         */
        std::vector<int> size();


};

#endif // UTILITY_H

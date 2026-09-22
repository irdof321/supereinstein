#include "Utility.h"
#include <math.h>
#include <QDebug>

using namespace UtilityGame;
using namespace std;

/***************************************************************
 * Utility functions and variable
 * ************************************************************/
    QPoint ZeroPoint (120,300);

float UtilityGame::norm(QPoint p)
{
    return sqrt((p.x()*p.x())+(p.y()*p.y()));
}


/*******************************************************************
 * Matrix class methods
 * *******************************************************************/

    Matrix::Matrix(int l, int r): _row(l),_line(r)
    {
        vector<int> vh (r);
        _matrix =  vector<vector<int>>();

        for (int i(0);i<r;++i){             // init a row of 0
            vh[i] =0;
        }

        for (int j(0);j<l;++j){
            _matrix.push_back(vh);          // add the rows with 0
        }
    }

    void Matrix::setElem(int r, int l, int nb)
    {
        (_matrix)[r][l] = nb;
    }

    int Matrix::getElem(int r, int l)
    {
        return (_matrix)[r][l];
    }

    void Matrix::setMatrixFromTxt(QString fileName)
    {
        QFile f(fileName);
        f.open(QIODevice::ReadOnly);
        int j(0);
        while (!f.atEnd()) {                                    //is file is found
            QString line = f.readLine();
            for(int i(0);i<_row;i++){
                QChar c = line[i];
                if(!(c.isNumber())){
                    this->setElem(i,j,0);
                }else {
                    this->setElem(i,j,(c.digitValue()));
                }

            }
            j++;
        }
    }

    std::vector<int>& Matrix::operator[](int l)
    {
        return _matrix[l];
    }

    std::vector<int> Matrix::size()
    {
        return {_row,_line};
    }








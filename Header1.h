#ifndef MAT_H
#define MAT_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;


class Mat {
    int col;
    int lin;
    int** matrice;

public:

    Mat(int, int);
    Mat();
    Mat(Mat&);
    ~Mat();
    Mat operator=(Mat&);
    Mat operator+(const Mat&)const;
    Mat operator-(const Mat&)const;
    vector<int>& operator[] (int) const;
    Mat operator*(const Mat&)const;
    Mat operator*(int)const;
    friend std::istream& operator>>(std::istream& in, Mat&);
    friend std::ostream& operator<<(std::ostream& in, const Mat&);
    int det(Mat&);
    int nrlin(Mat&);
    int nrcol(Mat&);
    Mat& removelin(Mat&, int);
    Mat& removecol(Mat&, int);
    Mat& remove(Mat&, int, int);
};
#endif //MAT_H
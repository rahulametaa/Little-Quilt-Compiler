#ifndef MAT_H
#define MAT_H
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Tile{
 private:
    char name;
    int no;
 public:
    Tile();
    Tile(char name); 
    void rotate_clock(); 
    void display();

}; 

class Quilt{
 private:
       vector< vector<Tile> > mat;  
       int row;
       int col;
      
 public:
     Quilt();
     Quilt(char name);
     Quilt turn();
     Quilt sew(Quilt &m);
     Quilt hdRow();
     Quilt tlRows();
     Quilt hdCol();
     Quilt tlCols();
     void display();



};

#endif

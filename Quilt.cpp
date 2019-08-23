#include<iostream>
#include<string>
#include"Quilt.h"

using namespace std;

Tile::Tile(){}

Tile::Tile(char name){
  this->name=name;
  this->no=0;

}


void Tile::rotate_clock(){
  no=(no+1)%4;

}


void Tile::display(){
   cout<<name<<no<<" ";

}

Quilt::Quilt(){}

Quilt::Quilt(char name){
     vector<Tile> x;
     Tile T(name);
     x.push_back(T);
     mat.push_back(x);
     row=1;
     col=1; 

}


Quilt Quilt::sew(Quilt &m){
  try{
       if(this->row!=m.row)
           throw this->row;
     }
  catch(int x){
          cout<<"Error:Can't perform sew operation\n";
          exit(1);
       }
  Quilt M;
  M.row=this->row;
  M.col=this->col+m.col;
  vector<Tile> temp;

  for(int i=0;i<m.row;i++)
   {  
      temp.clear(); 
      for(int j=0;j<this->col;j++)
           temp.push_back(this->mat[i][j]);
      for(int j=0;j<m.col;j++)
           temp.push_back(m.mat[i][j]);
      M.mat.push_back(temp);        
   }
 
  return M;
  
  
}



void Quilt::display(){

 cout<<"ROWS="<<row<<endl;
 cout<<"COLUMNS="<<col<<endl<<endl;

  for(int i=0;i<row;i++){
     for(int j=0;j<col;j++)
       mat[i][j].display();

    cout<<endl;
  }
  
}


Quilt Quilt::turn(){
     Quilt M;
     M.row=this->col;
     M.col=this->row;
     
     vector<Tile> x; 
     for(int i=0;i<M.row;i++)
     {
           x.clear();
           for(int j=M.col-1;j>=0;j--){
                x.push_back(this->mat[j][i]);
              }
           M.mat.push_back(x);

      }

     for(int i=0;i<M.row;i++)
       for(int j=0;j<M.col;j++)
             M.mat[i][j].rotate_clock();
     
     return M;
}


Quilt Quilt::hdRow(){
  Quilt M;
  M.row=1;
  M.col=col;
  M.mat.push_back(mat[0]);
  return M;

}


Quilt Quilt::tlRows(){
  Quilt M;
  M.row=row-1;
  M.col=col;
  for(int i=1;i<row;i++)
     M.mat.push_back(mat[i]);
  return M;

}


Quilt Quilt::hdCol(){
  Quilt M;
  M.row=row;
  M.col=1;
  vector<Tile> x;
  for(int i=0;i<row;i++){
     x.clear();
     x.push_back(mat[i][0]);
     M.mat.push_back(x);
    }
  return M;

}



Quilt Quilt::tlCols(){
  Quilt M;
  M.row=row;
  M.col=col-1;
  vector<Tile> x;
  for(int i=0;i<row;i++){
      x.clear();
     for(int j=1;j<col;j++)
          x.push_back(mat[i][j]);
    M.mat.push_back(x); 

  }
  return M;

}










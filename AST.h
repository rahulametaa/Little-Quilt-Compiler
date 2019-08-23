#ifndef AST_H
#define AST_H
#include"Quilt.h"
#include "Gcode.h"
#include<string>
#include<fstream>
#include<vector>
using namespace std;

class AST{
protected:
      static int c;
public:
    virtual void printtree()=0;
    virtual Quilt solve()=0;
    virtual Gcode generate_cpp()=0;

};


class Turn_AST:public AST{
  AST *ptr;
  public:
    Turn_AST(AST *ptr); 
    virtual void printtree();
    virtual Quilt solve();    
    virtual Gcode generate_cpp();
 
};



class Sew_AST:public AST{
  AST *lptr;
  AST *rptr;
  public:
    Sew_AST(AST *lptr,AST *rptr);
    virtual void printtree();  
    virtual Quilt solve();
    virtual Gcode generate_cpp();

};

class A_AST:public AST{
  public:
    virtual void printtree();
    virtual Quilt solve();
    virtual Gcode generate_cpp();

};



class B_AST:public AST{
  public:
    virtual void printtree();
    virtual Quilt solve();
    virtual Gcode generate_cpp();

};


class HdRow_AST:public AST{
   AST *ptr;
  public:
    HdRow_AST(AST *ptr); 
    virtual void printtree();
    virtual Quilt solve();
    virtual Gcode generate_cpp();
 
};


class TlRows_AST:public AST{
     AST *ptr;
  public:
    TlRows_AST(AST *ptr); 
    virtual void printtree();
    virtual Quilt solve();
    virtual Gcode generate_cpp();
 
};

class HdCol_AST:public AST{
     AST *ptr;
  public:
    HdCol_AST(AST *ptr); 
    virtual void printtree();
    virtual Quilt solve();
    virtual Gcode generate_cpp();
 
};

class TlCols_AST:public AST{
     AST *ptr;
  public:
    TlCols_AST(AST *ptr); 
    virtual void printtree();
    virtual Quilt solve();
    virtual Gcode generate_cpp();
 

};


class LET_AST:public AST{
    AST *decls;
    AST *expr;
   public:
     LET_AST(AST* decls,AST* expr);
     virtual void printtree();
     virtual Quilt solve();
     virtual Gcode generate_cpp();

};


class DECL_AST:public AST{
   AST **decls;
   int no_decl;
  public:
      DECL_AST(AST *decl);
      void Add_decl(AST *decl);
      virtual void printtree();
      virtual Quilt solve();
      virtual Gcode generate_cpp();

};

class VAL_AST:public AST{
   char *name;
   AST *expr;
 public:
    VAL_AST(char *name,AST* expr);
    virtual void printtree();
    virtual Quilt solve();
    virtual Gcode generate_cpp();

};

class FUN_AST:public AST{
  char *name;
  AST *fplist;
  AST *expr;
  public:
     FUN_AST(char *name,AST *fplist,AST *expr);
     virtual void printtree();
     virtual Quilt solve();
     virtual Gcode generate_cpp();

};

class FPARAM_AST:public AST{
     char** fplist;
     int no_fp;
  public:
      FPARAM_AST(char *name);
      void Add_param(char *name);
      virtual void printtree();
      virtual Quilt solve();
      virtual Gcode generate_cpp();


};

class CALL_FUN_AST:public AST{
     char *name;
     AST *aplist;
     int ptr;
   public:
     CALL_FUN_AST(char *name,AST *aplist,int ptr);
     virtual void printtree();
     virtual Quilt solve();
     virtual Gcode generate_cpp();


};

class CALL_VAL_AST:public AST{
     char *name;
     int ptr;
   public:
     CALL_VAL_AST(char *name,int ptr);
     virtual void printtree();
     virtual Quilt solve();
     virtual Gcode generate_cpp();


};


class CALL_PARAM_AST:public AST{
     char *name;
   public:
     CALL_PARAM_AST(char *name);
     virtual void printtree();
     virtual Quilt solve();
     virtual Gcode generate_cpp();


};


class APARAM_AST:public AST{
     AST **aplist;
     int no_ap;
  public:
     APARAM_AST(AST *expr);
     void Add_param(AST *expr);
     virtual void printtree();
     virtual Quilt solve();
     virtual Gcode generate_cpp();

};

#endif

#include <iostream>
using namespace std;

class Posicion{
    public:
        int xPosicion;
        int yPosicion;

        Posicion(int dx,int dy){
            xPosicion=dx;
            yPosicion=dy;
        }    
};

class Movable{
    public:
        virtual void setPosicion(Posicion *p)=0;
        virtual Posicion *getPosicion() const=0;
        virtual void mostrar() const=0;
};

class MoveServant{
    public:
        void moveTo(Movable *serviced,Posicion *where){
            serviced->setPosicion(where);
            serviced->mostrar();
        }
        void moveBy(Movable *serviced, int dx, int dy){
            dx += serviced->getPosicion()->xPosicion;
            dy += serviced->getPosicion()->yPosicion;
            serviced->setPosicion(new Posicion(dx,dy));
            serviced->mostrar();
        }
};

class Triangulo : public Movable{
    private:
        Posicion *p;
    public:
    
        void setPosicion(Posicion *p)override{
            this->p=p;
        }
        
        Posicion *getPosicion()const override{
            return p;
        }

        void mostrar()const override{
            cout<<"La posicion actual del triangulo es: "<<endl;
            cout<<"En x: "<<p->xPosicion<<endl;
            cout<<"En y: "<<p->yPosicion<<endl;
        }

};

class Elipse : public Movable{
    private:
        Posicion *p;
    public:
        void setPosicion(Posicion *p)override{
            this->p=p;
        }

        Posicion *getPosicion()const override{
            return this->p;
        }

        void mostrar()const override{
            cout<<"La posicion actual del elipse es: "<<endl;
            cout<<"En x: "<<p->xPosicion<<endl;
            cout<<"En y: "<<p->yPosicion<<endl;
        }
};

class Rectangulo : public Movable{
    private:
        Posicion *p;
    public:
        void setPosicion(Posicion *p)override{
            this->p=p;
        }

        Posicion *getPosicion()const override{
            return this->p;
        }

        void mostrar()const override{
            cout<<"La posicion actual del rectangulo es: "<<endl;
            cout<<"En x: "<<p->xPosicion<<endl;
            cout<<"En y: "<<p->yPosicion<<endl;
        }
};


int main(){
    Posicion* puntoA=new Posicion(5,7);
    Posicion* puntoB=new Posicion(20,5);
    Posicion* puntoC=new Posicion(100,700);
    Triangulo* triangulo= new Triangulo(); 
    Rectangulo* rectangulo=new Rectangulo();
    Elipse* elipse= new Elipse();
    //nuestro servidor
    MoveServant* mover= new MoveServant();
    cout<<"Usando moveTo"<<endl;
    cout<<"Se asigna una posicion inicial a las figuras"<<endl;
    mover->moveTo(triangulo,puntoA);
    mover->moveTo(rectangulo,puntoA);
    mover->moveTo(elipse,puntoA);
    cout<<"-------------------------------------------------"<<endl;
    cout<<"Se modifica la posicion: "<<endl;
    mover->moveTo(triangulo,puntoB);
    mover->moveTo(rectangulo,puntoB);
    mover->moveTo(elipse,puntoB);
    cout<<"-------------------------------------------------"<<endl;
    cout<<"Usando moveBy"<<endl;
    cout<<"Se modifica la posicion: "<<endl;
    mover->moveBy(triangulo,50,30);
    mover->moveBy(rectangulo,50,30);
    mover->moveBy(elipse,50,30);
    cout<<"-------------------------------------------------"<<endl;
    cout<<"Se modifica la posicion: "<<endl;
    mover->moveBy(triangulo,10,60);
    mover->moveBy(rectangulo,10,60);
    mover->moveBy(elipse,10,60);
    delete puntoA;
    delete puntoB;
    delete puntoC;
    delete triangulo;
    delete rectangulo;
    delete elipse;
    return 0;

}

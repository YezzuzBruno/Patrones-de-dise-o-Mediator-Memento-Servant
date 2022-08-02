#include <iostream>
#include <string>
using namespace std;
/**
 * La interfaz Mediator declara un método utilizado por los componentes para 
 * notificar al mediador sobre varios eventos. El Mediador puede reaccionar 
 * a estos eventos y pasar la ejecución a otros componentes.
 */
class BaseComponent;
class Mediator {
    public:
      //se envia el emisor y el evento
      virtual void Notify(BaseComponent *sender, string event) const = 0;
};

/**
 * El componente base proporciona la funcionalidad básica de almacenar la 
 * instancia de un mediador dentro de los objetos del componente.
 */
class BaseComponent {
    protected:
        Mediator *mediator_;

    public:
        BaseComponent(Mediator *mediator = nullptr) : mediator_(mediator) {
        }
        void set_mediator(Mediator *mediator) {
            this->mediator_ = mediator;
        }
};

/**
 * Los componentes concretos implementan varias funciones. No dependen de
otros componentes. Tampoco dependen de ninguna clase mediadora concreta.
 */
class Component1 : public BaseComponent {
    public:
      void DoA() {
        cout << "El componente 1 hace A\n";
        this->mediator_->Notify(this, "A");
      }
      void DoB() {
        cout << "El componente 1 hace B.\n";
        this->mediator_->Notify(this, "B");
      }
};

class Component2 : public BaseComponent {
    public:
      void DoC() {
          cout << "El componente 2 hace C.\n";
          this->mediator_->Notify(this, "C");
      }
      void DoD() {
          cout << "El componente 2 hace D.\n";
          this->mediator_->Notify(this, "D");
      }
};

/**
 * Los Mediadores Concretos implementan el comportamiento cooperativo coordinando varios componentes.
 */
class ConcreteMediator : public Mediator {
    private:
      Component1 *component1_;
      Component2 *component2_;

    public:
      ConcreteMediator(Component1 *c1, Component2 *c2) : component1_(c1), component2_(c2) {
          this->component1_->set_mediator(this);
          this->component2_->set_mediator(this);
      }
      //se envia el emisor y el evento
      void Notify(BaseComponent *sender, string event) const override {
          if (event == "A") {
            cout << "El mediador reacciona en A y desencadena las siguientes operaciones:\n";
            this->component2_->DoC();
          }
          if (event == "D") {
            cout << "El mediador reacciona en D y desencadena las siguientes operaciones:\n";
            this->component1_->DoB();
            this->component2_->DoC();
          }
      }
};

/**
 * The client code.
 */

void ClientCode() {
    Component1 *c1 = new Component1;
    Component2 *c2 = new Component2;
    ConcreteMediator *mediator = new ConcreteMediator(c1, c2);
    cout << "El cliente activa la operacion A.\n";
    c1->DoA();
    cout << "\n";
    cout << "El cliente activa la operacion D.\n";
    c2->DoD();

    delete c1;
    delete c2;
    delete mediator;
}

int main() {
  ClientCode();
  return 0;
}
#include <iostream>
#include <ctime>
#include <vector>
using namespace std;
/*
 La interfaz Memento proporciona una forma de recuperar los metadatos del recuerdo, 
 como la fecha de creación o el nombre. Sin embargo, no expone el estado del originador.
 */
//recuerdo
class Memento {
    public:
        virtual string GetName() const = 0;
        virtual string date() const = 0;
        virtual string state() const = 0;
};

/*
 El Concrete Memento contiene la infraestructura para almacenar el estado del originador.
 */
class ConcreteMemento : public Memento {
    private:
        string state_;
        string date_;

    public:
        ConcreteMemento(string state) : state_(state) {
            this->state_ = state;
            time_t now = time(0);
            this->date_ = ctime(&now);
        }
    /**
     * The Originator uses this method when restoring its state.
     */
        string state() const override {
            return this->state_;
        }
    /**
     * El resto de los métodos son utilizados por Caretaker para mostrar metadatos.
     */
        string GetName() const override {
            return this->date_ + " / (" + this->state_.substr(0, 9) + "...)";
        }
        string date() const override {
            return this->date_;
        }
};

/**
 * El originador tiene un estado importante que puede cambiar con el tiempo. 
 * También define un método para guardar el estado dentro de un recuerdo y 
 * otro método para restaurar el estado desde él.
 */

//originador de contraseñas(ejemplo)
class Originador {
  /**
   * @var string En aras de la simplicidad, el estado del originador se almacena 
   * dentro de una sola variable.
   */
    private:
        string state_;

        string GenerateRandomString(int length= 10) {
            const char alphanum[] = "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
            int stringLength = sizeof(alphanum) - 1;

            string random_string;
            for (int i = 0; i < length; i++) {
                random_string += alphanum[rand() % stringLength];
            }
            return random_string;
        }

    public:
        Originador(string state) : state_(state) {
            cout << "Originador: Mi estado inicial es: " << this->state_ << "\n";
        }
        /*
        La lógica comercial del Originador puede afectar su estado interno. 
        Por lo tanto, el cliente debe realizar una copia de seguridad del estado 
        antes de iniciar los métodos de la lógica empresarial a través del método save().
        */

        //hacer algo (un cambio)
        void DoSomething() {
            cout << "Originador: Estoy haciendo algo importante(un cambio).\n";
            this->state_ = this->GenerateRandomString(30);
            cout << "Originador: y mi estado ha cambiado a: " << this->state_ << "\n";
        }

        /**
         * Guarda el estado actual dentro de un recuerdo.
         */
        Memento *Save() {
            return new ConcreteMemento(this->state_);
        }
        /**
         * Restaura el estado del Creador a partir de un objeto de recuerdo.
         */
        void Restore(Memento *memento) {
            this->state_ = memento->state();
            cout << "Originador: Mi estado ha cambiado a: " << this->state_ << "\n";
        }
};

/**
 * El Cuidador no depende de la clase Concrete Memento. Por lo tanto, 
 * no tiene acceso al estado del originador, almacenado dentro del memento. 
 * Funciona con todos los recuerdos a través de la interfaz base de Memento.
 */
class Cuidador {
  
    private:
        vector<Memento *> mementos_;
        Originador *originator_;

    public:
        Cuidador(Originador *originator) : originator_(originator) {
            this->originator_ = originator;
        }
        //copia de seguridad
        void Backup() {
            cout << "\nCuidador: Guardando el estado del originador(copia de seguridad)...\n";
            this->mementos_.push_back(this->originator_->Save());
        }
        void Deshacer() {
            if (!this->mementos_.size()) {
                return;
            }
            Memento *memento = this->mementos_.back();
            this->mementos_.pop_back();
            cout << "Cuidador: Restaurando el estado a " << memento->GetName() << "\n";
            try {
                this->originator_->Restore(memento);
            } catch (...) {
                this->Deshacer();
            }
        }
        //mostrar el historial de cambios
        void ShowHistory() const {
            cout << "Cuidador: Aqui esta la lista de recuerdos:\n";
            for (Memento *memento : this->mementos_) {
                cout << memento->GetName() << "\n";
            }
        }
};
/**
 * Client code.
 */

void ClientCode() {
    //creando un estado inicial o version inicial
    Originador *originator = new Originador("123456789");
    Cuidador *caretaker = new Cuidador(originator);
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    caretaker->Backup();
    originator->DoSomething();
    cout << "\n";
    caretaker->ShowHistory();
    cout << "\nCliente: Ahora, ¡retrocedamos!\n\n";
    caretaker->Deshacer();
    cout << "\nCliente: Una vez mas!\n\n";
    caretaker->Deshacer();

    delete originator;
    delete caretaker;
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    ClientCode();
    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

class Animal {
    protected:
    int edad;
    string nombre;
    string raza;
public:
    Animal(string nombre, int edad, string raza) : nombre(nombre), edad(edad), raza(raza) {}
    virtual ~Animal() = default;
    virtual void mostrarInfo() const = 0;
    virtual string getTipo() const = 0;
    string getNombre() const {return nombre;};
    int getEdad() const {return edad;};
    string getRaza() const {return raza;};
};

class Perro : public Animal {
    public:
    Perro(string nombre, int edad, string raza) : Animal(nombre, edad, raza){}

    void mostrarInfo() const override {
        cout << "Perro:" << endl;
        cout << "Nombre: " << nombre <<endl;
        cout << "Edad: " << edad << endl;
        cout << "Raza: " << raza << endl;
    }
    string getTipo() const override {return "Perro";};
};

class Gato : public Animal {
    public:
    Gato(string nombre, int edad, string raza) : Animal(nombre, edad, raza){}

    void mostrarInfo() const override {
        cout << "Gato:" << endl;
        cout << "Nombre: " << getNombre() << endl;
        cout << "Edad: " << getEdad() << endl;
        cout << "Raza: " << getRaza() << endl;
    }
    string getTipo() const override {return "Gato";};
};

class HistorialClinico {
    vector<string> registros;
    public:
    void agregarEntrada(const string& entrada) {
        registros.push_back(entrada);
    }
    void mostrarHistorial() const {
        if (registros.empty()) {
            cout << "No hay historial clínico" << "\n" << endl;
            return;
        }
        cout << "Historial:" << endl;
        for (const auto& entrada : registros) {
            cout << entrada << "\n" << endl;
        }
    }
};

class Paciente {
    unique_ptr<Animal> animal;
    HistorialClinico historial;
    public:
    Paciente(Animal*a) : animal(a) {}
    void agregarRegistro(const string& texto) {
        historial.agregarEntrada(texto);
    }
    void mostrarHistorial() const {
        animal->mostrarInfo();
        historial.mostrarHistorial();
    }
    string nombreAnimal() const {return animal->getNombre();};
};

class Veterinaria {
    vector<Paciente> pacientes;
    public:
    void agregarPaciente(Animal*a) {
        pacientes.emplace_back(a);
    }
    void mostrarPacientes() const {
        if (pacientes.empty()) {
            cout << "No hay pacientes" << endl;
            return;
        }
        cout << "Pacientes:" << endl;
        for (const auto& p : pacientes) {
            p.mostrarHistorial();
        }
    }
    void registrarConsulta(const string& nombre, const string& texto) {
        for (auto& p : pacientes) {
            if (p.nombreAnimal() == nombre) {
                p.agregarRegistro(texto);
                return;
            }
        }
        cout << "Animal no encontrado: " << nombre << endl;
    }
    void registrarPaciente() {
        string nombre;
        int edad;
        string tipo;
        string raza;
        cout << "Ingrese el nombre del paciente:" << endl;
        cin.ignore();
        getline(cin, nombre);
        cout << "Ingrese la edad del paciente:" << endl;
        cin >> edad;
        cout << "Ingrese el tipo del paciente (Gato/Perro):" << endl;
        cin >> tipo;
        cout << "Ingrese el raza del paciente:" << endl;
        cin.ignore();
        getline(cin, raza);
        Animal*a = nullptr;
        if (tipo == "Gato")
            a = new Gato(nombre, edad, raza);
        else if (tipo == "Perro")
            a = new Perro(nombre, edad, raza);
        else {
            cout << "Tipo de animal invalido" << endl;
            return;
        }
        agregarPaciente(a);
        cout << "Paciente agregado." << endl;
    }
};

int main() {
    Veterinaria vet;
    int opcion;
    while (true) {
        cout << "Ingrese una opcion:" << endl;
        cout << "1) Agregar pacientes" << endl;
        cout << "2) Mostrar pacientes" << endl;
        cout << "3) Registrar consulta" << endl;
        cout << "4) Salir " << endl;
        cin >> opcion;
        switch (opcion) {
            case 1:
                vet.registrarPaciente();
                break;
            case 2:
                vet.mostrarPacientes();
                break;
            case 3: {
                string nombre;
                string texto;
                cout << "Ingrese el nombre del paciente:" << endl;
                cin >> nombre;
                cout << "Consulta: " << endl;
                cin.ignore();
                getline(cin, texto);
                vet.registrarConsulta(nombre, texto);
                break;
            }
            case 4:
                cout << "Saliendo del programa" << endl;
                return 0;
            default:
                cout << "Opcion invalida, intente de nuevo" << endl;
        }
    }
}

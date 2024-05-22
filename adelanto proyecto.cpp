#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

enum MedioPublicidad { TV, RADIO, INTERNET };

class Candidato {
public:
    Candidato(const string& nombre, int edad, const string& partidoPolitico)
        : nombre_(nombre), edad_(edad), partidoPolitico_(partidoPolitico), costoCampania_(0), votosObtenidos_(0), porcentajeVotos_(0) {}

    void mostrarInfo() const {
        cout << "Nombre: " << nombre_ << endl;
        cout << "Edad: " << edad_ << endl;
        cout << "Partido Politico: " << partidoPolitico_ << endl;
        cout << "Costo de Campaña: $" << costoCampania_ << endl;
        cout << "Votos Obtenidos: " << votosObtenidos_ << endl;
        cout << "Porcentaje de Votos: " << porcentajeVotos_ << "%" << endl;
    }

    void votarCandidato(MedioPublicidad medio, int& totalVotos) {
        votosObtenidos_++;
        totalVotos++;

        switch (medio) {
            case TV:
                costoCampania_ += 1000;
                break;
            case RADIO:
                costoCampania_ += 500;
                break;
            case INTERNET:
                costoCampania_ += 100;
                break;
        }

        calcularPorcentajeVotos(totalVotos);
    }

    void calcularPorcentajeVotos(int totalVotos) {
        if (totalVotos > 0) {
            porcentajeVotos_ = static_cast<double>(votosObtenidos_) / totalVotos * 100;
        } else {
            porcentajeVotos_ = 0;
        }
    }

    void vaciarDatos() {
        votosObtenidos_ = 0;
        costoCampania_ = 0;
        porcentajeVotos_ = 0;
    }

    double getCostoCampania() const {
        return costoCampania_;
    }

private:
    string nombre_;
    int edad_;
    string partidoPolitico_;
    double costoCampania_;
    int votosObtenidos_;
    double porcentajeVotos_;
};

class GestorElecciones {
public:
    void agregarCandidato(const string& nombre, int edad, const string& partidoPolitico) {
        candidatos_.emplace_back(nombre, edad, partidoPolitico);
    }

    void mostrarCandidatos() const {
        for (int i = 0; i < candidatos_.size(); i++) {
            cout << "Candidato " << i + 1 << ":" << endl;
            candidatos_[i].mostrarInfo();
            cout << endl;
        }
    }

    void votarCandidato(int index, MedioPublicidad medio) {
        candidatos_[index].votarCandidato(medio, totalVotos_);
    }

    int calcularTotalVotos() const {
        return totalVotos_;
    }

    double calcularCostoPromedioCampania() const {
        double totalCostos = 0;
        for (const Candidato& c : candidatos_) {
            totalCostos += c.getCostoCampania();
        }
        return totalCostos / candidatos_.size();
    }

    void vaciarUrna() {
        for (Candidato& c : candidatos_) {
            c.vaciarDatos();
        }
        totalVotos_ = 0;
    }

private:
    vector<Candidato> candidatos_;
    int totalVotos_ = 0;
};

int main() {
    GestorElecciones gestor;

    // Agregar candidatos
    gestor.agregarCandidato("Juan Perez", 45, "Partido Azul");
    gestor.agregarCandidato("Maria Garcia", 38, "Partido Verde");
    gestor.agregarCandidato("Pedro Rodriguez", 52, "Partido Rojo");

    // Simular algunas votaciones
    gestor.votarCandidato(0, TV);
    gestor.votarCandidato(1, RADIO);
    gestor.votarCandidato(2, INTERNET);
    gestor.votarCandidato(0, TV);
    gestor.votarCandidato(1, INTERNET);
    gestor.votarCandidato(2, RADIO);

    // Mostrar informacion de candidatos
    cout << "Informacion de Candidatos:" << endl;
    gestor.mostrarCandidatos();

    // Mostrar estadisticas
    cout << "Total de Votos: " << gestor.calcularTotalVotos() << endl;
    cout << "Costo Promedio de Campaña: $" << gestor.calcularCostoPromedioCampania() << endl;

    // Vaciar urna
    gestor.vaciarUrna();

    return 0;
}
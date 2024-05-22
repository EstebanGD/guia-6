#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm> 

struct Recurso {
    std::string codigo;
    std::string nombre;
    bool disponible;
};

struct Estudiante {
    std::string codigo;
    std::string nombre;
};

struct Prestamo {
    Recurso* recurso;
    Estudiante* estudiante;
};

std::vector<Recurso> recursos;
std::unordered_map<std::string, Estudiante> estudiantes;
std::vector<Prestamo> prestamos;

void agregarRecurso(const std::string& codigo, const std::string& nombre) {
    Recurso nuevoRecurso = {codigo, nombre, true};
    recursos.push_back(nuevoRecurso);
    std::cout << "Recurso agregado: " << codigo << " - " << nombre << std::endl;
}

void agregarEstudiante(const std::string& codigo, const std::string& nombre) {
    Estudiante nuevoEstudiante = {codigo, nombre};
    estudiantes[codigo] = nuevoEstudiante;
    std::cout << "Estudiante agregado: " << codigo << " - " << nombre << std::endl;
}

void prestarRecurso(const std::string& codigoRecurso, const std::string& codigoEstudiante) {
    auto it = std::find_if(recursos.begin(), recursos.end(), [&](const Recurso& r) {
        return r.codigo == codigoRecurso && r.disponible;
    });

    if (it != recursos.end() && estudiantes.count(codigoEstudiante)) {
        it->disponible = false;
        Prestamo nuevoPrestamo = {&(*it), &estudiantes[codigoEstudiante]};
        prestamos.push_back(nuevoPrestamo);
        std::cout << "Recurso prestado: " << codigoRecurso << " a " << codigoEstudiante << std::endl;
    } else {
        std::cout << "No se pudo realizar el préstamo." << std::endl;
    }
}

void consultarPrestamosEstudiante(const std::string& codigoEstudiante) {
    std::cout << "Préstamos del estudiante " << codigoEstudiante << ":" << std::endl;
    for (const Prestamo& p : prestamos) {
        if (p.estudiante->codigo == codigoEstudiante) {
            std::cout << "- " << p.recurso->codigo << " - " << p.recurso->nombre << std::endl;
        }
    }
}

void consultarPrestamo(const std::string& codigoRecurso, const std::string& codigoEstudiante) {
    for (const Prestamo& p : prestamos) {
        if (p.recurso->codigo == codigoRecurso && p.estudiante->codigo == codigoEstudiante) {
            std::cout << "Préstamo: " << std::endl;
            std::cout << "Recurso: " << p.recurso->codigo << " - " << p.recurso->nombre << std::endl;
            std::cout << "Estudiante: " << p.estudiante->codigo << " - " << p.estudiante->nombre << std::endl;
            return;
        }
    }
    std::cout << "No se encontró el préstamo." << std::endl;
}

void devolverRecurso(const std::string& codigoRecurso, const std::string& codigoEstudiante) {
    auto it = std::find_if(prestamos.begin(), prestamos.end(), [&](const Prestamo& p) {
        return p.recurso->codigo == codigoRecurso && p.estudiante->codigo == codigoEstudiante;
    });

    if (it != prestamos.end()) {
        it->recurso->disponible = true;
        prestamos.erase(it);
        std::cout << "Recurso devuelto: " << codigoRecurso << " por " << codigoEstudiante << std::endl;
    } else {
        std::cout << "No se encontró el préstamo." << std::endl;
    }
}

int main() {
    agregarRecurso("R001", "Libro de programación");
    agregarRecurso("R002", "Proyector");
    agregarRecurso("R003", "Laptop");
    agregarEstudiante("E001", "Juan Pérez");
    agregarEstudiante("E002", "María García");

    prestarRecurso("R001", "E001");

    consultarPrestamosEstudiante("E001");

    consultarPrestamo("R001", "E001");

    devolverRecurso("R001", "E001");

    return 0;
}
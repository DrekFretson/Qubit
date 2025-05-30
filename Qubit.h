#ifndef QUBIT_H
#define QUBIT_H

#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <cassert>

using namespace std;
using Complex = complex<double>;
using Matrix = vector<vector<Complex>>;


class Qubit {
private:
    Complex alpha; // |0>
    Complex beta;  // |1>


    bool isNormalized(double tolerance = 1e-6) const {
        return abs(norm() - 1.0) < tolerance;
    }


    double norm() const {
        return sqrt(abs(alpha) * abs(alpha) + abs(beta) * abs(beta));
    }

public:
    Qubit(Complex a, Complex b) : alpha(a), beta(b) {
        if (!isNormalized()) {
            throw invalid_argument("Qubit state must be normalized");
        }
    }


    Complex getAlpha() const { return alpha; }
    Complex getBeta() const { return beta; }

    // Применение однокубитного гейта(матрица 2х2) к кубиту
    void applyGate(const Matrix& gate) {
        assert(gate.size() == 2 && gate[0].size() == 2 && gate[1].size() == 2 && "Gate must be a 2x2 matrix");

        Complex new_alpha = gate[0][0] * alpha + gate[0][1] * beta;
        Complex new_beta = gate[1][0] * alpha + gate[1][1] * beta;

        alpha = new_alpha;
        beta = new_beta;


        assert(isNormalized() && "Gate operation broke normalization");
    }


    void printState() const {
        cout << "State: " << alpha << " |0> + " << beta << " |1>" << endl;
    }
};



namespace PauliGates {
    const Matrix X = { {0, 1}, {1, 0} }; //NOT
    const Matrix Y = { {0, Complex(0, -1)}, {Complex(0, 1), 0} }; //гиперболический поворот
    const Matrix Z = { {1, 0}, {0, -1} }; //фазовый сдвиг
}




class TwoQubitSystem {
private:
    vector<Qubit> qubits;

public:
    TwoQubitSystem(const Qubit& q1, const Qubit& q2) : qubits{ q1, q2 } {}

    void applyCNOT() {
        if (qubits[0].getBeta().real() == 1) {
            qubits[1].applyGate(PauliGates::X);
        }
    }

    void printState() const {
        cout << "Two-qubit system state:" << endl;
        for (const auto& qubit : qubits) {
            qubit.printState();
        }
    }
};


#endif

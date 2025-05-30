#include "Qubit.h"


int main() {
    setlocale(LC_ALL, "Rus");
    try {
        // Создаем кубит в состоянии |0>
        Qubit q0(0.0, 1.0);
        Qubit q1 = q0;
        cout << "Начальное состояние:" << endl;
        q1.printState();

        // Применяем гейт X (аналог классического NOT)
        q1.applyGate(PauliGates::X);
        cout << "\nПосле применения X-гейта:" << endl;
        q1.printState();
        q1 = q0;

        // Применяем гейт Y
        q1.applyGate(PauliGates::Y);
        cout << "\nПосле применения Y-гейта:" << endl;
        q1.printState();
        q1 = q0;

        // Применяем гейт Z
        q1.applyGate(PauliGates::Z);
        cout << "\nПосле применения Z-гейта:" << endl;
        q1.printState();
        q1 = q0;

        // Создаем систему из двух кубитов
        Qubit q2(1.0 / sqrt(2), -1.0 / sqrt(2)); // Состояние |+>
        TwoQubitSystem system(q1, q2);
        cout << "\nНачальное состояние двухкубитной системы:" << endl;
        system.printState();

        // Применяем CNOT (первый кубит - управляющий, второй - целевой)
        system.applyCNOT();
        cout << "\nПосле применения CNOT-гейта:" << endl;
        system.printState();
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}

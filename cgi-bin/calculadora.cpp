#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>  // Para std::setprecision
using namespace std;

int main() {
    // Obtener la cadena de consulta
    const char* query_string = getenv("QUERY_STRING");
    
    // Inicializar variables como double para soportar decimales
    double num1 = 0.0, num2 = 0.0;
    char operacion[20] = "";  // Para guardar la operación

    if (query_string != nullptr) {
        // Parsear los parámetros
        char* param = strdup(query_string);  // Hacer una copia de la cadena de consulta
        char* token = strtok(param, "&");    // Separar los parámetros
        while (token != nullptr) {
            if (sscanf(token, "num1=%lf", &num1) == 1) { /* Se ha encontrado num1 */ } 
            else if (sscanf(token, "num2=%lf", &num2) == 1) { /* Se ha encontrado num2 */ }
            else if (sscanf(token, "operacion=%s", operacion) == 1) { /* Se ha encontrado la operación */ }
            token = strtok(nullptr, "&"); // Continuar con el siguiente parámetro
        }
        free(param);  // Liberar la memoria
    }

    // Realizar la operación
    double resultado = 0.0;
    if (strcmp(operacion, "sumar") == 0) {
        resultado = num1 + num2;
    } else if (strcmp(operacion, "restar") == 0) {
        resultado = num1 - num2;
    } else if (strcmp(operacion, "multiplicar") == 0) {
        resultado = num1 * num2;
    } else if (strcmp(operacion, "dividir") == 0) {
        if (num2 != 0) {
            resultado = num1 / num2;
        } else {
            cout << "Content-Type: text/plain\n\n";
            cout << "Error: No se puede dividir entre cero";
            return 0;
        }
    } else {
        cout << "Content-Type: text/plain\n\n";
        cout << "Error: Operación no válida";
        return 0;
    }

    // Generar la respuesta HTTP con el resultado formateado a 2 decimales
    cout << "Content-Type: text/plain\n\n";
    cout << fixed << setprecision(2) << resultado;

    return 0;
}

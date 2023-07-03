#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>    // Para funções matemáticas
#include <cstdlib>  // Para geração de números aleatórios
#include <limits>   // Para limites numéricos
#include <memory>   // Para gerenciamento de memória

// Usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants
const double infinity = std::numeric_limits<double>::infinity();  // Infinito
const double pi = 3.1415926535897932385;  // Valor de pi

// Utility Functions

// Converte graus para radianos
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// Limita um valor dentro de um intervalo especificado
inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// Gera um número aleatório no intervalo [0,1)
inline double random_double() {
    return rand() / (RAND_MAX + 1.0);
}

// Gera um número aleatório no intervalo [min,max)
inline double random_double(double min, double max) {
    return min + (max - min) * random_double();
}

// Gera um número inteiro aleatório no intervalo [min,max]
inline int random_int(int min, int max) {
    return static_cast<int>(random_double(min, max + 1));
}

// Common Headers

#include "ray.h"  // Cabeçalho para a classe ray
#include "vec3.h" // Cabeçalho para a classe vec3

#endif

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
    ray() {} // Construtor padrão vazio

    // Construtor que inicializa o raio com uma origem e direção
    ray(const point3& origin, const vec3& direction)
        : orig(origin), dir(direction), tm(0)
    {}

    // Construtor que inicializa o raio com uma origem, direção e tempo
    ray(const point3& origin, const vec3& direction, double time)
        : orig(origin), dir(direction), tm(time)
    {}

    // Função que retorna a origem do raio
    point3 origin() const {
        return orig;
    }

    // Função que retorna a direção do raio
    vec3 direction() const {
        return dir;
    }

    // Função que retorna o tempo do raio
    double time() const {
        return tm;
    }

    // Função que retorna o ponto ao longo do raio em uma distância t
    point3 at(double t) const {
        return orig + t * dir;
    }

public:
    point3 orig; // Origem do raio
    vec3 dir;    // Direção do raio
    double tm;   // Tempo do raio
};

#endif

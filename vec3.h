#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;
using std::fabs;

class vec3 {
public:
    vec3() : e{0,0,0} {}  // Construtor padrão que inicializa o vetor com (0,0,0)
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}  // Construtor que permite definir as coordenadas x, y e z do vetor

    double x() const { return e[0]; }  // Retorna a coordenada x do vetor
    double y() const { return e[1]; }  // Retorna a coordenada y do vetor
    double z() const { return e[2]; }  // Retorna a coordenada z do vetor

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }  // Operador unário de negação, retorna o vetor com suas coordenadas negativas
    double operator[](int i) const { return e[i]; }  // Permite acessar as coordenadas do vetor como um array constante
    double& operator[](int i) { return e[i]; }  // Permite acessar as coordenadas do vetor como um array

    vec3& operator+=(const vec3 &v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(const double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(const double t) {
        return *this *= 1/t;
    }

    double length() const {
        return sqrt(length_squared());
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    bool near_zero() const {
        // Retorna true se o vetor estiver próximo de zero em todas as dimensões.
        const auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

    // Funções estáticas para gerar vetores aleatórios
    inline static vec3 random() {
        return vec3(random_double(), random_double(), random_double());
    }

    inline static vec3 random(double min, double max) {
        return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
    }

public:
    double e[3];  // Coordenadas do vetor
};

// Tipos de alias para vec3
using point3 = vec3;   // Ponto 3D
using color = vec3;    // Cor RGB

// Funções utilitárias para vec3

// Operador de saída para vec3
inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// Operadores aritméticos com vetores
inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

// Produto escalar entre dois vetores
inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

// Produto vetorial entre dois vetores
inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// Retorna o vetor unitário de um vetor
inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

// Gera um ponto aleatório dentro do disco unitário
inline vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

// Gera um vetor aleatório dentro da esfera unitária
inline vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

// Gera um vetor aleatório unitário
inline vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

// Gera um vetor aleatório na hemisfério com base na normal
inline vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0)  // No mesmo hemisfério que a normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

// Reflete um vetor em relação a uma normal
inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;
}

// Refrata um vetor com base na normal e no índice de refração
inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

#endif

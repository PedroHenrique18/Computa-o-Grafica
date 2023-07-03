#ifndef SPHERE_H
#define SPHERE_H

#include "rtweekend.h"  // Inclui o cabeçalho "rtweekend.h"

#include "hittable.h"  // Inclui o cabeçalho "hittable.h"

class sphere : public hittable {
public:
    sphere() {}  // Construtor padrão

    // Construtor da esfera com centro, raio e material
    sphere(point3 cen, double r, shared_ptr<material> m)
        : center(cen), radius(r), mat_ptr(m) {};

    // Implementação da função de interseção da esfera
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

public:
    point3 center;  // Centro da esfera
    double radius;  // Raio da esfera
    shared_ptr<material> mat_ptr;  // Ponteiro para o material da esfera
};

// Implementação da função de interseção da esfera
bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;  // Vetor entre a origem do raio e o centro da esfera
    auto a = r.direction().length_squared();  // Coeficiente a da equação de interseção
    auto half_b = dot(oc, r.direction());  // Coeficiente b/2 da equação de interseção
    auto c = oc.length_squared() - radius * radius;  // Coeficiente c da equação de interseção

    auto discriminant = half_b * half_b - a * c;  // Discriminante da equação de interseção
    if (discriminant < 0) return false;  // Se o discriminante for negativo, não há interseção

    auto sqrtd = sqrt(discriminant);  // Raiz quadrada do discriminante

    // Encontra a raiz mais próxima que está dentro do intervalo aceitável
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;  // Parâmetro t da interseção
    rec.p = r.at(rec.t);  // Ponto de interseção
    vec3 outward_normal = (rec.p - center) / radius;  // Vetor normal à superfície da esfera
    rec.set_face_normal(r, outward_normal);  // Define o sentido normal da superfície com base no raio e no vetor normal
    rec.mat_ptr = mat_ptr;  // Define o material da esfera para o registro de interseção

    return true;  // Há interseção
}

#endif

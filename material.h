#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"

// Declaração antecipada da estrutura hit_record
struct hit_record;

// Classe abstrata para materiais
class material {
public:
    // Função virtual pura para calcular a dispersão dos raios
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const = 0;
};

// Classe para materiais lambertianos (difusos)
class lambertian : public material {
public:
    color albedo; // Albedo do material

    // Construtor que recebe o albedo como parâmetro
    lambertian(const color& a) : albedo(a) {}

    // Implementação da função de dispersão para materiais lambertianos
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const override {
        // Calcula uma direção aleatória para dispersão
        auto scatter_direction = rec.normal + random_unit_vector();

        // Verifica se a direção de dispersão é degenerada (perto de zero)
        // Caso seja degenerada, usa a normal como direção de dispersão
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        // Define o raio dispersado com a nova direção e o ponto de origem
        scattered = ray(rec.p, scatter_direction);
        // Define a atenuação como o albedo do material
        attenuation = albedo;

        return true; // Sempre retorna true, indicando que houve dispersão
    }
};

// Classe para materiais metálicos
class metal : public material {
public:
    color albedo; // Albedo do material
    double fuzz;  // Fuzziness do material

    // Construtor que recebe o albedo e a fuzziness como parâmetros
    metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    // Implementação da função de dispersão para materiais metálicos
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const override {
        // Calcula a reflexão do raio de entrada na superfície metálica
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);

        // Define o raio dispersado com a reflexão e um deslocamento aleatório
        scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        // Define a atenuação como o albedo do material
        attenuation = albedo;

        // Verifica se o raio dispersado está na mesma direção da normal da superfície
        // Se estiver, significa que o raio foi refletido e retorna true
        // Caso contrário, retorna false (o raio foi absorvido pela superfície)
        return (dot(scattered.direction(), rec.normal) > 0);
    }
};

// Classe para materiais dielétricos (vidros)
class dielectric : public material {
public:
    double ir; // Índice de refração do material

    // Construtor que recebe o índice de refração como parâmetro
    dielectric(double index_of_refraction) : ir(index_of_refraction) {}

    // Implementação da função de dispersão para materiais dielétricos
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
    ) const override {
        attenuation = color(1.0, 1.0, 1.0);
        double refraction_ratio = rec.front_face ? (1.0 / ir) : ir;

        vec3 unit_direction = unit_vector(r_in.direction());
        double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        vec3 direction;

        if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
            direction = reflect(unit_direction, rec.normal);
        else
            direction = refract(unit_direction, rec.normal, refraction_ratio);

        // Define o raio dispersado com a direção calculada
        scattered = ray(rec.p, direction);
        return true; // Sempre retorna true, indicando que houve dispersão
    }

private:
    // Função estática para calcular a reflectância usando a aproximação de Schlick
    static double reflectance(double cosine, double ref_idx) {
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};

#endif

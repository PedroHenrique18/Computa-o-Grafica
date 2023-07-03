#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"        // Inclui o cabeçalho "ray.h" para a definição de 'ray' usada no arquivo.
#include "rtweekend.h"  // Inclui o cabeçalho "rtweekend.h" para outras definições utilizadas.

class material; // Declaração antecipada (forward declaration) da classe "material" para evitar referências circulares.

// Estrutura para armazenar informações sobre uma interseção com um objeto hittable.
struct hit_record {
    point3 p;                    // Ponto de interseção 3D
    vec3 normal;                 // Vetor normal na interseção
    shared_ptr<material> mat_ptr; // Ponteiro compartilhado para o material do objeto na interseção
    double t;                    // Parâmetro 't' do raio onde ocorreu a interseção
    bool front_face;             // Indica se o raio atingiu a frente (true) ou a parte de trás (false) do objeto

    // Função para definir a normal do objeto com base na direção do raio e na normal externa.
    // Também determina se o raio atingiu a frente ou a parte de trás do objeto.
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

// Classe abstrata base para objetos hittables.
class hittable {
public:
    // Método virtual puro para calcular a interseção entre um raio e o objeto.
    // Retorna true se o raio atingiu o objeto e preenche o registro de interseção 'rec',
    // com as informações relevantes sobre o ponto de interseção.
    // t_min e t_max especificam o intervalo válido de parâmetros 't' do raio.
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif

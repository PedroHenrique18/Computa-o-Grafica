#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"  // Inclui o cabeçalho "rtweekend.h" para outras definições utilizadas.

class camera {
public:
    // Construtor padrão da câmera
    camera() : camera(point3(0,0,-1), point3(0,0,0), vec3(0,1,0), 40, 1, 0, 10) {}

    // Construtor da câmera com parâmetros personalizados
    camera(
        point3 lookfrom,
        point3 lookat,
        vec3   vup,
        double vfov,              // Campo de visão vertical em graus
        double aspect_ratio,
        double aperture,
        double focus_dist,
        double _time0 = 0,
        double _time1 = 0
    ) {
        auto theta = degrees_to_radians(vfov);                         // Converte o campo de visão vertical de graus para radianos
        auto h = tan(theta/2);                                         // Metade da altura do viewport
        auto viewport_height = 2.0 * h;                                // Altura do viewport
        auto viewport_width = aspect_ratio * viewport_height;          // Largura do viewport

        w = unit_vector(lookfrom - lookat);                            // Vetor que aponta para trás (da câmera para o alvo)
        u = unit_vector(cross(vup, w));                                // Vetor unitário que aponta para a direção horizontal
        v = cross(w, u);                                               // Vetor unitário que aponta para a direção vertical

        origin = lookfrom;                                             // Posição da câmera
        horizontal = focus_dist * viewport_width * u;                  // Vetor horizontal do viewport
        vertical = focus_dist * viewport_height * v;                   // Vetor vertical do viewport
        lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist*w;  // Canto inferior esquerdo do viewport

        lens_radius = aperture / 2;                                    // Raio da lente
        time0 = _time0;                                                // Tempo inicial do obturador
        time1 = _time1;                                                // Tempo final do obturador
    }

    // Método para obter um raio primário da câmera
    ray get_ray(double s, double t) const {
        vec3 rd = lens_radius * random_in_unit_disk();                 // Desvio aleatório na lente
        vec3 offset = u * rd.x() + v * rd.y();                         // Vetor de deslocamento para desfocar a imagem
        return ray(
            origin + offset,                                           // Origem do raio é deslocada pela posição da lente
            lower_left_corner + s*horizontal + t*vertical - origin - offset,  // Direção do raio é calculada com base no viewport e deslocada pela posição da lente
            random_double(time0, time1)                                // Tempo aleatório do raio para simulação de motion blur
        );
    }

private:
    point3 origin;                 // Posição da câmera
    point3 lower_left_corner;       // Canto inferior esquerdo do viewport
    vec3 horizontal;                // Vetor horizontal do viewport
    vec3 vertical;                  // Vetor vertical do viewport
    vec3 u, v, w;                   // Vetores de base da câmera
    double lens_radius;             // Raio da lente
    double time0, time1;            // Tempos de abertura/fechamento do obturador
};

#endif


//O arquivo "camera.h" define a classe "camera" que é usada para representar uma câmera no sistema de traçado de raios. A classe contém os seguintes membros de dados:

//origin: Representa a posição da câmera (ponto de onde os raios são emitidos).
//lower_left_corner: Representa o canto inferior esquerdo do retângulo da viewport da câmera.
//horizontal: Vetor que representa a extensão horizontal da viewport da câmera.
//vertical: Vetor que representa a extensão vertical da viewport da câmera.
//u, v, w: São vetores que formam uma base ortonormal para a câmera, usados para calcular a direção dos raios primários.
//lens_radius: O raio da lente da câmera, usado para simular efeitos de desfoque.
//time0, time1: Representam os tempos de abertura e fechamento do obturador da câmera, usados para simular efeitos de motion blur.
//A classe camera possui dois construtores: um construtor padrão que inicializa a câmera com valores padrão e um construtor personalizado que permite especificar os parâmetros da câmera.

//O método get_ray() retorna um raio primário da câmera para uma determinada posição (s, t) na viewport. Ele leva em consideração a posição do pixel na viewport, o deslocamento da lente (para simular o efeito de desfoque) e o tempo do obturador (para simular motion blur).

//Em resumo, o arquivo "camera.h" define a classe "camera" e fornece métodos para calcular raios primários da câmera com base nos parâmetros especificados.
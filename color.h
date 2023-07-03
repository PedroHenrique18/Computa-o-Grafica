#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"  // Inclui o cabeçalho "vec3.h" para a definição da classe vec3

#include <iostream>


void write_color(std::ostream &out, color pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();  // Componente vermelha do pixel
    auto g = pixel_color.y();  // Componente verde do pixel
    auto b = pixel_color.z();  // Componente azul do pixel

    // Substitui componentes NaN por zero. Veja a explicação em Ray Tracing: The Rest of Your Life.
    if (r != r) r = 0.0;
    if (g != g) g = 0.0;
    if (b != b) b = 0.0;

    // Divide a cor pelo número de amostras e aplica correção gama para gama=2.0.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Escreve o valor traduzido [0,255] de cada componente de cor.
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}


#endif



//O arquivo "color.h" define uma função chamada write_color, que é usada para escrever uma cor em um formato de saída específico. O arquivo também inclui o cabeçalho 
//"vec3.h" e depende da definição do tipo color, que é presumivelmente definido nesse arquivo ou em outro lugar.

//A função write_color tem os seguintes parâmetros:

//out: Uma referência a um fluxo de saída (como std::cout) onde a cor será escrita.
//pixel_color: A cor a ser escrita.
//samples_per_pixel: O número de amostras por pixel usado no cálculo da cor.
//A função realiza as seguintes etapas:

//Extrai os componentes de cor vermelho, verde e azul da cor.
//Verifica se algum componente é um NaN (not-a-number) e, se for o caso, substitui-o por zero. Isso é feito para lidar com casos em que ocorrem operações inválidas, 
//como raiz quadrada de um número negativo.
//Divide cada componente de cor pelo número de amostras por pixel e aplica a correção de gama (gamma-correction). A correção de gama é uma transformação não linear 
//aplicada aos valores de cor para compensar as características de exibição de monitores e dispositivos de saída.
//Converte os valores de cor normalizados no intervalo [0,1] para o intervalo inteiro [0,255] e os grava no fluxo de saída, separados por espaços.
//Em resumo, o arquivo "color.h" fornece uma função utilitária para escrever cores em um formato específico, aplicando correções e normalizações adequadas para a 
//exibição correta.
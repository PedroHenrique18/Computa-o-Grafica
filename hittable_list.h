#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "rtweekend.h"  // Inclui o cabeçalho "rtweekend.h" para funções e tipos auxiliares

#include "hittable.h"  // Inclui o cabeçalho "hittable.h" para a definição da classe hittable

#include <memory>  // Inclui o cabeçalho <memory> para usar shared_ptr
#include <vector>  // Inclui o cabeçalho <vector> para usar vector


class hittable_list : public hittable {
    public:
        hittable_list() {}  // Construtor padrão

        hittable_list(shared_ptr<hittable> object) { add(object); }  // Construtor que adiciona um objeto à lista

        void clear() { objects.clear(); }  // Limpa a lista de objetos
        void add(shared_ptr<hittable> object) { objects.push_back(object); }  // Adiciona um objeto à lista

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        std::vector<shared_ptr<hittable>> objects;  // Vetor de objetos hittable
};


bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
    auto hit_anything = false;  // Variável para indicar se algum objeto foi atingido
    auto closest_so_far = t_max;  // Variável para armazenar a distância mais próxima encontrada até o momento

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;  // Atualiza a variável indicando que um objeto foi atingido
            closest_so_far = temp_rec.t;  // Atualiza a distância mais próxima encontrada
            rec = temp_rec;  // Atualiza o registro de colisão com os dados do objeto atingido
        }
    }

    return hit_anything;  // Retorna se algum objeto foi atingido
}


#endif



//O arquivo "hittable_list.h" define a classe hittable_list, que é uma lista de objetos hittables (objeto que pode ser atingido por um raio em uma renderização de ray tracing). A classe herda da classe hittable.

//A classe hittable_list tem as seguintes características e funcionalidades principais:

//Ela possui um vetor objects que armazena os ponteiros compartilhados (shared_ptr) para os objetos hittables.
//Possui um construtor padrão e um construtor que aceita um ponteiro compartilhado para um objeto hittable.
//Tem os métodos clear() para limpar a lista de objetos e add() para adicionar um objeto hittable à lista.
//Implementa o método virtual hit() da classe hittable. Esse método itera sobre todos os objetos da lista e verifica se algum deles é atingido pelo raio, 
//dentro do intervalo especificado por t_min e t_max. Ele armazena o objeto atingido mais próximo e retorna true se algum objeto for atingido.
//Em resumo, o arquivo "hittable_list.h" define uma classe que permite armazenar e iterar sobre uma lista de objetos hittables, fornecendo funcionalidades para 
//adicionar, limpar e verificar interseções entre raios e os objetos na lista. Isso é usado para representar e gerenciar objetos em uma cena renderizada por ray tracing.
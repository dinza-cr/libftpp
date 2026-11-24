#pragma once

#include <cstddef>

template <typename TType>
class Pool {
public:
    // Classe imbriquée : accessible via Pool<TType>::Object
    class Object {
    public:
        Object();
        Object(const Object&) = delete;
        Object& operator=(const Object&) = delete; // Interdit l'assignation par copie
        Object(Object&& other) noexcept;           // Autorise le move (pour le return de acquire)
        Object& operator=(Object&& other) noexcept;
        ~Object();
        
        TType* operator->(); // Requis par l'énoncé
        const TType* operator->() const; // Bonne pratique pour les objets const

    private:
        TType* ptr;
        // Pointeur vers l'objet pré-alloué et référence/pointeur vers la Pool parente
    };

    void resize(const size_t& numberOfObjectStored);

    template <typename... TArgs>
    Object acquire(TArgs&&... p_args);
};

template <typename TType>
Pool<TType>::Object::Object(){

}

template <typename TType>
Pool<TType>::Object::~Object(){

}


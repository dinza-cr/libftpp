# libftpp
A library implementing advanced C++ concepts.

## Library content

### Data structures

#### Pool


# Architecture du projet

.
├── Makefile                    # Génère libftpp.a à la racine[cite: 6, 21]
├── libftpp.hpp                 # Header global à la racine (inclut les headers de sections)[cite: 6, 21]
├── includes/                   # Tous les autres .hpp (et .tpp si besoin)
│   ├── data_structures.hpp     # Inclut pool.hpp et data_buffer.hpp
│   ├── design_patterns.hpp     # Inclut memento.hpp, observer.hpp, singleton.hpp, state_machine.hpp
│   ├── threading.hpp           # Inclut thread_safe_queue.hpp, thread.hpp, worker_pool.hpp, persistent_worker.hpp
│   ├── network.hpp             # Inclut message.hpp, client.hpp, server.hpp
│   ├── mathematics.hpp         # Inclut ivector2.hpp, ivector3.hpp, random_2D_coordinate_generator.hpp, perlin_noise_2D.hpp
│   │
│   ├── data_structures/        # Sous-dossiers par chapitre pour la lisibilité
│   │   ├── pool.hpp
│   │   └── data_buffer.hpp
│   ├── design_patterns/
│   │   ├── memento.hpp
│   │   ├── observer.hpp
│   │   ├── singleton.hpp
│   │   └── state_machine.hpp
│   ├── iostream/
│   │   └── thread_safe_iostream.hpp
│   ├── threading/
│   │   ├── thread_safe_queue.hpp
│   │   ├── thread.hpp
│   │   ├── worker_pool.hpp
│   │   └── persistent_worker.hpp
│   ├── network/
│   │   ├── message.hpp
│   │   ├── client.hpp
│   │   └── server.hpp
│   └── mathematics/
│       ├── ivector2.hpp
│       ├── ivector3.hpp
│       ├── random_2D_coordinate_generator.hpp
│       └── perlin_noise_2D.hpp
│
└── srcs/                       # Les fichiers .cpp organisés en miroir
    ├── data_structures/
    │   └── data_buffer.cpp
    ├── design_patterns/
    │   └── memento.cpp
    ├── iostream/
    │   └── thread_safe_iostream.cpp
    ├── threading/
    │   ├── thread.cpp
    │   ├── worker_pool.cpp
    │   └── persistent_worker.cpp
    ├── network/
    │   ├── message.cpp
    │   ├── client.cpp
    │   └── server.cpp
    └── mathematics/
        ├── ivector2.cpp
        ├── ivector3.cpp
        ├── random_2D_coordinate_generator.cpp
        └── perlin_noise_2D.cpp
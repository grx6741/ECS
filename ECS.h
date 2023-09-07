#pragma once

#include <cstdint>
#include <typeinfo>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <stdio.h>

namespace ECS {

    typedef  uint32_t Entity;
    static std::vector<Entity> deleted_entities;
    static uint32_t entity_id = 0;

    struct BaseComponent {
        std::size_t id;
        Entity entity_attached_to;
    };

    class Registry {
        public:
            static inline auto components = std::unordered_map<std::size_t, std::vector<BaseComponent*>* >();
            static inline auto entities = std::unordered_map<Entity, std::vector<BaseComponent*>* >();
    };

    class System {
        public:
            static inline auto systems = std::vector<System*>();

            inline System() {
                System::systems.push_back(this);
            }

            virtual void initSystem() {};
            virtual void updateSystem(float dt) {};

            static void inline initAllSystems() {
                for (System* s : System::systems) {
                    s->initSystem();
                }
            }

            static void inline updateAllSystems(float dt) {
                for (System* s : System::systems) {
                    s->updateSystem(dt);
                }
            }
    };

    template <typename T>
        static inline void registerComponent() {
            if (Registry::components.find(typeid(T).hash_code()) != Registry::components.end()) {
                return;
            }
            Registry::components[typeid(T).hash_code()] = new std::vector<BaseComponent*>;
        }

    template <typename T>
        struct Component : BaseComponent {
            Component() {
                this->id = typeid(T).hash_code();
                registerComponent<T>();
            }
        };

    template <typename T>
        static inline std::vector<T*>* queryComponentByName() {
            return (std::vector<T*>*)Registry::components[typeid(T).hash_code()];
        }

    static inline std::vector<BaseComponent*>* queryComponentByEntity(Entity e) {
        return Registry::entities[e];
    }

    static inline Entity createEntity() {
        Registry::entities[entity_id] = new std::vector<BaseComponent*>();
        return entity_id++;
    }

    template<typename T>
        static inline void addComponentToEntity(Entity e) {
            T* comp = new T();
            comp->entity_attached_to = e;
            Registry::components[typeid(T).hash_code()]->push_back(comp);
            Registry::entities[e]->push_back(comp);
        }

    static inline void deleteEntity(Entity e) {
        if (std::find(deleted_entities.begin(), deleted_entities.end(), e) != deleted_entities.end()) {
            return;
        }
        deleted_entities.push_back(e);
        auto* comps = Registry::entities[e];
        std::for_each(comps->begin(), comps->end(), [](BaseComponent* c) {
                delete c;
                });
        delete comps;
    }

    static inline void closeECS() {
        for (auto comps : Registry::components) {
            delete comps.second;
            Registry::components[comps.first] = nullptr;
        }
    }

}


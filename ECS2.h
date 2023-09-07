#pragma once

#include <cstdint>
#include <typeinfo>
#include <vector>
#include <array>

namespace ECS {

    typedef  uint32_t Entity;
    static std::vector<Entity> deleted_entities;

    struct BaseComponent {
        static inline std::size_t count = 0;
        std::size_t id;
        Entity entity_attached_to;
    };

    class Registry {
        public:
            // static inline auto components = std::unordered_map<std::size_t, std::vector<BaseComponent*>* >();
            // static inline auto entities = std::unordered_map<Entity, std::vector<BaseComponent*>* >();
            // static inline auto components = std::vector<std::vector<BaseComponent*>>();
            // static inline auto entities = std::vector<std::vector<BaseComponent*>>();
            // static inline auto components = std::array<std::array
    };

    template<typename T>
        int registerComponent() {
            BaseComponent::count++;
            return -1;
        }

    template<typename T>
        struct Component : public BaseComponent {
            Component() {
                ECS::registerComponent<T>();
            }
        };


}

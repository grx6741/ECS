#pragma once

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <optional>
#include <stack>
#include <typeinfo>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <stdio.h>

#include <utility>
#include <cstdlib>

#define MAX_COUNT_PER_COMPONENT (std::size_t)(1 << 20)

namespace DS {
template<typename T>
class tombStone {
private:
    T* items;

    std::size_t count;
    std::size_t end;
    std::vector<std::size_t> deleted_items;

public:
    tombStone(std::size_t count) : count(count), end(0) {
        this->items = (T*)std::calloc(this->count, sizeof(T));
    }

    template<int I>
    tombStone()
    {
        
    }

    ~tombStone() {
        std::free(this->items);
    }

    inline std::size_t getSize() { return end; }

    inline std::size_t addItem() {
        if (deleted_items.empty()) {
            T* comp = new(this->items + this->end) T();
            return this->end++;
        }

        std::size_t last = deleted_items[deleted_items.size()-1];
        this->deleted_items.pop_back();
        return last;
    }

    inline bool isItemDeleted(std::size_t index) {
        return (std::find(this->deleted_items.begin(), this->deleted_items.end(), index) != this->deleted_items.end());
    }

    inline void deleteItem(std::size_t index) {
        if (!isItemDeleted(index))
            return;
        if (index < this->count)
            this->deleted_items.push_back(index);
    }

    inline T* getItem(std::size_t index) {
        // REMINDER: May need to check if item is already deleted
        if (index < this->count)
            return this->items + index;
        return nullptr;
    }

};

}

namespace ECS {

struct BaseComponent {

    std::size_t id;
    std::size_t entity_attached_to;

};

class Registry {
public:
    static inline auto componentTypes = std::vector<void*>();
    static inline auto registererdComponentTypes = std::vector<std::size_t>();

    template<typename T>
    static inline DS::tombStone<T>* getTombStone() {
        std::size_t hash = typeid(T).hash_code();
        for (unsigned char i = 0; i < Registry::registererdComponentTypes.size(); i++) {
            if (Registry::registererdComponentTypes[i] == hash)
                return (DS::tombStone<T>*)Registry::componentTypes[i];
        }
        return nullptr;
    }

    static inline void FreeRegistry() {
        for (auto a : Registry::componentTypes)
        {
            delete (DS::tombStone<int>*)a;
        }
    }
};

struct Component : BaseComponent {

    template <typename T>
    static inline void registerComponent() {
        std::size_t hash = typeid(T).hash_code();
        if (
            std::find(
                Registry::registererdComponentTypes.begin(),
                Registry::registererdComponentTypes.end(),
                hash
            ) != Registry::registererdComponentTypes.end()
        )
            return;

        auto ts = new DS::tombStone<T>(MAX_COUNT_PER_COMPONENT);
        Registry::registererdComponentTypes.push_back(hash);
        Registry::componentTypes.push_back(ts);
    }
};

class Entity {

private:

    static inline std::size_t entity_counter = 0;
    std::size_t id;
    std::unordered_map<std::size_t, std::vector<std::size_t>> components;

public:
    inline Entity() {
        this->id = ++Entity::entity_counter;
    }

    template<typename T>
    inline void addComponent() {
        Component::registerComponent<T>();

        std::size_t id = Registry::getTombStone<T>()->addItem();
        T* comp = Registry::getTombStone<T>()->getItem(id);

        comp->id = id;
        comp->entity_attached_to = this->id;

        components[typeid(T).hash_code()].push_back(id);
    };

    template<typename T>
    inline T* getComponents() {
        return components[typeid(T).hash_code()];
    }
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

#if 0
template <typename T>
static inline void registerComponent() {
    if (Registry::components.find(typeid(T).hash_code()) != Registry::components.end()) {
        return;
    }
    Registry::components[typeid(T).hash_code()] = new std::vector<BaseComponent*>;
}
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
#endif

}


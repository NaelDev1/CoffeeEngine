#pragma once
#include <cstdint>
#include <bitset>
#include <array>

using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 5000;

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

class EntityManager
{
public:
    Entity CreateEntity()
    {
        return m_EntityCount++;
    }

    void DestroyEntity(Entity entity)
    {
        m_Signatures[entity].reset();
    }

    void SetSignature(Entity entity, Signature signature)
    {
        m_Signatures[entity] = signature;
    }

    Signature GetSignature(Entity entity) const
    {
        return m_Signatures[entity];
    }

private:
    std::array<Signature, MAX_ENTITIES> m_Signatures{};
    Entity m_EntityCount = 0;
};
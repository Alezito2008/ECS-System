#pragma once

#include <string>

class GameObject;

class Component {
public:
    Component(GameObject* parent);
    virtual ~Component() = default;

    void Destroy();

    inline void SetParent(GameObject* newParent);

    inline void SetActive(const bool active) { m_IsActive = active; }
    inline bool IsActive() const { return m_IsActive; }

    virtual const std::string& GetName() const;

    virtual void Start();
    virtual void Update();
    virtual void OnDestroy();

    private:
        static unsigned int m_NextID;
        unsigned int m_ID;
        bool m_IsActive = true;

    protected:
        GameObject* m_Owner;
};

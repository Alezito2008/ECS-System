template <typename T>
inline T *GameObject::FindComponent()
{
    T* comp = ComponentManager::GetInstance().FindComponent<T>(this);
    return comp;
}

template <typename T>
inline bool GameObject::RemoveComponent()
{
    return ComponentManager::GetInstance().RemoveComponent<T>(this);
}

template <typename T>
inline T *GameObject::AddComponent()
{
    T* comp = ComponentManager::GetInstance().CreateComponent<T>(this);
    return comp;
}

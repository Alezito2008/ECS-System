#include "Scene.h"

unsigned int Scene::s_NextID = 0;

Scene::Scene() {
    m_ID = s_NextID++;
}

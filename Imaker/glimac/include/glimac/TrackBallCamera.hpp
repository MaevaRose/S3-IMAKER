#include <glimac/glm.hpp>

namespace glimac {

  class TrackBallCamera {
    public :
    TrackBallCamera() : m_fDistance(30.f), m_fAngleX(0.f), m_fAngleY(0.f) {};

    void moveFront(float delta){
      m_fDistance += delta;
    }

    void rotateLeft(float degrees){
      m_fAngleY += degrees;
    }

    void rotateUp(float degrees){
      m_fAngleX += degrees;
    }

    glm::mat4 getViewMatrix() const {
      glm::mat4 VM = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -m_fDistance)); // Translation
      VM = glm::rotate(VM, glm::radians(m_fAngleX), glm::vec3(1.f, 0.f, 0.f)); // Translation * Rotation
      VM = glm::rotate(VM, glm::radians(m_fAngleY), glm::vec3(0.f, 1.f, 0.f)); // Translation * Rotation * rotation
      return VM;
    }

    private :
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;
  };
}

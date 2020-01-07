#pragma once
#include <glimac/glm.hpp>
#include <class/World.hpp>

namespace glimac {

  class TrackBallCamera {
    public :
    TrackBallCamera() : m_fDistance(60.f), m_fAngleX(-60.f), m_fAngleZ(0.f), ViewMatrix(glm::mat4(1.f)) {
    };

    void moveFront(float delta){
      m_fDistance += delta;
    }

    void rotateLeft(float degrees){
      m_fAngleZ += degrees;
    }

    void rotateUp(float degrees){
      m_fAngleX += degrees;
    }

    glm::mat4 getViewMatrix(Imaker::World world) const {
      glm::mat4 VM = glm::translate(ViewMatrix, glm::vec3(0.f, 0.f, -m_fDistance)); // Translation
      VM = glm::rotate(VM, glm::radians(m_fAngleX), glm::vec3(1.f, 0.f, 0.f)); // Translation * Rotation
      VM = glm::rotate(VM, glm::radians(m_fAngleZ), glm::vec3(0.f, 0.f, 1.f)); // Translation * Rotation * rotation
      VM = glm::translate(VM, glm::vec3(float(-world.getWidth()), float(-world.getHeight()), float(-world.getLength()))); // pour centrer la caméra sur la scène
      return VM;
    }

    void defaultPosition(){
      m_fDistance = 60.f;
      m_fAngleX = -60.f;
      m_fAngleZ = 0.f;
    }

    void posTop(){
      m_fDistance = 60.f;
      m_fAngleX = 0.f;
      m_fAngleZ = 0.f;
    }

    void posBottom(){
      m_fDistance = 60.f;
      m_fAngleX = 180.f;
      m_fAngleZ = 0.f;
    }

    void posLeft(){
      m_fDistance = 60.f;
      m_fAngleX = -90.f;
      m_fAngleZ = 90.f;
    }

    void posRight(){
      m_fDistance = 60.f;
      m_fAngleX = -90.f;
      m_fAngleZ = -90.f;
    }

    void posFront(){
      m_fDistance = 60.f;
      m_fAngleX = -90.f;
      m_fAngleZ = 0.f;
    }

    void posBack(){
      m_fDistance = 60.f;
      m_fAngleX = -90.f;
      m_fAngleZ = 180.f;
    }

    public :
    float m_fDistance;
    float m_fAngleX;
    float m_fAngleZ;
    glm::mat4 ViewMatrix;
  };
}

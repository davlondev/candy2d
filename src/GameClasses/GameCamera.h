#pragma once

#include "../stdafx.h"

class GameCamera {
private:
    glm::vec2 _position;
    glm::vec2 _size;
    glm::vec2 _origin;
    float _originalZoom;
    float _zoom;

public: 
    GameCamera(
        glm::vec2 pos = glm::vec2(0.0f, 0.0f),
        glm::vec2 size = glm::vec2(0.0f, 0.0f),
        glm::vec2 origin = glm::vec2(0.0f, 0.0f),
        float originalZoom = 4.0f,
        float zoom = 1.0f) :
            _position(pos), _size(size), _origin(origin), _originalZoom(originalZoom), _zoom(zoom) {}

    inline glm::vec2 GetPosition() const { return _position; }
    inline void SetPosition(glm::vec2 pos) { _position = pos; }
    inline void Translate(glm::vec2 pos) { _position += pos; }

    inline glm::vec2 GetSize() const { return _size; }
    inline void SetSize(glm::vec2 size) { _size = size; }
    inline void AddSize(glm::vec2 size) { _size += size; }

    inline glm::vec2 GetOrigin() const { return _origin; }
    inline void SetOrigin(glm::vec2 orig) { _origin = orig; }

    inline float GetOriginalZoom() const { return _originalZoom; }
    inline void SetOriginalZoom(float origZoom) { _originalZoom = origZoom; }

    inline float GetZoom() const { return _zoom; }
    inline void SetZoom(float zoom) { _zoom = zoom; }
    inline void AddZoom(float zoom) { _zoom += zoom; } 

    inline void MoveSlowly(glm::vec2 targetPos, float speed=5.0f) {
        glm::vec2 target = targetPos * (GetZoom()/GetOriginalZoom());
        glm::vec2 delta = target - GetPosition();
        //std::cout << "delta: " << Vec2toString(delta) << std::endl;
        glm::vec2 move = glm::vec2(delta.x * speed, delta.y * speed);
        Translate(move);
        //std::cout << "delta: " << Vec2toString(cam->position) << std::endl;
    }

    inline glm::vec2 WorldToScreen(const glm::vec2 &pos) {
        glm::vec2 ret = glm::vec2(0.0f,0.0f);
        // ret += g::viewport.position;
        ret += GetPosition() + (GetSize() / 2.0f);
        ret -= pos * (GetZoom() / GetOriginalZoom()); // assuming that pos is the origin
        return ret;
    }

    glm::vec2 ScreenToWorld(const glm::ivec2 &pos) {
        glm::vec2 ret = pos;
        ret -= GetPosition();
        ret -= (GetSize() / 2.0f);
        ret *= -1;
        ret /= GetZoom() / GetOriginalZoom();
        return ret;
    }
};
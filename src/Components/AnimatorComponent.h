#pragma once

#include "../stdafx.h"
#include "BaseComponent.h"

//#define SHOWDEBUG

class Animation {
private:
    SDL_Rect _startFrame;
    float _delay;
    float _timer;
    int _numFrames;
    int _curFrame;

public:
    Animation(const SDL_Rect& startFrame, float delay, int numFrames) :
        _startFrame(startFrame), _delay(delay), _timer(0.0f), _numFrames(numFrames), _curFrame(0) {
        std::cout << "        Animation()" << this << std::endl;
        }
    ~Animation() {
        std::cout << "        ~Animation() " << this << std::endl;
    }

    const SDL_Rect& GetStartFrame() const { return _startFrame; }
    float GetDelay() const { return _delay; }

    float GetTimer() const { return _timer; }
    void IncTimer(float amount) { 
        if (_timer >= _delay) {
            _timer = 0.0f;
        }
        _timer += amount; 
    }

    int GetNumFrames() const { return _numFrames; }

    int GetCurFrame() const { return _curFrame; }
    void IncCurFrame(int frames = 1) { 
        _curFrame += frames; 
        if (_curFrame >= _numFrames - 1) _curFrame = 0;
    }
    void SetCurFrame(int frame) { _curFrame = frame; }
};

class AnimatorComponent : public Component {
private:
    std::vector<Animation*> _animations;
    int _curAnimationIndex;
public:

    template<typename... Args>
    AnimatorComponent(Args&&... args) 
        : _curAnimationIndex(0) {
        (_animations.emplace_back(std::forward<Args>(args)...));
#ifdef SHOWDEBUG
        std::cout << "    AnimatorComponent()" << std::endl;
#endif
    }
    ~AnimatorComponent() {
#ifdef SHOWDEBUG
        std::cout << "    ~AnimatorComponent()" << std::endl;
#endif
        for (auto a : _animations) {
            delete a;
        }
        _animations.clear();
    }
    int GetCurrentAnimationIndex() const { return _curAnimationIndex; }
    void SetCurrentAnimationIndex(int index) { _curAnimationIndex = index; }

    // chatGPT!
    template<typename... Args>
    void AddAnimation(Args&&... args) {
        _animations.emplace_back(std::forward<Args>(args)...);
    }

    void PopAnimation() { _animations.pop_back(); }

    int GetNumAnimations() const { return _animations.size(); }
    Animation* GetCurrentAnimation() { return _animations[_curAnimationIndex]; }
};
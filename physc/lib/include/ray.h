#pragma once

#include "sphere.h"

#include <fstream>

class Ray {
public:
    explicit Ray(const glm::vec3 &origin, const glm::vec3 &direction) :
            origin_{origin}, direction_{direction} {};

    template<bool normalize_direction=false>
    inline glm::vec3 at(float t) noexcept { return origin_ + (direction_ * t); }


    [[nodiscard]] inline glm::vec3& origin() noexcept { return origin_; }

    [[nodiscard]] inline glm::vec3& direction() noexcept { return direction_; }

    bool intersectsSphere(const Sphere &sphere, float& t);

    void sampleRayCasting(int32_t width, int32_t height);

    glm::vec3 determineColor(const Sphere& sphere, float& t);

    void castNumerousRaysIntoScene(int32_t width, int32_t height);

    inline glm::vec3 rayColor() {
        glm::vec3 r_hat = glm::normalize(direction_);
        const float t = 0.5f * (r_hat.y + 1.0f);
        return interpolateBetween(glm::vec3{1.0, 1.0, 1.0}, glm::vec3(0.5, 0.3, 0.65), t);
    }

private:

    inline glm::vec3 interpolateBetween(glm::vec3 from, glm::vec3 to, float t) const noexcept {
        return (1 - t) * from + to * t;
    }

private:
    glm::vec3 origin_;
    glm::vec3 direction_;
};

template<>
inline glm::vec3 Ray::at(float t) noexcept { return origin_ + (glm::normalize(direction_) * t); }
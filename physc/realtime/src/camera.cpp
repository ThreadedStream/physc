#include <include/camera.h>
#include <spdlog/spdlog.h>

void Camera::move(float dt, const Direction &dir) noexcept {
    switch (dir) {
        case Direction::FORWARD:
            eye_ += camera_speed_ * dt * front_;
            break;
        case Direction::BACKWARD:
            eye_ -= camera_speed_ * dt * front_;
            break;
        case Direction::LEFT:
            right_ = glm::normalize(glm::cross(front_, up_));
            eye_ -= right_ * camera_speed_ * dt;
            break;
        case Direction::RIGHT:
            right_ = glm::normalize(glm::cross(front_, up_));
            eye_ += right_ * camera_speed_ * dt;
            break;
        default:
            break;
    }
}

void Camera::rotate(double x_pos, double y_pos, float dt, bool &initial) {

    static const float sensitivity = 0.002f;
    static float vertical_angle{0.0f}, horizontal_angle{0.0f};

    const auto dx = static_cast<float>(last_x_ - x_pos);
    const auto dy = static_cast<float>(last_y_ - y_pos);

    horizontal_angle += dx * sensitivity;
    vertical_angle += dy * sensitivity;

    spdlog::info("yaw: {}, pitch: {}", horizontal_angle, vertical_angle);


    last_x_ = x_pos;
    last_y_ = y_pos;

    front_.x = glm::cos(glm::radians(horizontal_angle)) * glm::cos(glm::radians(vertical_angle));
    front_.y = glm::sin(glm::radians(glm::radians(vertical_angle)));
    front_.z = glm::sin(glm::radians(horizontal_angle)) * glm::cos(glm::radians(vertical_angle));

    front_ = glm::normalize(front_);
    up_ = glm::normalize(glm::cross(right_, front_));

    // disable "variable unused" warning
    (void)dt;
}

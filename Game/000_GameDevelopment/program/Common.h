#pragma once
#include <dxe.h>

// 状態管理
enum class PlayerState {
    FLIGHT,
    SWINGBY,
    BOOST
};

const float SLOW_TIME_SCALE = 0.3f;
const float GRAVITY_RANGE_FACTOR = 2.5f;

// 数値用のLerp
inline float MyLerp(float a, float b, float t) {
    return a + (b - a) * t;
}

// --- 追加：Vector3用のLerp ---
inline tnl::Vector3 MyLerp(const tnl::Vector3& a, const tnl::Vector3& b, float t) {
    return a + (b - a) * t;
}
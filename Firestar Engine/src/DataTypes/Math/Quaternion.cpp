#include "DataTypes/Math/Quaternion.h"
#include <fmt/base.h>

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482f

Quaternion Quaternion::operator*(const Quaternion& other) const {
    return Quaternion(
        w * other.x + x * other.w + y * other.z - z * other.y,
        w * other.y - x * other.z + y * other.w + z * other.x,
        w * other.z + x * other.y - y * other.x + z * other.w,
        w * other.w - x * other.x - y * other.y - z * other.z
    );
}

Quaternion Quaternion::FromEuler(float pitch, float yaw, float roll) {
    float cy = cos(yaw * 0.5 * PI / 180.0f);
    float sy = sin(yaw * 0.5 * PI / 180.0f);
    float cp = cos(pitch * 0.5 * PI / 180.0f);
    float sp = sin(pitch * 0.5 * PI / 180.0f);
    float cr = cos(roll * 0.5 * PI / 180.0f);
    float sr = sin(roll * 0.5 * PI / 180.0f);

    return Quaternion(
        sr * cp * cy - cr * sp * sy, // X
        cr * sp * cy + sr * cp * sy, // Y
        cr * cp * sy - sr * sp * cy, // Z
        cr * cp * cy + sr * sp * sy  // W
    ); 
}

void Quaternion::Print() const{
    fmt::print("Quaternion({}, {}, {}, {})\n", x, y, z, w);
}
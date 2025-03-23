#pragma once
#include <iostream>
#include <numbers>
#include <string>
#include <vector>

const auto pi = std::numbers::pi_v< float >;

struct Vector2 {
    float x, y;

    bool IsValid() const {
        if (std::isnan(x) || std::isnan(y)) return false;
        if (std::isinf(x) || std::isinf(y)) return false;

        const float MAX_COORD = 50000.0f;
        if (std::abs(x) > MAX_COORD || std::abs(y) > MAX_COORD) return false;

        return true;
    }
};
struct Vector3
{
    float x, y, z;

    Vector3(float x, float y, float z) : x(x), y(y), z(z)
    {
    }

    Vector3() : x(0), y(0), z(0)
    {
    }

    Vector3 lerp(const Vector3& other, float t) const {
        return {
            x + (other.x - x) * t,
            y + (other.y - y) * t,
            z + (other.z - z) * t
        };
    }


    inline const float& operator[](int i) const
    {
        return ((float*)this)[i];
    }

    inline float& operator[](int i)
    {
        return ((float*)this)[i];
    }

    inline Vector3 __fastcall operator/(float s) const
    {
        return *this * (1.0f / s);
    }

    const float dot(const Vector3& vec) const
    {
        return x * vec.x + y * vec.y + z * vec.z;
    }

    const float distance(Vector3 vector) const
    {
        return sqrtf(powf(vector.x - x, 2.0) + powf(vector.y - y, 2.0) + powf(vector.z - z, 2.0));
    }

    const Vector3 operator*(float value) const
    {
        return { x * value, y * value, z * value };
    }

    const float squared() const
    {
        return x * x + y * y + z * z;
    }

    inline Vector3 direction() const
    {
        const float lenSquared = squared();
        const float invSqrt = 1.0f / sqrtf(lenSquared);
        return Vector3(x * invSqrt, y * invSqrt, z * invSqrt);
    }

    static const Vector3& one()
    {
        static const Vector3 v(1, 1, 1);
        return v;
    }
    static const Vector3& unitX()
    {
        static const Vector3 v(1, 0, 0);
        return v;
    }
    static const Vector3& unitY()
    {
        static const Vector3 v(0, 1, 0);
        return v;
    }
    static const Vector3& unitZ()
    {
        static const Vector3 v(0, 0, 1);
        return v;
    }

    inline Vector3& operator*=(float fScalar)
    {
        x *= fScalar;
        y *= fScalar;
        z *= fScalar;
        return *this;
    }

    Vector3 operator-(const Vector3& vec) const
    {
        return { x - vec.x, y - vec.y, z - vec.z };
    }

    Vector3 operator+(const Vector3& vec) const
    {
        return { x + vec.x, y + vec.y, z + vec.z };
    }

    Vector3 operator*(const Vector3& vec) const
    {
        return { x * vec.x, y * vec.y, z * vec.z };
    }

    Vector3 operator/(const Vector3& vec) const
    {
        return { x / vec.x, y / vec.y, z / vec.z };
    }

    Vector3& operator-=(const Vector3& rkVector)
    {
        x -= rkVector.x;
        y -= rkVector.y;
        z -= rkVector.z;
        return *this;
    }

    float magnitude() const
    {
        return std::sqrtf((x * x) + (y * y) + (z * z));
    }

    Vector3 normalized() const
    {
        float m = magnitude();
        float nx = x / m, ny = y / m, nz = z / m;
        return Vector3(nx, ny, nz);
    }

    bool empty() const
    {
        return x == 0.f && y == 0.f && z == 0.f;
    }

    bool IsValid() const {
        if (std::isnan(x) || std::isnan(y) || std::isnan(z)) return false;
        if (std::isinf(x) || std::isinf(y) || std::isinf(z)) return false;

        const float MAX_COORD = 50000.0f;
        if (std::abs(x) > MAX_COORD || std::abs(y) > MAX_COORD || std::abs(z) > MAX_COORD) return false;

        return true;
    }

    Vector3 get_angle_to(const Vector3& dest) const
    {
        Vector3 diff = *this - dest;
        Vector3 ret;

        float length = diff.magnitude();
        ret.y = asinf(diff.y / length);
        ret.x = -atan2f(diff.x, -diff.z);

        return ret * (180.f / pi);
    }

    float unitize(float tolerance = 1e-06)
    {
        float fMagnitude = magnitude();

        if (fMagnitude > tolerance)
        {
            float fInvMagnitude = 1.0f / fMagnitude;
            x *= fInvMagnitude;
            y *= fInvMagnitude;
            z *= fInvMagnitude;
        }
        else
        {
            fMagnitude = 0.0f;
        }

        return fMagnitude;
    }

    const Vector3 normalizeeeeeeeeeeeeethissssssssss() const
    {
        Vector3 ret;
        float mag = this->magnitude();
        ret.x = x / mag;
        ret.y = y / mag;
        ret.z = z / mag;
        return ret;
    }


    Vector3 crossssssssproducttttttt(Vector3 b) const
    {
        return Vector3(y * z - b.y * z, z * x - b.z * x, x * y - b.x * y);
    }

    int size() const
    {
        return 3;
    }

    Vector3 operator-() const
    {
        return { -x, -y, -z };
    }
};

struct Vector4 { float x, y, z, w; };
struct Quaternion final { float x, y, z, w; };
struct Matrix3 {
    float data[9];
    Vector3 getColumn(int index) const {
        return Vector3{
            data[index],
            data[index + 3],
            data[index + 6]
        };
    }

    Vector3 GetForwardVector() const {
        return { data[6], data[7], data[8] };
    }
};

struct Matrix4 final {
    float data[16];

    bool IsValid() const {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (std::isnan(data[i * 4 + j]) || std::isinf(data[i * 4 + j])) return false;
            }
        }
        return true;
    }
};

struct CFrame
{
    Vector3 right_vector = { 1, 0, 0 };
    Vector3 up_vector = { 0, 1, 0 };
    Vector3 back_vector = { 0, 0, 1 };
    Vector3 position = { 0, 0, 0 };

    CFrame() = default;
    CFrame(Vector3 position) : position{ position }
    {
    }
    CFrame(Vector3 right_vector, Vector3 up_vector, Vector3 back_vector, Vector3 position)
        : right_vector{ right_vector },
        up_vector{ up_vector },
        back_vector{ back_vector },
        position{ position }
    {

    }
    CFrame Lerp(const CFrame& other, float t) const {
        Vector3 newRight = right_vector.lerp(other.right_vector, t);
        Vector3 newUp = up_vector.lerp(other.up_vector, t);
        Vector3 newBack = back_vector.lerp(other.back_vector, t);
        Vector3 newPosition = position.lerp(other.position, t);

        return CFrame(newRight, newUp, newBack, newPosition);
    }


public:
    void look_at_locked(Vector3 point) noexcept
    {
        Vector3 look_vector =
            (this->position - point).normalizeeeeeeeeeeeeethissssssssss() * Vector3 { 1, 0, 1 };
        Vector3 right_vector = Vector3{ 0, 1, 0 }.crossssssssproducttttttt(look_vector);
        Vector3 up_vector = {
            0, 1, 0
        };
        this->right_vector = right_vector;
        this->up_vector = up_vector;
        this->back_vector = look_vector * Vector3{ -1, -1, -1 };
    }

    CFrame look_at(Vector3 point) noexcept
    {
        Vector3 look_vector = (position - point).normalizeeeeeeeeeeeeethissssssssss() * Vector3 { -1, -1, -1 };
        Vector3 right_vector = Vector3(0, 1, 0).crossssssssproducttttttt(look_vector);
        Vector3 up_vector = look_vector.crossssssssproducttttttt(right_vector);

        return CFrame{ right_vector, up_vector, look_vector, this->position };
    }

    auto operator*(CFrame cframe) const noexcept
    {
        CFrame ret;

        ret.right_vector = { right_vector.x * cframe.right_vector.x + right_vector.y * cframe.up_vector.x +
                                 right_vector.z * cframe.back_vector.x,
                             right_vector.x * cframe.right_vector.y + right_vector.y * cframe.up_vector.y +
                                 right_vector.z * cframe.back_vector.y,
                             right_vector.x * cframe.right_vector.z + right_vector.y * cframe.up_vector.z +
                                 right_vector.z * cframe.back_vector.z };
        ret.up_vector = {
            up_vector.x * cframe.right_vector.x + up_vector.y * cframe.up_vector.x + up_vector.z * cframe.back_vector.x,
            up_vector.x * cframe.right_vector.y + up_vector.y * cframe.up_vector.y + up_vector.z * cframe.back_vector.y,
            up_vector.x * cframe.right_vector.z + up_vector.y * cframe.up_vector.z + up_vector.z * cframe.back_vector.z
        };
        ret.back_vector = { back_vector.x * cframe.right_vector.x + back_vector.y * cframe.up_vector.x +
                                back_vector.z * cframe.back_vector.x,
                            back_vector.x * cframe.right_vector.y + back_vector.y * cframe.up_vector.y +
                                back_vector.z * cframe.back_vector.y,
                            back_vector.x * cframe.right_vector.z + back_vector.y * cframe.up_vector.z +
                                back_vector.z * cframe.back_vector.z };
        ret.position = { right_vector.x * cframe.position.x + right_vector.y * cframe.position.y +
                             right_vector.z * cframe.position.z + position.x,
                         up_vector.x * cframe.position.x + up_vector.y * cframe.position.y +
                             up_vector.z * cframe.position.z + position.y,
                         back_vector.x * cframe.position.x + back_vector.y * cframe.position.y +
                             back_vector.z * cframe.position.z + position.z };

        return ret;
    }

    static CFrame fromEulerAnglesYXZ(float y, float x, float z, Vector3 pos) noexcept
    {
        float cosY = std::cos(y), sinY = std::sin(y);
        float cosX = std::cos(x), sinX = std::sin(x);
        float cosZ = std::cos(z), sinZ = std::sin(z);

        Vector3 right = {
            cosY * cosZ + sinY * sinX * sinZ,
            cosX * sinZ,
            -sinY * cosZ + cosY * sinX * sinZ
        };

        Vector3 up = {
            -cosY * sinZ + sinY * sinX * cosZ,
            cosX * cosZ,
            sinZ * sinY + cosY * sinX * cosZ
        };

        Vector3 back = {
            sinY * cosX,
            -sinX,
            cosY * cosX
        };

        return CFrame(right, up, back, pos);
    }


    auto operator*(Vector3 vec) const noexcept
    {
        Vector3 ret;

        ret.x = right_vector.x * vec.x + right_vector.y * vec.y + right_vector.z * vec.z + position.x;
        ret.y = up_vector.x * vec.x + up_vector.y * vec.y + up_vector.z * vec.z + position.y;
        ret.z = back_vector.x * vec.x + back_vector.y * vec.y + back_vector.z * vec.z + position.z;

        return ret;
    }
};
#pragma once

#include "FileSystem/Composite Save System/IComposite.h"
#include "DataTypes/Math/Vector3.h"

class CVector3  : public IComposite
{
private:
    Vector3 data;
    CVector3(const Vector3& data);
public:
    static CVector3* Set(const Vector3& data);
    ~CVector3();
};


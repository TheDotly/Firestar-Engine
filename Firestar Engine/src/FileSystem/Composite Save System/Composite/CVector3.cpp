#include "FileSystem/Composite Save System/Composite/CVector3.h"

CVector3* CVector3::Set(const Vector3& data){
    return new CVector3(data);
}

CVector3::CVector3(const Vector3& data){
    this->data = data;
}


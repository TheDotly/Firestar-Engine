#pragma once

#include <vector>
#include <string>

#include "FileSystem/Composite Save System/IComposite.h"

//ALL DATA TYPES
#include "FileSystem/Composite Save System/Composite/CVector3.h"
#include "FileSystem/Composite Save System/Composite/CVector2.h"
#include "FileSystem/Composite Save System/Composite/CChar.h"
#include "FileSystem/Composite Save System/Composite/CInt.h"
#include "FileSystem/Composite Save System/Composite/Cfloat.h"
#include "FileSystem/Composite Save System/Composite/CString.h"
#include "FileSystem/Composite Save System/Composite/CQuaternion.h"

// so the format of this
// int id -> this is the id of the data type 
// unsigned char data -> this is the data each class holds which can be converted back and fourth (BLACK ADDER GOES FOURTH)

class CompositeSave
{
private:
    std::vector<IComposite> data;
public:
    void addDataType(IComposite data);
    void save(std::string saveLocation);
};

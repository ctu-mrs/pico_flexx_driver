/****************************************************************************\
 * Copyright (C) 2015 Infineon Technologies
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

#pragma once

#include <cstdint>
#include <float.h>
#include <limits>
#include <royale/Definitions.hpp>
#include <royale/String.hpp>
#include <royale/Vector.hpp>

namespace royale {
enum class VariantType {
    Int,
    Float,
    Bool,
    Enum
};

/*! Implements a variant type which can take different basic data types, the default
 *  type is int and the value is set to zero
 */
class Variant {
  public:
    ROYALE_API Variant();
    ROYALE_API Variant(int n, int min = std::numeric_limits<int>::lowest(),
                       int max = std::numeric_limits<int>::max());
    ROYALE_API Variant(float n, float min = std::numeric_limits<float>::lowest(),
                       float max = std::numeric_limits<float>::max());
    ROYALE_API Variant(bool n);
    ROYALE_API Variant(royale::VariantType type, uint32_t value);

    ROYALE_API Variant(royale::String val, royale::Vector<royale::Pair<royale::String, int>> possibleVals);
    ROYALE_API Variant(int val, royale::Vector<royale::Pair<royale::String, int>> possibleVals);

    ROYALE_API ~Variant();

    ROYALE_API void setFloat(float n);
    ROYALE_API float getFloat() const;
    ROYALE_API float getFloatMin() const;
    ROYALE_API float getFloatMax() const;

    ROYALE_API void setInt(int n);
    ROYALE_API int getInt() const;
    ROYALE_API int getIntMin() const;
    ROYALE_API int getIntMax() const;

    ROYALE_API void setBool(bool n);
    ROYALE_API bool getBool() const;

    ROYALE_API void setData(royale::VariantType type, uint32_t value);
    ROYALE_API uint32_t getData() const;

    ROYALE_API royale::VariantType variantType() const;

    ROYALE_API void setEnumValue(int val);
    ROYALE_API void setEnumValue(royale::String val);
    ROYALE_API int getEnumValue() const;
    ROYALE_API royale::String getEnumString() const;
    ROYALE_API royale::Vector<royale::Pair<royale::String, int>> getPossibleVals() const;

    ROYALE_API bool operator==(const royale::Variant &v) const;
    ROYALE_API bool operator!=(const royale::Variant &v) const;
    ROYALE_API bool operator<(const royale::Variant &v) const;

    /*!
     *  This will be thrown if a wrong type is used
     */
    struct InvalidType {};

  private:
    ROYALE_API void setFloatMinMax(float min, float max);
    ROYALE_API void setIntMinMax(int min, int max);

    /*!
     *  Discriminant information about the stored type
     */
    VariantType m_type;

    /*!
     *  Representation of the stored type
     */
    union {
        int i;
        float f;
        bool b;
    };

    int intMin;
    int intMax;

    float floatMin;
    float floatMax;

    royale::Vector<royale::Pair<royale::String, int>> enumVec;

    friend std::ostream &operator<<(std::ostream &stream, const Variant &variant);
};

inline std::ostream &operator<<(std::ostream &stream, const Variant &variant) {
    switch (variant.variantType()) {
    case VariantType::Int: {
        stream << variant.getInt();
        break;
    }
    case VariantType::Float: {
        stream << variant.getFloat();
        break;
    }
    case VariantType::Bool: {
        if (variant.getBool()) {
            stream << "True";
        } else {
            stream << "False";
        }
        break;
    }
    case VariantType::Enum: {
        stream << variant.getEnumString();
        break;
    }
    }

    return stream;
}

} // namespace royale
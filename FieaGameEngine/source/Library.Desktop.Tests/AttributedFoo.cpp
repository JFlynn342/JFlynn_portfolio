#include "AttributedFoo.h"

namespace UnitTests {
    RTTI_DEFINITIONS(AttributedFoo);

    AttributedFoo::AttributedFoo() :
        Attributed(AttributedFoo::TypeIdClass())
    {
    }



    Vector<Signature> AttributedFoo::Signatures()
    {
        return Vector<Signature> {
            Signature("ExternalInt", Datum::DatumType::Integer, 1, offsetof(AttributedFoo, _externalInt)),
            Signature("ExternalFloat", Datum::DatumType::Float, 1, offsetof(AttributedFoo, _externalFloat)),
            Signature("ExternalString", Datum::DatumType::String, 1, offsetof(AttributedFoo, _externalString)),
            Signature("ExternalVector", Datum::DatumType::Vector, 1, offsetof(AttributedFoo, _externalVector)),
            Signature("ExternalMatrix", Datum::DatumType::Matrix, 1, offsetof(AttributedFoo, _externalMatrix)),

            Signature("ExternalIntArray", Datum::DatumType::Integer, _arraySize, offsetof(AttributedFoo, _externalIntArray)),
            Signature("ExternalFloatArray", Datum::DatumType::Float, _arraySize, offsetof(AttributedFoo, _externalFloatArray)),
            Signature("ExternalStringArray", Datum::DatumType::String, _arraySize, offsetof(AttributedFoo, _externalStringArray)),
            Signature("ExternalVectorArray", Datum::DatumType::Vector, _arraySize, offsetof(AttributedFoo, _externalVectorArray)),
            Signature("ExternalMatrixArray", Datum::DatumType::Matrix, _arraySize, offsetof(AttributedFoo, _externalMatrixArray)),

            Signature("Table", Datum::DatumType::Table, 1, 0)
        };

    }

    Scope* AttributedFoo::Clone() const
    {
        return new AttributedFoo(*this);
    }

}

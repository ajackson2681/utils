#pragma once

#include <cassert>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

struct FieldSpec 
{
    uint8_t highBit;
    uint8_t lowBit;
};

template <typename T>
class BitField 
{
    class BitFieldProxy;

public:
    BitField(T initial)
        : raw(initial)
    {}

    BitField()
        : BitField(static_cast<T>(0))
    {}

    ~BitField() {}

    BitField& operator=(const T& value) 
    {
        raw = value;
        return *this;
    }

    operator T() const 
    {
        return raw;
    }

    T operator()(int highBit, int lowBit) const 
    {
        return GetBits(highBit, lowBit);
    }

    T operator()(const FieldSpec& spec) const 
    {
        return Get(spec);
    }

    BitFieldProxy operator()(int highBit, int lowBit)
    {
        return BitFieldProxy(*this, highBit, lowBit);
    }

    BitFieldProxy operator()(const FieldSpec& spec) 
    {
        return BitFieldProxy(*this, spec.highBit, spec.lowBit);
    }

    T operator[](int bitPosition) const 
    {
        return GetBit(bitPosition);
    }

    BitFieldProxy operator[](int bitPosition)
    {
        return BitFieldProxy(*this, bitPosition, bitPosition);
    }

    void SetBit(int bitPosition, bool value) 
    {
        if (value) {
            raw |= (static_cast<T>(1) << bitPosition);
        } 
        else {
            raw &= ~(static_cast<T>(1) << bitPosition);
        }
    }

    T GetBit(int bitPosition) const 
    {
        return (raw >> bitPosition) & static_cast<T>(1);
    }

    void SetBits(int highBit, int lowBit, T value) 
    {
        T mask = ((static_cast<T>(1) << (highBit - lowBit + 1)) - 1) << lowBit;
        raw = (raw & ~mask) | ((value << lowBit) & mask);
    }

    T GetBits(int highBit, int lowBit) const 
    {
        T mask = ((static_cast<T>(1) << (highBit - lowBit + 1)) - 1) << lowBit;
        return (raw & mask) >> lowBit;
    }

    void Set(const FieldSpec& spec, T value)
    {
        assert(spec.highBit >= spec.lowBit);
        assert(spec.highBit < sizeof(T) * 8);
        
        SetBits(spec.highBit, spec.lowBit, value);
    }

    T Get(const FieldSpec& spec) const
    {
        assert(spec.highBit >= spec.lowBit);
        assert(spec.highBit < sizeof(T) * 8);
            
        return GetBits(spec.highBit, spec.lowBit);
    }

    std::string Hex() const
    {
        std::ostringstream stream;
        stream << "0x"
               << std::hex << std::uppercase << std::setfill('0')
               << std::setw(sizeof(T) * 2)
               << static_cast<uint64_t>(raw);
        return stream.str();
    }

    std::string Bin() const
    {
        std::ostringstream stream;
        stream << "0b";
        for (int i = sizeof(T) * 8 - 1; i >= 0; --i) 
        {
            stream << ((raw >> i) & static_cast<T>(1));
        }
        return stream.str();
    }

private:
    T raw;  

    /**
     * Proxy returned by the non-const call operators so that a field
     * selection can appear on the left-hand side of an assignment.
     * Reading converts to T; assigning writes back into the parent field.
     */
    class BitFieldProxy
    {
    public:
        BitFieldProxy(BitField& field, int highBit, int lowBit)
            : field(field)
            , highBit(highBit)
            , lowBit(lowBit)
        {}

        operator T() const
        {
            return field.GetBits(highBit, lowBit);
        }

        BitFieldProxy& operator=(T value)
        {
            field.SetBits(highBit, lowBit, value);
            return *this;
        }

        BitFieldProxy& operator=(const BitFieldProxy& other)
        {
            return *this = static_cast<T>(other);
        }

    private:
        BitField& field;
        int highBit;
        int lowBit;
    };
};
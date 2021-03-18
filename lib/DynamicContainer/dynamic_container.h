#pragma once

// A helper class for storing virtual classes or its children on stack, while being able to replace them.
// maxSize denotes maximum size of an object to be stored here.
// T represents the base class.
template <typename T, size_t maxSize>
class DynamicContainer {
private:
    uint8_t cBuf[maxSize] { 0 };
    T *value = nullptr;

public:
    DynamicContainer() = default;
    DynamicContainer(DynamicContainer &) = delete;
    DynamicContainer &operator =(DynamicContainer &) = delete;
    ~DynamicContainer() {
        if (value != nullptr) {
            value->~T();
        }
    }

    T *getValue() {
        return value;
    }

    template<typename ...Args>
    void putValue(T *(* factory)(void *, Args...), Args... args) {
        if (value != nullptr) {
            value->~T();
        }
        value = factory(reinterpret_cast<void *>(reinterpret_cast<T *>(cBuf)), args...);
    }
};

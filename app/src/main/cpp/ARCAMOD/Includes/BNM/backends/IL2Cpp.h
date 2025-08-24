#pragma once
#include "Includes.h"
#include "Struct.h"

// IL2CPP Function Pointer Types
typedef Il2CppClass *(*class_from_name_t)(const Il2CppImage *assembly, const char *name_space, const char *name);
typedef MethodInfo *(*class_get_method_from_name_t)(Il2CppClass *klass, const char *name, int paramcount);
typedef Il2CppDomain *(*domain_get_t)();
typedef const Il2CppAssembly ***(*domain_get_assemblies_t)();
typedef const Il2CppImage *(*assembly_get_image_t)(const Il2CppAssembly *assembly);
typedef const Il2CppAssembly *(*domain_assembly_open_t)(Il2CppDomain *domain, const char *name);
typedef FieldInfo *(*class_get_field_from_name_t)(Il2CppClass *klass, const char *name);

namespace IL2Cpp {
    void Il2CppAttach();
    void *Il2CppGetImageByName(const char *image);
    void *Il2CppGetClassType(const char *image, const char *namespaze, const char *clazz);
    void Il2CppGetStaticFieldValue(const char *image, const char *namespaze, const char *clazz, const char *name, void *output);
    void Il2CppSetStaticFieldValue(const char *image, const char *namespaze, const char *clazz, const char *name, void* value);
    void *Il2CppGetMethodOffset(const char *image, const char *namespaze, const char *clazz, const char *name, int argsCount = 0);
    void *Il2CppGetMethodOffset(const char *image, const char *namespaze, const char *clazz, const char *name, int argsCount);
    size_t Il2CppGetFieldOffset(const char *image, const char *namespaze, const char *clazz, const char *name);
}
template<typename T> struct IIL2CppArray {
    void *klass;
    void *monitor;
    void *bounds;
    int max_length;
    T m_Items[65535];
    int getLength() {
        return max_length;
    }
    T *getPointer() {
        return (T *)m_Items;
    }
    T &operator[](int i) {
        return m_Items[i];
    }
    T &operator[](int i) const {
        return m_Items[i];
    }
};
template<typename T>
using Array = IIL2CppArray<T>;
struct IIL2CppString {
    void *klass;
    void *monitor;
    int32_t length;
    uint16_t start_char;
    const char *CString();
    const wchar_t *WCString();
    static IIL2CppString *Create(const char *s);
    static IIL2CppString *Create(const wchar_t *s, int len);
    int getLength() {
        return length;
    }
};
typedef IIL2CppString String;
template<typename T> struct Il2CppList {
    void *klass;
    void *unk1;
    IIL2CppArray<T> *items;
    int size;
    int version;
    T *getItems() {
        return items->getPointer();
    }
    int getSize() {
        return size;
    }
    int getVersion() {
        return version;
    }
    T &operator[](int i) {
        return items->m_Items[i];
    }
    T &operator[](int i) const {
        return items->m_Items[i];
    }
};
template<typename T>
using List = Il2CppList<T>;
template<typename K, typename V> struct Il2CppDictionary {
    void *klass;
    void *unk1;
    IIL2CppArray<int **> *table;
    IIL2CppArray<void **> *linkSlots;
    IIL2CppArray<K> *keys;
    IIL2CppArray<V> *values;
    int touchedSlots;
    int emptySlot;
    int size;
    K *getKeys() {
        return keys->getPointer();
    }
    V *getValues() {
        return values->getPointer();
    }
    int getNumKeys() {
        return keys->getLength();
    }
    int getNumValues() {
        return values->getLength();
    }
    int getSize() {
        return size;
    }
};
template<typename K, typename V>
using Dictionary = Il2CppDictionary<K, V>;

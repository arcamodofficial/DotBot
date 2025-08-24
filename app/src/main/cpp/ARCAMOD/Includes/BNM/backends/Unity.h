#include <android/log.h>
#include "Vector3.h"
#include "Vector2.h"
#include "Quaternion.h"
#define M_PI 3.14159265358979323846
#define LOG_TAG  "UnityRR"
#define  LOGEUNITY(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGWUNITY(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGDUNITY(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGIUNITY(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
float NormalizeAngle (float angle){
    while (angle>360)
        angle -= 360;
    while (angle<0)
        angle += 360;
    return angle;
}
Vector3 NormalizeAngles (Vector3 angles){
    angles.x = NormalizeAngle (angles.x);
    angles.y = NormalizeAngle (angles.y);
    angles.z = NormalizeAngle (angles.z);
    return angles;
}
Quaternion GetRotationToLocation(Vector3 targetLocation, float y_bias, Vector3 myLoc){
    return Quaternion::LookRotation((targetLocation + Vector3(0, y_bias, 0)) - myLoc, Vector3(0, 1, 0));
}
template <typename T>
struct monoArray
{
    void* klass;
    void* monitor;
    void* bounds;
    int   max_length;
    void* vector [1];
    int getLength()
    {
        return max_length;
    }
    T getPointer()
    {
        return (T)vector;
    }
};
template <typename T>
struct monoList {
    void *unk0;
    void *unk1;
    monoArray<T> *items;
    int size;
    int version;
    T getItems(){
        return items->getPointer();
    }
    int getSize(){
        return size;
    }
    int getVersion(){
        return version;
    }
};
template <typename K, typename V>
struct monoDictionary {
    void *unk0;
    void *unk1;
    monoArray<int **> *table;
    monoArray<void **> *linkSlots;
    monoArray<K> *keys;
    monoArray<V> *values;
    int touchedSlots;
    int emptySlot;
    int size;
    K getKeys(){
        return keys->getPointer();
    }
    V getValues(){
        return values->getPointer();
    }
    int getNumKeys(){
        return keys->getLength();
    }
    int getNumValues(){
        return values->getLength();
    }
    int getSize(){
        return size;
    }
};
union intfloat {
    int i;
    float f;
};
typedef struct _monoString
{
    void* klass;
    void* monitor;
    int length;
    char chars[1];
    int getLength()
    {
        return length;
    }
    char* getChars()
    {
        return chars;
    }
} monoString;

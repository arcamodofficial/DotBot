#pragma once

#include <cstdint>  // Untuk uintptr_t
#include <sys/types.h>  // Untuk ssize_t

//
// Memory Tools Internal by foxcheatsid@gmail.com
// Created on Tue Apr 4 13:03:13 2023
//

/*
* Type
*/
enum Type {
    TYPE_DWORD,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_WORD,
    TYPE_BYTE,
    TYPE_QWORD,
};

/*
* Maps, Semua hasil pencarian ada di sini 
*/
struct Maps_t {
    uintptr_t start, end;
	Type type;
    struct Maps_t *next;
};

#define SIZE sizeof(struct Maps_t)

/*
* List Memori Region 
*/
enum RegionType {
    ALL,
    JAVA_HEAP,
    C_HEAP,
    C_ALLOC,
    C_DATA,
    C_BSS,
    PPSSPP,
    ANONYMOUS,
    JAVA,
    STACK,
    ASHMEM,
    VIDEO,
    OTHER,
    BAD,
    CODE_APP,
    CODE_SYS
};

namespace kFox 
{
    /*
    * Mendapatkan PackageName
    */
	const char *GetPackageName();
	
    /*
    * Mendapatkan semua hasil pencarian memori
    */
	Maps_t* GetResult();
	
    /*
    * Menghapus semua hasil pencarian memori
    */
	void ClearResult();
	
    /*
    * Set maximal hasil pencarian
    */
	void SetMaxResult(int max_result);
	
    /*
    * Set Region
    */
	int SetSearchRange(RegionType type);
	
    /*
    * Mencari value berdasarkan Region dan Type
    */
	void MemorySearch(char* value, Type type);
	
    /*
    * Mencari value offset berdasarkan Region dan Type
    */
	void MemoryOffset(char *value, long int offset, Type type);
	
    /*
    * Write value berdasarkan offset
    */
	void MemoryWrite(char *value, long int offset, Type type);
	
    /*
    * Write value
    */
	void WriteValues(uintptr_t address, void *value, ssize_t size);
	
    /*
    * Read value
    */
	long ReadValues(uintptr_t address, void *buffer, ssize_t size);
}

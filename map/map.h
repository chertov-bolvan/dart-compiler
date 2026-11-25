#pragma once

#include <stddef.h>

typedef struct MapEntry {
    char *key;
    void *value;
} MapEntry;


typedef struct Map {
    MapEntry *items;
} Map;

int mapInsert(Map *map, const char *key, void *value);
void *mapGet(const Map *map, const char *key);
size_t mapSize(const Map *map);
void *mapValueAt(const Map *map, size_t index);
void mapFree(Map *map);
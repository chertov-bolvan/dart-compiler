#include "map.h"

#include <assert.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"


//Получить значение по ключу
void *mapGet(const Map *map, const char *key) {
    if (map->items == NULL)
        return NULL;

    ptrdiff_t index;
    (void) shgeti_ts(map->items, key, index);
    return index >= 0 ? map->items[index].value : NULL;
}

//Вставить значение по ключу
int mapInsert(Map *map, const char *key, void *value) {
    assert(key != NULL && value != NULL);

    if (mapGet(map, key) != NULL)
        return 0;

    if (map->items == NULL)
        sh_new_strdup(map->items);

    shput(map->items, key, value);
    return 1;
}

//Получить размер мапы
size_t mapSize(const Map *map) {
    return shlenu(map->items);
}

//Получить значение по индексу
void *mapValueAt(const Map *map, size_t index) {
    return index < mapSize(map) ? map->items[index].value : NULL;
}

//Освободить память мапы
void mapFree(Map *map) {
    shfree(map->items);
}
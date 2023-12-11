#include "relationshipMap.h"

long long relationshipMap::checkRange(long long id)
{
    if (id >= source && id <= (source + range))
    {
        return destination + (id - source);
    }
    return -1;
}

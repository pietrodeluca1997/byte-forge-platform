#include "ByteForgePlatform/OpenGL/PlatformOpenGLData.h"

#include <stdlib.h>

#include <ByteForgeLogging.h>
#include <ByteForgeMemory.h>

bool PlatformOpenGLData_Create(PlatformOpenGLData** platform_data)
{
    LOG_INFO("Creating platform data:");

    PlatformOpenGLData* new_platform_data = ALLOC(PlatformOpenGLData, MEMORY_ALLOCATION_CATEGORY_PLATFORM);

    if (!platform_data)
    {
        LOG_FATAL("Error when trying to allocate memory for platform data structure.");
        return false;
    }

    *platform_data = new_platform_data;

    LOG_SUCCESS("\t - Platform data structure created successfully.");
    LOG_NEW_LINE();

    return true;
}


void PlatformOpenGLData_Free(PlatformOpenGLData** platform_data)
{
    LOG_INFO("Freeing platform OpenGL data structure...");

    if (!platform_data || !*platform_data)
    {
        LOG_WARNING("\t - Warning: Attempted to free a NULL platform OpenGL data structure.");
        return;
    }

    FREE(platform_data, sizeof(PlatformOpenGLData), MEMORY_ALLOCATION_CATEGORY_PLATFORM);

    LOG_SUCCESS("\t - Platform OpenGL data structure freed successfully.");
}
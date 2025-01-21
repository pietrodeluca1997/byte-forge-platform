#include "ByteForgePlatform/PlatformWindowData.h"

#include <stdint.h>
#include <stdlib.h>

#include <ByteForgeLogging.h>

bool PlatformWindowData_Create(const char* window_title, const int window_width, const int window_height, PlatformWindowData** platform_window_data)
{
    LOG_INFO("Creating platform window data:");

    if (!window_title)
    {
        LOG_FATAL("\t - Error: Window title cannot be NULL.");
        return false;
    }

    if (window_width <= 0 || window_height <= 0)
    {
        LOG_FATAL("\t - Error: Window dimensions must be greater than zero. Provided: width=%d, height=%d.", window_width, window_height);
        return false;
    }

    PlatformWindowData* platform_window = calloc(1, sizeof(PlatformWindowData));

    if (!platform_window)
    {
        LOG_FATAL("\t - Error: Failed to allocate memory for platform window data structure.");
        return false;
    }

    size_t window_title_size = strlen(window_title) + 1;

    platform_window->window_title = calloc(window_title_size, sizeof(char));

    if (!platform_window->window_title)
    {
        LOG_FATAL("\t - Error: Failed to allocate memory for window title.");

        PlatformWindowData_Free(&platform_window);
        return false;
    }

    strcpy_s(platform_window->window_title, window_title_size, window_title);
    platform_window->window_width = (int)window_width;
    platform_window->window_height = (int)window_height;

    *platform_window_data = platform_window;

    LOG_SUCCESS("\t - PlatformWindowData created successfully. Title: \"%s\", Dimensions: %dx%d.", window_title, window_width, window_height);
    LOG_NEW_LINE();

    return true;
}

void PlatformWindowData_Free(PlatformWindowData** platform_window_data)
{
    LOG_INFO("Freeing platform window data structure...");

    if (!platform_window_data || !*platform_window_data)
    {
        LOG_WARNING("\t - Warning: Attempted to free a NULL platform window data structure.");
        return;
    }

    free((*platform_window_data)->window_title);
    free(*platform_window_data);

    LOG_SUCCESS("\t - Platform window data structure freed successfully.");
}
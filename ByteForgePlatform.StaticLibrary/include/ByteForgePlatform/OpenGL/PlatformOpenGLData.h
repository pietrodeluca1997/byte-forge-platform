#pragma once

#include "ByteForgePlatform/PlatformSettingsData.h"
#include "ByteForgePlatform/PlatformWindowData.h"

#include <SDL3/SDL.h>

/**
 * @brief Holds platform-specific data including SDL objects, settings, and window configuration.
 */
typedef struct PlatformOpenGLData
{
    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;
    SDL_GLContext opengl_context;
    PlatformSettingsData* settings_data;
    PlatformWindowData* window_data;
} PlatformOpenGLData;

/**
 * @brief Creates a PlatformOpenGLData instance empty.
 *
 * @param out_platform_data: Pointer to the output PlatformOpenGLData instance.
 *
 * @return True if the instance was created successfully, false otherwise.
 */
bool PlatformOpenGLData_Create(PlatformOpenGLData** platform_data);

/**
 * @brief Frees the memory associated with a PlatformOpenGLData instance, including its settings and window data.
 *
 * @param platform_data: Pointer to the PlatformOpenGLData instance to be freed. Must not be NULL.
 */
void PlatformOpenGLData_Free(PlatformOpenGLData** platform_data);

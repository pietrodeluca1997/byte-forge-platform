#pragma once

#include "ByteForgePlatform/PlatformInputCallbackFunctionSignature.h"
#include "PlatformOpenGLData.h"

#include <stdbool.h>

/**
 * @brief Initializes the platform context, setting up the necessary resources with OpenGL.
 *
 * @param platform_data: Pointer to the platform data required to initialize. Must not be NULL.
 * @return true if initialization succeeds, false otherwise.
 */
bool PlatformOpenGLContext_Initialize(PlatformOpenGLData* platform_data);

/**
 * @brief Polls for platform events in the current thread and processes input.
 *
 * @param handle_input_callback: Optional callback function to handle keyboard input events. Can be NULL.
 * @param application_data: Custom application data to send to the input callback.
 * @return true if polling succeeds, false if an error occurs or the application should exit.
 */
bool PlatformOpenGLContext_PollThreadEvents(const PlatformInputCallbackFunctionSignature handle_input_callback, const void* application_data);

/**
 * @brief Swaps the rendering buffers for the current platform context with OpenGL.
 *
 * @param platform_data: Pointer to the PlatformData instance containing the rendering context. Must not be NULL.
 */
void PlatformOpenGLContext_SwapBuffers(const PlatformOpenGLData* const platform_data);

/**
 * @brief Sets the background color for the rendering context with OpenGL.
 *
 * @param platform_data: Pointer to the PlatformData instance containing the rendering context. Must not be NULL.
 * @param r: Red component of the color (0-1).
 * @param g: Green component of the color (0-1).
 * @param b: Blue component of the color (0-1).
 * @param a: Alpha component of the color (0-1).
 */
void PlatformOpenGLContext_SetBackgroundColor(const PlatformOpenGLData* const platform_data, const float r, const float g, const float b, const float a);

/**
 * @brief Frees the resources associated with the platform context.
 *
 * @param platform_data: Pointer to the PlatformData instance to be freed. Can be NULL.
 */
void PlatformOpenGLContext_Free(PlatformOpenGLData* platform_data);
#pragma once

#include <ByteForgePlatform.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct PlatformTestFixture
{
	PlatformOpenGLData* platform_data;
} PlatformTestFixture;

void PlatformTestFixture_New(PlatformTestFixture** fixture);
void PlatformTestFixture_Free(PlatformTestFixture** fixture);
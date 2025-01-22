#include "PlatformTestFixture.h"

void PlatformTestFixture_New(PlatformTestFixture** fixture)
{
	PlatformTestFixture* new_fixture = calloc(1, sizeof(PlatformTestFixture));

	assert(new_fixture != NULL);

	assert(PlatformOpenGLData_Create(&new_fixture->platform_data));

	assert(PlatformWindowData_Create("Window Title", 1920, 1080, 320, 180, &new_fixture->platform_data->window_data));
	assert(PlatformSettingsData_Create(165, &new_fixture->platform_data->settings_data));

	*fixture = new_fixture;
}

void PlatformTestFixture_Free(PlatformTestFixture** fixture)
{
	PlatformOpenGLContext_Free((*fixture)->platform_data);
	PlatformOpenGLData_Free(&(*fixture)->platform_data);
	free(*fixture);
}

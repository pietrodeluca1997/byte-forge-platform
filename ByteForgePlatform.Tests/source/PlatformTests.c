#include "PlatformTestFixture.h"

int main()
{
	PlatformTestFixture* fixture = { 0 };
	PlatformTestFixture_New(&fixture);
	
	PlatformOpenGLContext_Initialize(fixture->platform_data);

	while (PlatformOpenGLContext_PollThreadEvents(NULL, NULL))
	{
		PlatformOpenGLContext_SetBackgroundColor(fixture->platform_data, 1, 1, 1, 1);
		PlatformOpenGLContext_SwapBuffers(fixture->platform_data);
	}
		
	PlatformTestFixture_Free(&fixture);

	return 0;
}
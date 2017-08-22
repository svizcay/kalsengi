#include <glad/glad.h>

//#pragma comment(lib, "opengl32.lib")

using namespace std;

extern "C" __declspec(dllexport) int GetPixels(float buffer[], int x, int y, int width, int height) {
	if (glGetError())
		return -1;

	glReadPixels(x, y, width, height, GL_RGBA, GL_FLOAT, buffer);

	if (glGetError())
		return -2;
	return 0;
}
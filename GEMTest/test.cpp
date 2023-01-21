#include "pch.h"

#include "GEM.h"


class File {
public:
	File(int a) : a(a) {}

	int a;
};

TEST(TestCaseName, TestName) {


	gem::Shader<gem::Blending> shader;
	shader.addBlending_Layout(0, "aPos");
	shader.addBlending_Layout(1, "aNormal");
	shader.addBlending_Layout(2, "aTexCoords");
	shader.addBlending_Layout(3, "aTangent");
	shader.addBlending_Layout(4, "aBitangent");
	shader.addBlending_Layout(5, "aMaterialNumber");

	shader.setBlending_VS_OUT("vs_out");

	shader.setBlending();
	shader.compile();


	gem::Shader<gem::TestEntry> shader2;
	shader2.setTestEntry("anything");
	shader2.setTestEntry_Layout(5, "random");
	shader2.setTestEntry_Test();
	shader2.compile();
}
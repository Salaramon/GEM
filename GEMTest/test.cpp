#include "pch.h"

#include <Shader.h>
#include "GEM.h"

TEST(TestCaseName, TestName) {
	Shader<Blending> shader;
	shader.addBlending_Layout(0, "aPos");
	shader.addBlending_Layout(1, "aNormal");
	shader.addBlending_Layout(2, "aTexCoords");
	shader.addBlending_Layout(3, "aTangent");
	shader.addBlending_Layout(4, "aBitangent");
	shader.addBlending_Layout(5, "aMaterialNumber");

	shader.setBlending_VS_OUT("vs_out");

	shader.setBlending();
	shader.compile();
}
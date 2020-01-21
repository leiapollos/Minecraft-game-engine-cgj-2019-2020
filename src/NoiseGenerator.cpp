#include "NoiseGenerator.h"

int NoiseGenerator::generateStoneHeight(float x, float z) const noexcept {
	float height = map(0,(float)m_noiseParameters.maxHeight-5, 0, 1, fBM(x*m_noiseParameters.smooth*2,
																		 z*m_noiseParameters.smooth*2,
																		 m_noiseParameters.octaves+1,
																		 m_noiseParameters.persistance));
	return (int) height;
}

int NoiseGenerator::generateHeight(float x, float z) const noexcept {
	float height = map((float)m_noiseParameters.minHeight,(float)m_noiseParameters.maxHeight, 0, 1, fBM(x*m_noiseParameters.smooth,
																	   z*m_noiseParameters.smooth,
																	   m_noiseParameters.octaves,
																	   m_noiseParameters.persistance));
	return (int) height;
}

float NoiseGenerator::fBM3D(float x, float y, float z, float sm, int oct) const noexcept {
	float XY = fBM(x*sm,y*sm,oct,0.5f);
	float YZ = fBM(y*sm,z*sm,oct,0.5f);
	float XZ = fBM(x*sm,z*sm,oct,0.5f);

	float YX = fBM(y*sm,x*sm,oct,0.5f);
	float ZY = fBM(z*sm,y*sm,oct,0.5f);
	float ZX = fBM(z*sm,x*sm,oct,0.5f);

	return (XY+YZ+XZ+YX+ZY+ZX)/6.0f;
}

float NoiseGenerator::map(float newmin, float newmax, float origmin, float origmax, float value) const noexcept{
	return math::lerp(newmin, newmax, math::inverseLerp(origmin, origmax, value));
}

float NoiseGenerator::fBM(float x, float z, int oct, float pers) const noexcept {
	float total = 0.0f;
	float frequency = 1.0f;
	float amplitude = m_noiseParameters.amplitude;
	float maxValue = 0.0f;
	float offset = m_noiseParameters.offset;
	for(int i = 0; i < oct ; i++) {
		total += PerlinNoise::NoiseNormalized((x+offset) * frequency, (z+offset) * frequency) * amplitude;

		maxValue += amplitude;

		amplitude *= pers;
		frequency *= 2;
	}

	return total/maxValue;
}

void NoiseGenerator::setParameters(const NoiseParameters& params) noexcept {
    m_noiseParameters = params;
}
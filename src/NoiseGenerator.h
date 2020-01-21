#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H
#include "mathf.h"
#include "PerlinNoise.h"

struct NoiseParameters {
    int maxHeight;
    int minHeight;
    float smooth;
    int octaves;
    float persistance;
    float amplitude;
    float offset;
};

class NoiseGenerator {
	public :
		NoiseGenerator() = default;
		int generateStoneHeight(float x, float z) const noexcept;
		int generateHeight(float x, float z) const noexcept;
		float fBM3D(float x, float y, float z, float sm, int oct) const noexcept;
		float map(float newmin, float newmax, float origmin, float origmax, float value) const noexcept;
		float fBM(float x, float z, int oct, float pers) const noexcept;
		void setParameters(const NoiseParameters& params) noexcept;
	private:
		NoiseParameters m_noiseParameters;
};

#endif
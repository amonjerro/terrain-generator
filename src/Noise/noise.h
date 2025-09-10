#include<random>

enum class GeneratorTypes {
	NG_WHITE_NOISE,
	NG_PERLIN
};

class NoiseGenerator {

public:
	virtual float GetNoiseValue(int x, int y) = 0;
	virtual void SetSeed(int seedValue) = 0;

protected:
	int seed;
};


class WhiteNoise : public NoiseGenerator {
public:
	WhiteNoise();
	float GetNoiseValue(int x, int y) override;
	void SetSeed(int seedValue) override;
protected:

private:
	std::mt19937 generator;
};
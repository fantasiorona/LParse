#include "randomizer.h"

#include <array>
#include <sstream>
#include <algorithm>

using namespace LParse;

Randomizer::Randomizer() :
	randomizer(*makeRandomSeedSeq()) {
	
}

Randomizer::Randomizer(const std::string& state) {
	std::istringstream stream(state);

	stream >> randomizer;
}

Randomizer::Randomizer(std::seed_seq& seedSeq) :
	randomizer(seedSeq) {
	
}

int Randomizer::makeInt(const int min, const int max) {
	return std::uniform_int_distribution<int>(min, max)(randomizer);
}

float Randomizer::makeFloat(const float min, const float max) {
	return std::uniform_real_distribution<float>(min, max)(randomizer);
}

std::mt19937 &Randomizer::getRandomizer() {
	return randomizer;
}

std::string Randomizer::toString() const {
	std::stringstream state;

	state << randomizer;

	return state.str();
}

Randomizer Randomizer::makeRandomizer() {
	std::array<int, std::mt19937::state_size> seeds{};
	std::generate_n(seeds.data(), seeds.size(), std::ref(randomizer));
	std::seed_seq seq(std::begin(seeds), std::end(seeds));

	return Randomizer(seq);
}

std::unique_ptr<std::seed_seq> Randomizer::makeRandomSeedSeq() {
	std::random_device rd;
	std::array<int, std::mt19937::state_size> seeds{};
	std::generate_n(seeds.data(), seeds.size(), std::ref(rd));

	return std::make_unique<std::seed_seq>(std::begin(seeds), std::end(seeds));
}

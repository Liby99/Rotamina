#include "object/cloth/ClothParticle.h"

using namespace rotamina;

ClothParticle::ClothParticle() : Particle(), normal(Eigen::Vector3f(0, 0, 0)), normalizeFactor(0) {}

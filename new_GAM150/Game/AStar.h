#pragma once

#include "../Engine/Vec2.h"
#include <vector>
#include <unordered_map>

class Mediator;

Math::ivec2 FindPath(const Math::ivec2& tile_position, const Math::ivec2& target, Mediator* mediator);
std::vector<Math::ivec2> GetNeighboringTiles(const Math::ivec2& position);
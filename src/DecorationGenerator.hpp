
#pragma once

#include <vector>

namespace autodecorate {

    enum class Style {
        Minimal,
        Glow,
        Mixed
    };

    enum class DecorationKind {
        SmallAccent,
        GlowAccent
    };

    struct GeneratorOptions {
        Style style = Style::Mixed;

        float density = 0.35f;
        float spacing = 45.0f;

        bool preserveGameplay = true;
        bool existingLevelMode = true;
        bool generateStandaloneLayout = true;
    };

    struct DecorationPoint {
        float x;
        float y;
        DecorationKind kind;
        float scale;
    };

    std::vector<DecorationPoint> makePlan(
        float left,
        float right,
        float floorY,
        GeneratorOptions const& options
    );

}

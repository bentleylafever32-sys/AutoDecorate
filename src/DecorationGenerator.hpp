
#pragma once

#include <cstdint>
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

    enum class Pattern {
        Wave,
        Symmetric,
        Floating,
        Scatter
    };

    struct Rect {
        float left;
        float bottom;
        float right;
        float top;
    };

    struct GeneratorOptions {
        Style style = Style::Mixed;
        Pattern pattern = Pattern::Wave;

        float density = 0.35f;
        float spacing = 45.0f;
        float clearance = 12.0f;

        std::uint32_t seed = 12345;

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
        GeneratorOptions const& options,
        std::vector<Rect> const& protectedAreas = {}
    );

}

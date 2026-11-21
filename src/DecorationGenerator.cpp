
#include "DecorationGenerator.hpp"

#include <algorithm>
#include <cmath>

namespace autodecorate {

    std::vector<DecorationPoint> makePlan(
        float left,
        float right,
        float floorY,
        GeneratorOptions const& options
    ) {
        std::vector<DecorationPoint> plan;

        if (!std::isfinite(left) ||
            !std::isfinite(right) ||
            !std::isfinite(floorY) ||
            right <= left ||
            !std::isfinite(options.spacing) ||
            options.spacing <= 0.0f) {
            return plan;
        }

        const float density =
            std::clamp(options.density, 0.0f, 1.0f);

        if (density <= 0.0f)
            return plan;

        const float spacing =
            options.spacing / std::max(density, 0.08f);

        const float start = left + spacing * 0.5f;

        int index = 0;

        for (float x = start; x < right; x += spacing, ++index) {

            const float wave =
                std::sin(static_cast<float>(index) * 0.85f);

            const float y =
                floorY + 28.0f + (wave + 1.0f) * 18.0f;

            DecorationKind kind = DecorationKind::SmallAccent;

            if (options.style == Style::Glow ||
                (options.style == Style::Mixed && index % 2 == 0)) {
                kind = DecorationKind::GlowAccent;
            }

            plan.push_back({
                x,
                y,
                kind,
                0.75f + static_cast<float>(index % 3) * 0.12f
            });
        }

        return plan;
    }

}

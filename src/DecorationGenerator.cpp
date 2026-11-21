
#include "DecorationGenerator.hpp"

#include <algorithm>
#include <cmath>
#include <random>

namespace autodecorate {

    static bool isBlocked(
        float x,
        float y,
        Rect const& area,
        float clearance
    ) {
        return
            x >= area.left - clearance &&
            x <= area.right + clearance &&
            y >= area.bottom - clearance &&
            y <= area.top + clearance;
    }

    std::vector<DecorationPoint> makePlan(
        float left,
        float right,
        float floorY,
        GeneratorOptions const& options,
        std::vector<Rect> const& protectedAreas
    ) {
        std::vector<DecorationPoint> plan;

        if (!std::isfinite(left) ||
            !std::isfinite(right) ||
            !std::isfinite(floorY) ||
            !std::isfinite(options.density) ||
            !std::isfinite(options.spacing) ||
            !std::isfinite(options.clearance) ||
            right <= left ||
            options.spacing <= 0.0f ||
            options.clearance < 0.0f) {
            return plan;
        }

        const float density =
            std::clamp(options.density, 0.0f, 1.0f);

        if (density <= 0.0f)
            return plan;

        const float spacing =
            options.spacing / std::max(density, 0.08f);

        std::mt19937 rng(options.seed);

        std::uniform_real_distribution<float> randomHeight(
            20.0f, 85.0f
        );

        const float center = (left + right) * 0.5f;

        int index = 0;

        for (
            float x = left + spacing * 0.5f;
            x < right && index < 2000;
            x += spacing, ++index
        ) {
            float y = floorY + 45.0f;

            switch (options.pattern) {

                case Pattern::Wave: {
                    y += std::sin(index * 0.85f) * 18.0f;
                    break;
                }

                case Pattern::Symmetric: {
                    const float distance = std::abs(x - center);
                    y += std::sin(distance * 0.045f) * 20.0f;
                    break;
                }

                case Pattern::Floating: {
                    y += std::sin(index * 0.45f) * 30.0f;
                    break;
                }

                case Pattern::Scatter: {
                    y = floorY + randomHeight(rng);
                    break;
                }
            }

            bool blocked = false;

            if (options.preserveGameplay) {
                for (auto const& area : protectedAreas) {

                    if (!std::isfinite(area.left) ||
                        !std::isfinite(area.right) ||
                        !std::isfinite(area.bottom) ||
                        !std::isfinite(area.top) ||
                        area.right < area.left ||
                        area.top < area.bottom) {
                        continue;
                    }

                    if (isBlocked(
                        x, y, area, options.clearance
                    )) {
                        blocked = true;
                        break;
                    }
                }
            }

            if (blocked)
                continue;

            DecorationKind kind =
                DecorationKind::SmallAccent;

            if (options.style == Style::Glow ||
                (options.style == Style::Mixed &&
                 index % 2 == 0)) {
                kind = DecorationKind::GlowAccent;
            }

            const float scale =
                0.75f + (index % 3) * 0.12f;

            plan.push_back({
                x,
                y,
                kind,
                scale
            });
        }

        return plan;
    }

}

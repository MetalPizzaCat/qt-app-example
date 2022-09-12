#include "Shapes.hpp"
double MathHelpers::DistanceBetweenPoints(QPointF a, QPointF b) { return std::sqrt((b.x() - a.x()) * (b.x() - a.x()) + (b.y() - a.y()) * (b.y() - a.y())); }
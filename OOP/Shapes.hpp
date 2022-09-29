#include <QPointF>
#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
#include <cmath>
#include <QVector>

namespace MathHelpers
{
    double DistanceBetweenPoints(QPointF a, QPointF b);
}

class Polygon : public QGraphicsItem
{

public:
    QPainterPath paintPath;
    QVector<QPointF> Points;
    virtual void Draw(QPainter *painter) = 0;
    virtual double GetPerimeter() const
    {
        double result = 0;
        for (int i = 1; i < Points.size(); i++)
        {
            result += MathHelpers::DistanceBetweenPoints(Points[i], Points[i - 1]);
        }
        result += MathHelpers::DistanceBetweenPoints(Points[Points.size() - 1], Points[0]);
        return result;
    }
    virtual double GetArea() const = 0;
    Polygon(QVector<QPointF> points) : Points(points)
    {
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        paintPath.clear();
        paintPath.moveTo(Points.first());
        for (QPointF const &point : Points)
        {
            paintPath.lineTo(point);
        }
        paintPath.closeSubpath();
        painter->drawPath(paintPath);
        Draw(painter);
    }
};

class Triangle : public Polygon
{
private:
    double _lengthA_B;
    double _lengthB_C;
    double _lengthC_A;

public:
    void SetA(QPointF a)
    {
        Points[0] = a;
        _lengthA_B = MathHelpers::DistanceBetweenPoints(a, GetB());
        update();
    }
    void SetB(QPointF b)
    {
        Points[1] = b;
        _lengthB_C = MathHelpers::DistanceBetweenPoints(b, GetC());
        update();
    }
    void SetC(QPointF c)
    {
        Points[2] = c;
        _lengthC_A = MathHelpers::DistanceBetweenPoints(c, GetA());
        update();
    }

    QPointF GetA() const { return Points[0]; };
    QPointF GetB() const { return Points[1]; };
    QPointF GetC() const
    {
        return Points[2];
    };

    Triangle(QPointF a, QPointF b, QPointF c) : _lengthA_B(MathHelpers::DistanceBetweenPoints(a, b)),
                                                _lengthB_C(MathHelpers::DistanceBetweenPoints(b, c)),
                                                _lengthC_A(MathHelpers::DistanceBetweenPoints(c, a)),
                                                Polygon({a, b, c})
    {
    }
    QRectF boundingRect() const override
    {
        double smallestX = std::min(GetA().x(), std::min(GetB().x(), GetC().x()));
        double smallestY = std::min(GetA().y(), std::min(GetB().y(), GetC().y()));
        double biggestX = std::max(GetA().x(), std::max(GetB().x(), GetC().x()));
        double biggestY = std::max(GetA().y(), std::max(GetB().y(), GetC().y()));

        // return QRectF(smallestX, smallestY, biggestX, biggestY);
        return QRectF(-400, -400, 400, 400);
    }

    void Draw(QPainter *painter) override
    {

        painter->setPen(QPen(Qt::red, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawPoint(GetMedianIntersection());
    }
    double GetArea() const override
    {
        double p = GetPerimeter() / 2.f;
        return std::sqrt(p * (p - _lengthA_B) * (p - _lengthB_C) * (p - _lengthC_A));
    }

    double GetAltitudeLengthForAB() const
    {
        return 2.f * GetArea() / _lengthA_B;
    }
    double GetAltitudeLengthForBC() const
    {
        return 2.f * GetArea() / _lengthB_C;
    }

    double GetAltitudeLengthForCA() const
    {
        return 2.f * GetArea() / _lengthC_A;
    }

    double GetBisectLengthForAB() const
    {
        double p = GetPerimeter() / 2.f;
        return 2.f * std::sqrt(_lengthB_C * _lengthC_A * p * (p - _lengthA_B)) / (_lengthC_A + _lengthB_C);
    }

    double GetBisectLengthForCA() const
    {
        double p = GetPerimeter() / 2.f;
        return 2.f * std::sqrt(_lengthA_B * _lengthB_C * p * (p - _lengthC_A)) / (_lengthA_B + _lengthB_C);
    }
    double GetBisectLengthForBC() const
    {
        double p = GetPerimeter() / 2.f;
        return 2.f * std::sqrt(_lengthC_A * _lengthA_B * p * (p - _lengthB_C)) / (_lengthC_A + _lengthA_B);
    }

    QPointF GetMedianIntersection() const
    {
        return QPointF((GetA().x() + GetB().x() + GetC().x()) / 3.0f, (GetA().y() + GetB().y() + GetC().y()) / 3.0f);
    }
};
#include <QPointF>
#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>
#include <cmath>

namespace MathHelpers
{
    double DistanceBetweenPoints(QPointF a, QPointF b);
}

class Polygon : public QGraphicsItem
{
public:
    virtual void Draw(QPainter *painter) = 0;
    virtual double GetPerimeter() const = 0;
    virtual double GetArea() const = 0;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        Draw(painter);
    }

    virtual ~Polygon() {}
};

class Triangle : public Polygon
{
private:
    QPointF _a;
    QPointF _b;
    QPointF _c;

    double _lengthA_B;
    double _lengthB_C;
    double _lengthC_A;

public:
    void SetA(QPointF a)
    {
        _a = a;
        _lengthA_B = MathHelpers::DistanceBetweenPoints(a, _b);
    }
    void SetB(QPointF b)
    {
        _b = b;
        _lengthB_C = MathHelpers::DistanceBetweenPoints(b, _c);
    }
    void SetC(QPointF c)
    {
        _c = c;
        _lengthC_A = MathHelpers::DistanceBetweenPoints(c, _a);
    }

    QPointF GetA() const { return _a; };
    QPointF GetB() const { return _b; };
    QPointF GetC() const { return _c; };

    Triangle(QPointF a, QPointF b, QPointF c) : _a(a), _b(b), _c(c),
                                                _lengthA_B(MathHelpers::DistanceBetweenPoints(a, b)),
                                                _lengthB_C(MathHelpers::DistanceBetweenPoints(b, c)),
                                                _lengthC_A(MathHelpers::DistanceBetweenPoints(c, a))
    {
    }
    QRectF boundingRect() const override
    {
        double smallestX = std::min(_a.x(), std::min(_b.x(), _c.x()));
        double smallestY = std::min(_a.y(), std::min(_b.y(), _c.y()));
        double biggestX = std::max(_a.x(), std::max(_b.x(), _c.x()));
        double biggestY = std::max(_a.y(), std::max(_b.y(), _c.y()));

        return QRectF(smallestX, smallestY, biggestX, biggestY);
    }

    void Draw(QPainter *painter) override
    {
        QLineF a(_a, _b);
        QLineF b(_b, _c);
        QLineF c(_c, _a);
        QPointF p = GetMedianIntersection();
        painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawLine(a);
        painter->drawLine(b);
        painter->drawLine(c);
        painter->setPen(QPen(Qt::red, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawPoint(p);
    }

    double GetPerimeter() const override
    {
        return _lengthA_B + _lengthB_C + _lengthC_A;
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
        return QPointF((_a.x() + _b.x() + _c.x()) / 3.0f, (_a.y() + _b.y() + _c.y()) / 3.0f);
    }

    virtual ~Triangle() {}
};
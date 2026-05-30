# Point

Simple 2D point class.

## Interface

```cpp
struct Point
{
    Point(int x = 0, int y = 0);
    Point(const Point& point);

    int GetX() const;
    int GetY() const;

    Point operator = (const Point& point);
    bool operator == (const Point& point) const;
};
```

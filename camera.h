#ifndef CAMERA_H
#define CAMERA_H

#include <QVector2D>
#include <QMatrix4x4>
#include <QElapsedTimer>

class Camera
{
public:
    Camera(int width, int height);
    ~Camera();

    QMatrix4x4 getViewProjection() const;
    QMatrix4x4 getView() const;

    void update();
    void resize(int width, int height);

private:
    float m_fov {45.f};
    float m_near {0.01};
    float m_far {100.f};

    QVector3D m_up {0, 1, 0};
    QVector3D m_position {0, 0, 3};
    QVector3D m_target {0, 0, 0};

    QMatrix4x4 m_view;
    QMatrix4x4 m_projection;

    QElapsedTimer m_etimer;
};

#endif // CAMERA_H

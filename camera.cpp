#include "camera.h"


Camera::Camera(int width, int height)
{
    m_view.lookAt(m_position, m_target, m_up);
    m_projection.perspective(m_fov, static_cast<float>(width)/height, m_near, m_far);
    m_etimer.start();
}

Camera::~Camera()
{

}

QMatrix4x4 Camera::getViewProjection() const
{
    return m_projection*m_view;
}

QMatrix4x4 Camera::getView() const
{
    return m_view;
}

void Camera::update()
{
    const float radius = 3.0f;
    const float speed = 0.7f;
    float px = sin(speed * m_etimer.elapsed()/1000.f) * radius;
    float pz = cos(speed * m_etimer.elapsed()/1000.f) * radius;
    m_position = QVector3D(px, 2.f, pz);
    m_view.setToIdentity();
    m_view.lookAt(m_position, m_target, m_up);
}

void Camera::resize(int width, int height)
{
    m_projection.setToIdentity();
    m_projection.perspective(m_fov, static_cast<float>(width)/height, m_near, m_far);
}


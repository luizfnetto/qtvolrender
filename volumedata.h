#ifndef VOLUMEDATA_H
#define VOLUMEDATA_H

#include <vector>

#include <QString>
#include <QOpenGLFunctions>

class VolumeData
{
public:
    VolumeData(QString path, int dim_size);
    VolumeData(QString path, int dim_x, int dim_y, int dim_z);
    ~VolumeData();

    std::vector<float> GetNormalizedFloatData();
    std::tuple<int, int, int> GetDimesionsSizes();

private:
    int m_dim_x {0};
    int m_dim_y {0};
    int m_dim_z {0};
    std::vector<GLubyte> m_data;
};

#endif // VOLUMEDATA_H

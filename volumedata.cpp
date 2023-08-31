#include "volumedata.h"

#include <QFile>

using namespace std;

VolumeData::VolumeData(QString path, int dim_size) : VolumeData(path, dim_size, dim_size, dim_size)
{
}

VolumeData::VolumeData(QString path, int dim_x, int dim_y, int dim_z)
    : m_dim_x(dim_x)
    , m_dim_y(dim_y)
    , m_dim_z(dim_z)
{
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        int total_size = dim_x*dim_y*dim_z;
        qDebug() << "File: "<< path << "Size: " << dim_x << "x" << dim_y << "x" << dim_z << " = " << total_size;

        QByteArray tmpData = file.readAll();
        m_data.resize(tmpData.size());

        for (int i = 0; i < tmpData.size(); i++)
            m_data[i] = tmpData[i];

    } else {
        qDebug() << "File not found in: " << path;
    }
    file.close();
}

VolumeData::~VolumeData()
{

}

vector<float> VolumeData::GetNormalizedFloatData()
{
    vector<float> fData(m_data.size());

    for (int i = 0; i < m_data.size(); i++)
        fData[i] = static_cast<float>(m_data[i])/255.f;

    return fData;
}

std::tuple<int, int, int> VolumeData::GetDimesionsSizes()
{
    return {m_dim_x, m_dim_y, m_dim_z};
}

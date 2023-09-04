#include "volumedata.h"

#include <QFile>

using namespace std;

VolumeData::VolumeData(QString path, int dim_size, EVolumeDataType data_type) : VolumeData(path, dim_size, dim_size, dim_size, data_type)
{
}

VolumeData::VolumeData(QString path, int dim_x, int dim_y, int dim_z, EVolumeDataType data_type)
    : m_path(path)
    , m_dim_x(dim_x)
    , m_dim_y(dim_y)
    , m_dim_z(dim_z)
    , m_data_type(data_type)
{
    if (m_data_type == EVolumeDataType::UInt8)
        readUInt8Data();
    else if (m_data_type == EVolumeDataType::UInt16)
        readUInt16Data();
}

VolumeData::~VolumeData()
{

}

const std::vector<float> &VolumeData::GetData() const
{
    return m_data;
}

std::vector<float> VolumeData::GetNormalizedData()
{
    vector<float> fData(m_data.size());

    float offset = -m_min; // Push all values to 0 if not
    float length = m_max - m_min;

    for (int i = 0; i < m_data.size(); i++) {
        fData[i] = (m_data[i] - offset)/length;
    }

    return fData;
}

std::tuple<int, int, int> VolumeData::GetDimesionsSizes()
{
    return {m_dim_x, m_dim_y, m_dim_z};
}

void VolumeData::readUInt8Data()
{
    QFile file(m_path);
    if (file.open(QIODevice::ReadOnly)) {
        int total_size = m_dim_x*m_dim_y*m_dim_z;
        qDebug() << "File: "<< m_path << "Size: " << m_dim_x << "x" << m_dim_y << "x" << m_dim_z << " = " << total_size;

        QByteArray tmpData = file.readAll();

        m_data.clear();
        m_data.resize(total_size);

        for (int i = 0; i < tmpData.size(); i++) {
            GLubyte v = tmpData[i];
            m_data[i] = static_cast<float>(v);

            if (m_max < m_data[i])
                m_max = m_data[i];

            if (m_min > m_data[i])
                m_min = m_data[i];
        }
        qDebug() << "Max: " << m_max << " Min: " << m_min;
    } else {
        qDebug() << "File not found in: " << m_path;
    }
    file.close();
}

void VolumeData::readUInt16Data()
{
    QFile file(m_path);
    if (file.open(QIODevice::ReadOnly)) {
        int total_size = m_dim_x*m_dim_y*m_dim_z;
        qDebug() << "File: "<< m_path << "Size: " << m_dim_x << "x" << m_dim_y << "x" << m_dim_z << " = " << total_size;

        m_data.clear();
        m_data.resize(total_size);

        QDataStream data(&file);

        for (int i = 0; !data.atEnd(); i++) {
            unsigned short v;
            data >> v;
            m_data[i] = static_cast<float>(v);

            if (m_max < v)
                m_max = v;

            if (m_min > v)
                m_min = v;
        }
        qDebug() << "Max: " << m_max << " Min: " << m_min;
    } else {
        qDebug() << "File not found in: " << m_path;
    }
    file.close();
}

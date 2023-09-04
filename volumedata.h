#ifndef VOLUMEDATA_H
#define VOLUMEDATA_H

#include <vector>

#include <QString>
#include <QOpenGLFunctions>

enum class EVolumeDataType {
    Invalid,
    UInt8,
    UInt16,
};

class VolumeData
{
public:
    VolumeData(QString path, int dim_size, EVolumeDataType data_type);
    VolumeData(QString path, int dim_x, int dim_y, int dim_z, EVolumeDataType data_type);
    ~VolumeData();

    const std::vector<float>& GetData() const;
    std::vector<float> GetNormalizedData();
    std::tuple<int, int, int> GetDimesionsSizes();

private:
    void readUInt8Data();
    void readUInt16Data();

private:
    QString m_path;

    int m_dim_x {0};
    int m_dim_y {0};
    int m_dim_z {0};

    float m_max {0};
    float m_min {0};

    EVolumeDataType m_data_type {EVolumeDataType::Invalid};

    std::vector<float> m_data;
};

#endif // VOLUMEDATA_H

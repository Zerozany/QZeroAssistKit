#include "ConfigSetting.h"
#include <QMetaProperty>

ConfigSetting::ConfigSetting(const QString& _fileName, Format _format, QObject* _parent) : QSettings{_fileName, _format, _parent}
{
    std::invoke(&ConfigSetting::init, this);
}

void ConfigSetting::init()
{
    const QMetaObject* meta{metaObject()};
    for (int i{meta->propertyOffset()}; i < meta->propertyCount(); ++i)
    {
        const QMetaProperty property{meta->property(i)};
        if (!property.isWritable())
        {
            continue;
        }
        const QString propertyName{QString::fromLatin1(property.name())};
        QString       group{};
        for (int i{0}; i < meta->classInfoCount(); ++i)
        {
            const QMetaClassInfo classInfo{meta->classInfo(i)};
            if (propertyName == QString::fromLatin1(classInfo.name()))
            {
                group = QString::fromLatin1(classInfo.value());
                break;
            }
        }
        if (!group.isEmpty())
        {
            beginGroup(group);
        }
        if (!contains(propertyName))
        {
            if (isWritable())
            {
                setValue(propertyName, QVariant{property.metaType()});
            }
        }
        QVariant propertyValue{value(propertyName)};
        if (propertyValue.convert(property.metaType()))
        {
            property.write(this, propertyValue);
        }
        if (!group.isEmpty())
        {
            endGroup();
        }
    }
    this->sync();
}

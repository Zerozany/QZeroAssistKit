#include "SettingsManager.h"
#include <QMetaProperty>

SettingsManager::SettingsManager(const QString& _fileName, Format _format, QObject* _parent) : QSettings{_fileName, _format, _parent}
{
    std::invoke(&SettingsManager::init, this);
}

void SettingsManager::init()
{
    for (int i{metaObject()->propertyOffset()}; i < metaObject()->propertyCount(); ++i)
    {
        const QMetaProperty property{metaObject()->property(i)};
        if (!property.isWritable())
        {
            continue;
        }
        const QString propertyName{QString::fromLatin1(property.name())};
        QString       group{};
        for (int i{0}; i < metaObject()->classInfoCount(); ++i)
        {
            if (propertyName == QString::fromLatin1(metaObject()->classInfo(i).name()))
            {
                group = QString::fromLatin1(metaObject()->classInfo(i).value());
                break;
            }
        }
        if (!group.isEmpty())
        {
            beginGroup(group);
        }
        if (!contains(propertyName))
        {
            setValue(propertyName, QVariant{property.metaType()});
        }
        if (value(propertyName).convert(property.metaType()))
        {
            property.write(this, value(propertyName));
        }
        if (!group.isEmpty())
        {
            endGroup();
        }
    }
    this->sync();
}

#include "ClassesManager.h"
#include "ClassMate.h"
#include <QDir>
#include <QFile>

constexpr const char* ClassMateJsonName{"ClassMate.json"};

ClassesManager::ClassesManager(QObject* _parent) : QObject{_parent}
{
    std::invoke(&ClassesManager::connectSignal2Slot, this);
}

auto ClassesManager::connectSignal2Slot() noexcept -> void
{
    connect(this, &ClassesManager::classesListChanged, this, &ClassesManager::onClassesListChanged);
    connect(this, &ClassesManager::localClassesPathChanged, this, &ClassesManager::onLocalClassesPathChanged);
}

void ClassesManager::addNewClassMate()
{
    ClassMate*   classMate{new ClassMate{this}};
    QVariantList variantList{m_classesList};
    variantList.append(QVariant::fromValue(classMate));
    this->setClassesList(variantList);
}

void ClassesManager::saveClassMate(const ClassMate* _classMate)
{
    if (!QDir{}.mkpath(m_localClassesPath))
    {
        return;
    }
    QFile classFile{m_localClassesPath + QDir::separator() + _classMate->classID() + QDir::separator() + QString::fromUtf8(ClassMateJsonName)};
    if (!classFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream inputStream{&classFile};
    inputStream << _classMate;
    classFile.close();
}

void ClassesManager::onClassesListChanged()
{
}

void ClassesManager::onLocalClassesPathChanged()
{
    m_classesList.clear();
    QStringList classesDirs{QDir{m_localClassesPath}.entryList(QDir::Dirs | QDir::NoDotAndDotDot)};
    for (const auto& _mate : classesDirs)
    {
    }
}

ClassesManager* ClassesManager::create(QQmlEngine*, QJSEngine*)
{
    static ClassesManager* classManager{new ClassesManager{}};
    return classManager;
}

QVariantList ClassesManager::classesList() const
{
    return m_classesList;
}

void ClassesManager::setClassesList(const QVariantList& _classesList)
{
    if (m_classesList == _classesList)
    {
        return;
    }
    m_classesList = _classesList;
    Q_EMIT this->classesListChanged();
}

ClassMate* ClassesManager::currentClassMate() const
{
    return m_currentClassMate;
}

void ClassesManager::setCurrentClassMate(ClassMate* _currentClassMate)
{
    if (m_currentClassMate == _currentClassMate)
    {
        return;
    }
    m_currentClassMate = _currentClassMate;
    Q_EMIT this->currentClassMateChanged();
}

QString ClassesManager::localClassesPath() const
{
    return m_localClassesPath;
}

void ClassesManager::setLocalClassesPath(const QString& _localClassesPath)
{
    if (m_localClassesPath == _localClassesPath)
    {
        return;
    }
    m_localClassesPath = _localClassesPath;
    Q_EMIT this->localClassesPathChanged();
}

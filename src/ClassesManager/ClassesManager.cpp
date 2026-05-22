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
    connect(this, &ClassesManager::localClassesPathChanged, this, &ClassesManager::onLocalClassesPathChanged);
}

void ClassesManager::addNewClassMate()
{
    ClassMate*   classMate{new ClassMate{this}};
    QVariantList tmpVariantList{m_classesList};
    tmpVariantList.append(QVariant::fromValue(classMate));
    this->setClassesList(tmpVariantList);
    this->setCurrentClassMate(classMate);
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

bool ClassesManager::deleteClassMate(const ClassMate* _classMate)
{
    if (!QDir{m_localClassesPath + QDir::separator() + _classMate->classID()}.removeRecursively())
    {
        return false;
    }
    QVariantList tmpVariantList{m_classesList};
    for (qsizetype i{tmpVariantList.size() - 1}; i >= 0; --i)
    {
        if (tmpVariantList[i].value<ClassMate*>()->classID() != _classMate->classID())
        {
            continue;
        }
        tmpVariantList.removeAt(i);
        break;
    }
    this->setClassesList(tmpVariantList);
    return true;
}

ClassMate* ClassesManager::getClassMate(const QString& _classMateID)
{
    for (auto classMate : m_classesList)
    {
        if (classMate.value<ClassMate*>()->classID() != _classMateID)
        {
            continue;
        }
        return classMate.value<ClassMate*>();
    }
    return nullptr;
}

QVariantList ClassesManager::queryClassMate(const QString& _classMateID)
{
    QVariantList variantList{};
    for (auto classMate : m_classesList)
    {
        if (classMate.value<ClassMate*>()->classID() != _classMateID)
        {
            continue;
        }
        variantList.append(classMate);
    }
    return variantList;
}

void ClassesManager::onLocalClassesPathChanged()
{
    QVariantList tmpVariantList{};
    QStringList  classesDirs{QDir{m_localClassesPath}.entryList(QDir::Dirs | QDir::NoDotAndDotDot)};
    for (const auto& _mate : classesDirs)
    {
        QFile classFile{m_localClassesPath + QDir::separator() + _mate + QDir::separator() + QString::fromUtf8(ClassMateJsonName)};
        if (!classFile.exists() || !classFile.open(QIODevice::ReadOnly))
        {
            continue;
        }
        QTextStream outputStream{&classFile};
        ClassMate*  cassMate{new ClassMate{this}};
        outputStream >> *cassMate;
        classFile.close();
        tmpVariantList.append(QVariant::fromValue(cassMate));
    }
    this->setClassesList(tmpVariantList);
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

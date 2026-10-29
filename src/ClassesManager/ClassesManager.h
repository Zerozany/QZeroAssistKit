_Pragma("once");
#include <QObject>
#include <QtQml>

#if defined(Q_OS_WINDOWS) && defined(_MSC_VER)
    #ifdef QZeroAssistKit
        #define QZERO_API Q_DECL_EXPORT
    #else
        #define QZERO_API Q_DECL_IMPORT
    #endif
#elif defined(__GNUC__) || defined(__clang__)
    #define QZERO_API __attribute__((visibility("default")))
#else
    #define QZERO_API
#endif

class ClassMate;

class QZERO_API ClassesManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QVariantList classesList READ classesList WRITE setClassesList NOTIFY classesListChanged)
    Q_PROPERTY(ClassMate* currentClassMate READ currentClassMate WRITE setCurrentClassMate NOTIFY currentClassMateChanged)
    Q_PROPERTY(QString localClassesPath READ localClassesPath WRITE setLocalClassesPath NOTIFY localClassesPathChanged)

public:
    explicit(true) ClassesManager(QObject* _parent = nullptr);

    virtual ~ClassesManager() noexcept = default;

public:
    virtual QVariantList classesList() const;
    virtual void         setClassesList(const QVariantList& _classesList);

    virtual ClassMate* currentClassMate() const;
    virtual void       setCurrentClassMate(ClassMate* _currentClassMate);

    virtual QString localClassesPath() const;
    virtual void    setLocalClassesPath(const QString& _localClassesPath);

public:
    Q_INVOKABLE virtual void addNewClassMate();

    Q_INVOKABLE virtual void saveClassMate(const ClassMate* _classMate);

    Q_INVOKABLE virtual bool deleteClassMate(const ClassMate* _classMate);

    Q_INVOKABLE virtual ClassMate* getClassMate(const QString& _classMateID);

    Q_INVOKABLE virtual QVariantList queryClassMate(const QString& _classMateID);

protected:
    virtual auto connectSignal2Slot() noexcept -> void;

Q_SIGNALS:
    void classesListChanged();

    void currentClassMateChanged();

    void localClassesPathChanged();

protected Q_SLOTS:
    virtual void onLocalClassesPathChanged();

private:
    QVariantList m_classesList{};
    ClassMate*   m_currentClassMate{nullptr};
    QString      m_localClassesPath{};
};

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
    QML_SINGLETON
    QML_ELEMENT
    Q_PROPERTY(QVariantList classesList READ classesList WRITE setClassesList NOTIFY classesListChanged)
    Q_PROPERTY(ClassMate* currentClassMate READ currentClassMate WRITE setCurrentClassMate NOTIFY currentClassMateChanged)
    Q_PROPERTY(QString localClassesPath READ localClassesPath WRITE setLocalClassesPath NOTIFY localClassesPathChanged)

public:
    static ClassesManager* create(QQmlEngine*, QJSEngine*);

    ~ClassesManager() noexcept = default;

    Q_DISABLE_COPY_MOVE(ClassesManager)

public:
    QVariantList classesList() const;
    void         setClassesList(const QVariantList& _classesList);

    ClassMate* currentClassMate() const;
    void       setCurrentClassMate(ClassMate* _currentClassMate);

    QString localClassesPath() const;
    void    setLocalClassesPath(const QString& _localClassesPath);

public:
    Q_INVOKABLE void addNewClassMate();

    Q_INVOKABLE void saveClassMate(const ClassMate* _classMate);

private:
    explicit(true) ClassesManager(QObject* _parent = nullptr);

    auto connectSignal2Slot() noexcept -> void;

Q_SIGNALS:
    void classesListChanged();

    void currentClassMateChanged();

    void localClassesPathChanged();

private Q_SLOTS:
    void onClassesListChanged();

    void onLocalClassesPathChanged();

private:
    QVariantList m_classesList{};
    ClassMate*   m_currentClassMate{nullptr};
    QString      m_localClassesPath{};
};

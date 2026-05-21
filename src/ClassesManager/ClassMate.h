_Pragma("once");
#include <QObject>
#include <QJsonObject>
#include <QTextStream>

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

class QZERO_API ClassMate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString classID READ classID WRITE setClassID NOTIFY classIDChanged)
    Q_PROPERTY(QString creatTime READ creatTime WRITE setCreatTime NOTIFY creatTimeChanged)
    Q_PROPERTY(QString endTime READ endTime WRITE setEndTime NOTIFY endTimeChanged)
public:
    explicit(true) ClassMate(QObject* _parent = nullptr);
    ~ClassMate() noexcept = default;

public:
    QString classID() const;
    void    setClassID(const QString& _classID);

    QString creatTime() const;
    void    setCreatTime(const QString& _creatTime);

    QString endTime() const;
    void    setEndTime(const QString& _endTime);

public:
    virtual auto toJson() const noexcept -> QJsonObject;

    virtual auto fromJson(const QJsonObject& _jsonObject) -> void;

private:
    auto initBasicInfo() noexcept -> void;

Q_SIGNALS:
    void classIDChanged();

    void creatTimeChanged();

    void endTimeChanged();

private:
    QString m_classID{};
    QString m_creatTime{};
    QString m_endTime{};
};

QTextStream& operator<<(QTextStream& _inputStream, const ClassMate& _classMate);

QTextStream& operator>>(QTextStream& _outputStream, ClassMate& _classMate);

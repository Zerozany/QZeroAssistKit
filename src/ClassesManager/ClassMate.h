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
    friend QZERO_API QTextStream& operator<<(QTextStream& _outputStream, const ClassMate& _classMate);
    friend QZERO_API QTextStream& operator>>(QTextStream& _inputStream, ClassMate& _classMate);
    Q_OBJECT
    Q_PROPERTY(QString classID READ classID WRITE setClassID NOTIFY classIDChanged)
    Q_PROPERTY(QString creatTime READ creatTime WRITE setCreatTime NOTIFY creatTimeChanged)
    Q_PROPERTY(QString endTime READ endTime WRITE setEndTime NOTIFY endTimeChanged)
public:
    explicit(true) ClassMate(QObject* _parent = nullptr);

    virtual ~ClassMate() noexcept = default;

public:
    virtual QString classID() const;
    virtual void    setClassID(const QString& _classID);

    virtual QString creatTime() const;
    virtual void    setCreatTime(const QString& _creatTime);

    virtual QString endTime() const;
    virtual void    setEndTime(const QString& _endTime);

protected:
    virtual auto initBasicInfo() noexcept -> void;

protected:
    virtual auto toJson() const noexcept -> QJsonObject;

    virtual auto fromJson(const QJsonObject& _jsonObject) -> void;

Q_SIGNALS:
    void classIDChanged();

    void creatTimeChanged();

    void endTimeChanged();

private:
    QString m_classID{};
    QString m_creatTime{};
    QString m_endTime{};
};

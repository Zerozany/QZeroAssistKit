_Pragma("once");
#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QTranslator>

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

class QJSEngine;
class QQmlEngine;
class QQmlApplicationEngine;

class QZERO_API Translator : public QTranslator
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)
public:
    ~Translator() noexcept = default;

public:
    static Translator* create(QQmlEngine* _qmlEngine = nullptr, QJSEngine* _qJSEngine = nullptr);

    Q_INVOKABLE QString language() const;
    Q_INVOKABLE void    setLanguage(const QString& _language);

private:
    explicit(true) Translator(QQmlApplicationEngine* _qmlApplicationEngine = nullptr, QTranslator* _parent = nullptr);

    auto connectSignal2Slot() noexcept -> void;

Q_SIGNALS:
    void languageChanged();

private Q_SLOTS:
    void onLanguageChanged();

private:
    QString                m_language{};
    QQmlApplicationEngine* m_qmlApplicationEngine{nullptr};
};

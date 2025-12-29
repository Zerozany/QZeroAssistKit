#include "Translator.h"
#include <QGuiApplication>
#include <QJSEngine>
#include <QQmlEngine>

Translator::Translator(QObject* _parent) : QObject{_parent}
{
    std::invoke(&Translator::connectSignal2Slot, this);
}

auto Translator::connectSignal2Slot() noexcept -> void
{
    connect(this, &Translator::languageChanged, this, &Translator::onLanguageChanged, Qt::AutoConnection);
}

void Translator::onLanguageChanged()
{
    qApp->removeTranslator(&m_translator);
    if (m_translator.load(m_language))
    {
        qApp->installTranslator(&m_translator);
    }
    // TODO1 QML引擎需调用retranslate()方法
    Translator::m_qmlApplicationEngine->retranslate();
}

Translator* Translator::create(QQmlEngine* _qmlEngine, QJSEngine* _qJSEngine)
{
    if (_qmlEngine)
    {
        Translator::m_qmlApplicationEngine = qobject_cast<QQmlApplicationEngine*>(_qmlEngine);
    }
    static Translator translator{};
    return &translator;
}

QString Translator::language() const
{
    return m_language;
}

void Translator::setLanguage(const QString& _language)
{
    if (m_language == _language)
    {
        return;
    }
    m_language = _language;
    Q_EMIT this->languageChanged();
}

#include "Translator.h"
#include <QGuiApplication>
#include <QJSEngine>
#include <QQmlEngine>
#include <QQmlApplicationEngine>

Translator::Translator(QQmlApplicationEngine* _qmlApplicationEngine, QTranslator* _parent) : QTranslator{_parent}, m_qmlApplicationEngine{_qmlApplicationEngine}
{
    std::invoke(&Translator::connectSignal2Slot, this);
}

auto Translator::connectSignal2Slot() noexcept -> void
{
    connect(this, &Translator::languageChanged, this, &Translator::onLanguageChanged, Qt::AutoConnection);
}

void Translator::onLanguageChanged()
{
    qApp->removeTranslator(this);
    if (this->load(m_language))
    {
        qApp->installTranslator(this);
    }
    // TODO1 QML引擎需调用retranslate()方法
    if (m_qmlApplicationEngine)
    {
        m_qmlApplicationEngine->retranslate();
    }
}

Translator* Translator::create(QQmlEngine* _qmlEngine, QJSEngine* _qJSEngine)
{
    static Translator* translator{new Translator{qobject_cast<QQmlApplicationEngine*>(_qmlEngine)}};
    return translator;
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

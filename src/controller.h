// SDPX-FileCopyrightText: 2021 Carl Schwan <carlschwan@kde.org>
// SPDX-LicenseRed: LGPL-2.0-or-later

#pragma once

#include <KPackage/Package>
#include <QObject>
#include <QQuickItem>

class QQmlEngine;
class QQuickItem;
class KLocalizedContext;

/// /brief Main Controller for the AccountWizard.
///
/// Creates QQuickItem from pluginId
class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *wizardItem READ wizardItem WRITE setWizardItem NOTIFY wizardItemChanged)
    Q_PROPERTY(QString wizardId READ wizardId WRITE setWizardId NOTIFY wizardIdChanged)

public:
    Controller(QObject *parent = nullptr);
    ~Controller()
    {
    }

    QQuickItem *wizardItem();
    void setWizardItem(QQuickItem *wizardItem);

    QString wizardId() const;
    void setWizardId(const QString &wizardId);

Q_SIGNALS:
    void wizardItemChanged();
    void wizardIdChanged();

private:
    QQuickItem *createGui(const QString &qmlPath);
    QString qmlPath() const;

    QQmlEngine *m_engine;
    KLocalizedContext *m_contextObj = nullptr;
    KPackage::Package m_wizardPackage;
    QQuickItem *m_wizardItem;
    QString m_wizardId;
};

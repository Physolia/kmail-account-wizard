/*
    SPDX-FileCopyrightText: 2009 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "setupobject.h"
#include <QMap>
#include <akonadi/agentinstance.h>

class KJob;

class Resource : public SetupObject
{
    Q_OBJECT
public:
    explicit Resource(const QString &type, QObject *parent = nullptr);
    void create() override;
    void destroy() override;
    void edit();

public Q_SLOTS:
    Q_SCRIPTABLE void setName(const QString &name);
    Q_SCRIPTABLE void setOption(const QString &key, const QVariant &value);
    Q_SCRIPTABLE Q_REQUIRED_RESULT QString identifier();
    Q_SCRIPTABLE void reconfigure();
    Q_SCRIPTABLE void setEditMode(const bool editMode);

private:
    void instanceCreateResult(KJob *job);

    QString m_typeIdentifier, m_name;
    QMap<QString, QVariant> m_settings;
    Akonadi::AgentInstance m_instance;

    bool m_editMode = false;
};

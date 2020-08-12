/*
    SPDX-FileCopyrightText: 2009 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef SETUPOBJECT_H
#define SETUPOBJECT_H

#include <QObject>

class SetupObject : public QObject
{
    Q_OBJECT
public:
    explicit SetupObject(QObject *parent);

    virtual void create() = 0;
    virtual void destroy() = 0;

    SetupObject *dependsOn() const;
    void setDependsOn(SetupObject *obj);

Q_SIGNALS:
    void error(const QString &msg);
    void info(const QString &msg);
    void finished(const QString &msg);

private:
    SetupObject *m_dependsOn = nullptr;
};

#endif

// SPDX-FileCopyrightText: 2009 Volker Krause <vkrause@kde.org>
// SPDX-FileCopyrightText: 2021 Carl Schwan <carlschwan@kde.org>
// SPDX-License-Identifier: LGPL-2.0-or-later

#include "setupobject.h"

SetupObject::SetupObject(QObject *parent)
    : QObject(parent)
{
}

SetupObject *SetupObject::dependsOn() const
{
    return m_dependsOn;
}

void SetupObject::setDependsOn(SetupObject *obj)
{
    m_dependsOn = obj;
}

#include "moc_setupobject.cpp"

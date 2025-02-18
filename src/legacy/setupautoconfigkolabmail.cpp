/*
    SPDX-FileCopyrightText: 2014 Sandro Knauß <knauss@kolabsys.com>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "setupautoconfigkolabmail.h"
#include "ispdb/autoconfigkolabmail.h"

SetupAutoconfigKolabMail::SetupAutoconfigKolabMail(QObject *parent)
    : SetupIspdb(parent)
{
    delete mIspdb;
    mIspdb = new AutoconfigKolabMail(this);
    connect(mIspdb, &AutoconfigKolabMail::finished, this, &SetupAutoconfigKolabMail::onIspdbFinished);
}

#include "moc_setupautoconfigkolabmail.cpp"

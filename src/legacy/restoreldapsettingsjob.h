/*
    SPDX-FileCopyrightText: 2010-2023 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <KConfigGroup>
#include <KLDAPCore/LdapServer>
#include <QObject>
class KConfig;
class RestoreLdapSettingsJob : public QObject
{
    Q_OBJECT
public:
    explicit RestoreLdapSettingsJob(QObject *parent = nullptr);
    ~RestoreLdapSettingsJob() override;

    void start();
    KConfig *config() const;
    void setConfig(KConfig *config);
    [[nodiscard]] bool canStart() const;
    [[nodiscard]] int entry() const;
    void setEntry(int entry);

Q_SIGNALS:
    void restoreDone();

private:
    void slotConfigSelectedHostLoaded(const KLDAPCore::LdapServer &server);
    void slotConfigHostLoaded(const KLDAPCore::LdapServer &server);
    void restore();
    void saveLdapSettings();
    void restoreSettingsDone();
    void loadNextSelectHostSettings();
    void loadNextHostSettings();
    void saveNextSelectHostSettings();
    void saveNextHostSettings();
    QList<KLDAPCore::LdapServer> mSelHosts;
    QList<KLDAPCore::LdapServer> mHosts;
    int mEntry = -1;
    int mNumSelHosts = -1;
    int mNumHosts = -1;
    int mCurrentIndex = 0;
    KConfig *mConfig = nullptr;
    KConfigGroup mCurrentGroup;
};

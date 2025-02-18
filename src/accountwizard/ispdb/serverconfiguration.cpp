// SPDX-FileCopyrightText: 2010 Omat Holding B.V. <info@omat.nl>
// SPDX-FileCopyrightText: 2014 Sandro Knauß <knauss@kolabsys.com>
// SPDX-FileCopyrightText: 2023 Carl Schwan <carl@carlschwan.eu>
// SPDX-License-Identifier: LGPL-2.0-or-later

#include "ispdb/serverconfiguration.h"
#include <KLocalizedString>

QString replacePlaceholders(const QString &in, const KMime::Types::AddrSpec &addrSpec)
{
    QString out(in);
    out.replace(QLatin1String("%EMAILLOCALPART%"), addrSpec.localPart);
    out.replace(QLatin1String("%EMAILADDRESS%"), addrSpec.asString());
    out.replace(QLatin1String("%EMAILDOMAIN%"), addrSpec.domain);
    return out;
}

QStringList Server::tags() const
{
    QStringList tags;
    switch (type) {
    case IMAP:
        tags << i18n("IMAP");
        break;
    case POP3:
        tags << i18n("POP3");
        break;
    case SMTP:
        tags << i18n("SMTP");
        break;
    }

    switch (socketType) {
    case SSL:
        tags << i18n("SSL/TLS");
        break;
    case StartTLS:
        tags << i18n("StartTLS");
        break;
    case None:
        tags << i18nc("No security mechanism", "None");
        break;
    }

    return tags;
}

std::optional<Server> Server::fromDomElement(const QDomElement &element, const KMime::Types::AddrSpec &addrSpec)
{
    QDomNode o = element.firstChild();
    Server server;
    while (!o.isNull()) {
        QDomElement f = o.toElement();
        if (f.isNull()) {
            o = o.nextSibling();
            continue;
        }

        const QString tagName(f.tagName());
        if (tagName == QLatin1String("hostname")) {
            server.hostname = replacePlaceholders(f.text(), addrSpec);
        } else if (tagName == QLatin1String("port")) {
            server.port = f.text().toInt();
        } else if (tagName == QLatin1String("socketType")) {
            const QString type(f.text());
            if (type == QLatin1String("plain")) {
                server.socketType = None;
            } else if (type == QLatin1String("SSL")) {
                server.socketType = SSL;
            }
            if (type == QLatin1String("STARTTLS")) {
                server.socketType = StartTLS;
            }
        } else if (tagName == QLatin1String("username")) {
            server.username = replacePlaceholders(f.text(), addrSpec);
        } else if (tagName == QLatin1String("authentication") && server.authType == 0) {
            const QString type(f.text());
            if (type == QLatin1String("password-cleartext") || type == QLatin1String("plain")) {
                server.authType = Plain;
            } else if (type == QLatin1String("password-encrypted") || type == QLatin1String("secure")) {
                server.authType = CramMD5;
            } else if (type == QLatin1String("NTLM")) {
                server.authType = NTLM;
            } else if (type == QLatin1String("GSSAPI")) {
                server.authType = GSSAPI;
            } else if (type == QLatin1String("client-ip-based")) {
                server.authType = ClientIP;
            } else if (type == QLatin1String("none")) {
                server.authType = NoAuth;
            } else if (type == QLatin1String("OAuth2")) {
                server.authType = OAuth2;
            }
        }
        o = o.nextSibling();
    }
    if (server.port == -1) {
        return std::nullopt;
    }
    return server;
}

QDebug operator<<(QDebug d, const EmailProvider &t)
{
    d << "domains " << t.domains;
    d << "displayName " << t.displayName;
    d << "shortDisplayName " << t.shortDisplayName;
    d << "imapServers " << t.imapServers;
    d << "popServers " << t.popServers;
    d << "smtpServers " << t.smtpServers;

    return d;
}

QDebug operator<<(QDebug d, const Server &t)
{
    d << "type " << t.type;
    d << "hostname " << t.hostname;
    d << "port " << t.port;
    d << "username " << t.username;
    d << "socketType " << t.socketType;
    d << "authType " << t.authType;
    return d;
}

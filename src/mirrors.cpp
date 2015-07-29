/* This file is part of QtTvDB
 *
 * Copyright (C) 2009-2011 Corentin Chary <corentin.chary@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <QtCore>
#include <QtCore/QDebug>

#include "qttvdb.h"

using namespace QtTvDB;

Mirrors::Mirrors(QObject *parent)
  : QObject(parent)
{
  init();
}

Mirrors::Mirrors(const QString & key, QObject *parent)
  : QObject(parent)
{
  init();
  setKey(key);
}

Mirrors::~Mirrors()
{
}

void
Mirrors::init()
{
  QList < QUrl > mirrors;

  mirrors.append(QUrl("http://www.thetvdb.com/"));

  setXmlMirrors(mirrors);
  setBannerMirrors(mirrors);
  setZipMirrors(mirrors);

  languagesDb_["en"].first = 7;
  languagesDb_["en"].second = "English";
  languagesDb_["da"].first = 10;
  languagesDb_["da"].second = "Dansk";
  languagesDb_["fi"].first = 11;
  languagesDb_["fi"].second = "Suomeksi";
  languagesDb_["nl"].first = 13;
  languagesDb_["nl"].second = "Nederlands";
  languagesDb_["de"].first = 14;
  languagesDb_["de"].second = "Deutsch";
  languagesDb_["it"].first = 15;
  languagesDb_["it"].second = "Italiano";
  languagesDb_["es"].first = 16;
  languagesDb_["es"].second = "Español";
  languagesDb_["fr"].first = 17;
  languagesDb_["fr"].second = "Français";
  languagesDb_["pl"].first = 18;
  languagesDb_["pl"].second = "Polski";
  languagesDb_["hu"].first = 19;
  languagesDb_["hu"].second = "Magyar";
  languagesDb_["el"].first = 20;
  languagesDb_["el"].second = "????????";
  languagesDb_["tr"].first = 21;
  languagesDb_["tr"].second = "Türkçe";
  languagesDb_["ru"].first = 22;
  languagesDb_["ru"].second = "??????? ????";
  languagesDb_["he"].first = 24;
  languagesDb_["he"].second = "?????";
  languagesDb_["ja"].first = 25;
  languagesDb_["ja"].second = "???";
  languagesDb_["pt"].first = 26;
  languagesDb_["pt"].second = "Português";
  languagesDb_["zh"].first = 27;
  languagesDb_["zh"].second = "??";
  languagesDb_["cs"].first = 28;
  languagesDb_["cs"].second = "?e?tina";
  languagesDb_["sl"].first = 30;
  languagesDb_["sl"].second = "Slovenski";
  languagesDb_["hr"].first = 31;
  languagesDb_["hr"].second = "Hrvatski";
  languagesDb_["ko"].first = 32;
  languagesDb_["ko"].second = "???";
  languagesDb_["sv"].first = 8;
  languagesDb_["sv"].second = "Svenska";
  languagesDb_["no"].first = 9;
  languagesDb_["no"].second = "Norsk";
  foreach (QString k, languagesDb_.keys())
    languagesById_[languagesDb_[k].first] = k;
  setLanguages(languagesDb_.keys());
}

QString
Mirrors::languageById(int id)
{
  return languagesById_[id];
}

QString
Mirrors::languageNameById(int id)
{
  return languageName(languageById(id));
}

int
Mirrors::languageId(const QString & l)
{
  return languagesDb_[l].first;
}

QString
Mirrors::languageName(const QString & l)
{  return languagesDb_[l].second;
}

QUrl
Mirrors::randomMirror(const QList<QUrl> & mirrors, bool addkey,
		      const QString & postfix, bool api)
{
  static int i = 0;

  if (mirrors.isEmpty())
    return QUrl();
  i++;
  i %= mirrors.size();
  QUrl m = mirrors.at(i);
  QString path = m.path();

  if (api)
    path += "/api/";
  if (addkey)
    path += key() + "/";
  if (!postfix.isEmpty())
    path += postfix;
  m.setPath(path);
#ifdef Q_WS_WIN
  qWarning() << m.path() << m.encodedPath();
#endif
  return m;
}

QUrl
Mirrors::mirrorsUrl()
{
  return QUrl(QString("http://www.thetvdb.com/api/%1/mirrors.xml").arg(key()));
}

QUrl
Mirrors::languagesUrl()
{
  return QUrl(QString("http://www.thetvdb.com/api/%1/languages.xml").arg(key()));
}

QUrl
Mirrors::serverTimeUrl()
{
  QUrl url = randomMirror(xmlMirrors(), false, QString("Updates.php"));
  //url.addQueryItem("type", "none");
  return url;
}

QUrl
Mirrors::searchShowUrl(const QString & showName, const QString & language)
{
  QUrl url = randomMirror(xmlMirrors(), false, QString("GetSeries.php"));
  //url.addQueryItem("seriesname", showName);
  if (!language.isEmpty())
    //url.addQueryItem("language", language);
  return url;
}

QUrl
Mirrors::showUrl(qint64 showId)
{
  return randomMirror(xmlMirrors(), true, QString("series/%1/").arg(showId));
}

QUrl
Mirrors::episodeUrl(qint64 episodeId)
{
  return randomMirror(xmlMirrors(), true, QString("episodes/%1/").arg(episodeId));
}

QUrl
Mirrors::showAndEpisodesUrl(qint64 showId, const QString & lang)
{
  if (lang.isEmpty())
    return randomMirror(xmlMirrors(), true, QString("series/%1/all/").arg(showId));
  else
    return randomMirror(xmlMirrors(), true, QString("series/%1/all/%2.xml").arg(showId).arg(lang));
}

QUrl
Mirrors::showAndEpisodesUrlZip(qint64 showId, const QString & lang)
{
  return randomMirror(zipMirrors(), true, QString("series/%1/all/%2.zip").arg(showId).arg(lang));
}

QUrl
Mirrors::updatesUrl(const QString & period)
{
  return randomMirror(xmlMirrors(), true, QString("updates/updates_%s.xml").arg(period));
}

QUrl
Mirrors::updatedShowsUrl(const QDateTime & period)
{
  QUrl url = randomMirror(xmlMirrors(), true, QString("Updates.php"));
  //url.addQueryItem("time", QString("%1").arg(period.toTime_t()));
  //url.addQueryItem("type", "series");
  return url;
}

QUrl
Mirrors::updatedEpisodesUrl(const QDateTime & period)
{
  QUrl url = randomMirror(xmlMirrors(), true, QString("Updates.php"));
  //url.addQueryItem("time", QString("%1").arg(period.toTime_t()));
  //url.addQueryItem("type", "episodes");
  return url;
}

QUrl
Mirrors::bannersUrl(qint64 showId)
{
  return randomMirror(xmlMirrors(), true, QString("series/%1/banners.xml").arg(showId));
}

QUrl
Mirrors::bannerUrl(const QString & path)
{
  return randomMirror(xmlMirrors(), false, QString("banners/%1").arg(path), false);
}

QList< QPair < Mirrors::Mask, QUrl > >
Mirrors::parseMirrors(const QString & xml)
{
  QDomDocument doc;

  doc.setContent(xml);
  return parseMirrors(doc.firstChildElement("Mirrors"));
}

QList< QPair < Mirrors::Mask, QUrl > >
Mirrors::parseMirrors(const QDomNode & node)
{
  QList< QPair < Mirrors::Mask, QUrl > > list;

  QDomElement p = node.firstChildElement("Mirror");
  while (!p.isNull()) {
    QUrl url(p.firstChildElement("mirrorpath").text());
    Mirrors::Mask mask = (Mirrors::Mask) p.firstChildElement("typemask").text().toUInt();

    list.append(QPair < Mirrors::Mask, QUrl >(mask, url));

    p = p.nextSiblingElement("Mirror");
  }
  return list;
}

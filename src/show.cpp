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

#include "qttvdb.h"

using namespace QtTvDB;

Show::Show(QObject *parent)
  : QObject(parent)
{
  init();
}

Show::Show(const QString & xml, QObject *parent)
  : QObject(parent)
{
  QDomDocument doc;

  doc.setContent(xml);
  init();
  init(doc);
}

Show::Show(const QDomNode & node, QObject *parent)
  : QObject(parent)
{
  init();
  init(node);
}

Show::~Show()
{

}

void
Show::init()
{
  setId(-1);
}

void
Show::init(const QDomNode & node)
{
  setId(node.firstChildElement("id").text().toULongLong());
  setName(node.firstChildElement("SeriesName").text());
  setOverview(node.firstChildElement("Overview").text());
  setGenre(node.firstChildElement("Genre").text().split("|", QString::SkipEmptyParts));
  setActors(node.firstChildElement("Actors").text().split("|", QString::SkipEmptyParts));
  setNetwork(node.firstChildElement("Network").text());
  setLanguage(node.firstChildElement("Language").text());
  setContentRating(node.firstChildElement("ContentRating").text());
  setRating(node.firstChildElement("Rating").text());
  setStatus(node.firstChildElement("Status").text());
  setRuntime(QTime( 0, 0 ).addSecs( node.firstChildElement("Runtime").text().toInt() * 60));
  setAirsTime(QTime::fromString(node.firstChildElement("Airs_Time").text(), "h:mm AP"));
  setAirsDay(node.firstChildElement("Airs_DayOfWeek").text());
  setFirstAired(QDateTime::fromString(node.firstChildElement("FirstAired").text(), Qt::ISODate));
  setBanner(node.firstChildElement("banner").text());
  setPoster(node.firstChildElement("poster").text());
  setFanArt(node.firstChildElement("fanart").text());
  setImdbId(node.firstChildElement("IMDB_ID").text());
  setSeriesId(node.firstChildElement("SeriesID").text());
  setZap2ItId(node.firstChildElement("zap2it_id").text());
  setLastUpdated(QDateTime::fromTime_t(node.firstChildElement("lastupdated").text().toUInt()));
}

bool
Show::isNull()
{
  return id() == -1;
}

QList< Show * >
Show::parseShows(const QString & xml)
{
  QDomDocument doc;

  doc.setContent(xml);
  return parseShows(doc);
}

QList< Show * >
Show::parseShows(const QDomNode & node)
{
  QList < Show * > list;

  QDomElement p;
  QDomNode prev;

  prev = node;
  p = prev.firstChildElement("Data");

  if (p.isNull())
    p = prev.toElement();
  else
    prev = p;
  p = prev.firstChildElement("Show");
  if (p.isNull())
    p = prev.firstChildElement("Series");

  while (!p.isNull()) {
    Show *e = new Show(p);

    if (e && !e->isNull())
      list.append(e);
    else
      delete e;
    prev = p;
    p = prev.nextSiblingElement("Show");
    if (p.isNull())
      p = prev.nextSiblingElement("Series");
  }
  return list;
}


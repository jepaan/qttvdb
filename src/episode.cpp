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

Episode::Episode(QObject *parent)
  : QObject(parent)
{
  init();
}

Episode::Episode(const QString & xml, QObject *parent)
  : QObject(parent)
{
  QDomDocument doc;

  init();
  doc.setContent(xml);
  init(doc);
}

Episode::Episode(const QDomNode & node, QObject *parent)
  : QObject(parent)
{
  init();
  init(node);
}

Episode::~Episode()
{

}

void
Episode::init(const QDomNode & node)
{
  setId(node.firstChildElement("id").text().toULongLong());
  setName(node.firstChildElement("EpisodeName").text());
  setShowId(node.firstChildElement("seriesid").text().toULongLong());
  setOverview(node.firstChildElement("Overview").text());
  setSeason(node.firstChildElement("SeasonNumber").text().toUInt());
  setEpisode(node.firstChildElement("EpisodeNumber").text().toUInt());
  setDirector(node.firstChildElement("Director").text());
  setGuestStars(node.firstChildElement("GuestStars").text().split("|"));
  setLanguage(node.firstChildElement("Language").text());
  setProductionCode(node.firstChildElement("ProductionCode").text());
  setRating(node.firstChildElement("Rating").text());
  setWriter(node.firstChildElement("Writer").text()); /* | */
  setFirstAired(QDateTime::fromString(node.firstChildElement("FirstAired").text(), Qt::ISODate));
  setDvdChapter(node.firstChildElement("DVD_chapter").text());
  setDvdDiscId(node.firstChildElement("DVD_discid").text());
  setDvdEpisodeNumber(node.firstChildElement("DVD_episodenumber").text());
  setDvdSeason(node.firstChildElement("DVD_season").text());
  setImage(node.firstChildElement("filename").text());
  setAirsAfterSeason(node.firstChildElement("airsafter_season").text());
  setAirsBeforeSeason(node.firstChildElement("airsbefore_season").text());
  setAirsBeforeEpisode(node.firstChildElement("airsbefore_episode").text());
  setCombinedEpisode(node.firstChildElement("combined_episode_number").text().toUInt());
  setCombinedSeason(node.firstChildElement("combined_season").text().toUInt());
  setAbsoluteNumber(node.firstChildElement("absolute_number").text().toUInt());
  setSeasonId(node.firstChildElement("seasonid").text().toUInt());
  setEpImgFlag(node.firstChildElement("EpImgFlag").text());
  setImdbId(node.firstChildElement("IMDB_ID").text());
  setLastUpdated(QDateTime::fromTime_t(node.firstChildElement("lastupdated").text().toUInt()));
}

void
Episode::init()
{
  setId(-1);
  setShowId(-1);
  setSeasonId(-1);
  setSeason(-1);
  setEpisode(-1);
  setCombinedEpisode(-1);
  setCombinedSeason(-1);
  setAbsoluteNumber(-1);
}

bool
Episode::isNull()
{
  return id() == -1;
}

QList< Episode * >
Episode::parseEpisodes(const QString & xml)
{
  QDomDocument doc;

  doc.setContent(xml);
  return parseEpisodes(doc);
}

QList< Episode * >
Episode::parseEpisodes(const QDomNode & node)
{
  QList < Episode * > list;

  QDomElement p;

  p = node.firstChildElement("Data");
  if (p.isNull())
    p = node.firstChildElement("Episode");
  else
    p = p.firstChildElement("Episode");

  while (!p.isNull()) {
    Episode *e = new Episode(p);

    if (e && !e->isNull())
      list.append(e);
    else
      delete e;
    p = p.nextSiblingElement("Episode");
  }
  return list;
}


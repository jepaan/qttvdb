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

Banner::Banner(QObject *parent)
  : QObject(parent)
{
  init();
}

Banner::Banner(const QString & xml, QObject *parent)
  : QObject(parent)
{
  QDomDocument doc;

  init();
  doc.setContent(xml);
  init(doc);
}

Banner::Banner(const QDomNode & node, QObject *parent)
  : QObject(parent)
{
  init();
  init(node);
}

Banner::~Banner()
{

}

void
Banner::init()
{
  setId(-1);
}

void
Banner::init(const QDomNode & node)
{
  setId(node.firstChildElement("id").text().toULongLong());
  setPath(node.firstChildElement("BannerPath").text());
  setType(node.firstChildElement("BannerType").text());
  setType2(node.firstChildElement("BannerType2").text());
  setLanguage(node.firstChildElement("Language").text());
  setSeason(node.firstChildElement("Season").text());
}

bool
Banner::isNull()
{
  return id() == -1;
}

QList< Banner * >
Banner::parseBanners(const QString & xml)
{
  QDomDocument doc;

  doc.setContent(xml);
  return parseBanners(doc);
}

QList< Banner * >
Banner::parseBanners(const QDomNode & node)
{
  QList < Banner * > list;

  QDomElement p;

  p = node.firstChildElement("Banners");
  if (p.isNull())
    p = node.firstChildElement("Banner");
  else
    p = p.firstChildElement("Banner");

  while (!p.isNull()) {
    Banner *e = new Banner(p);

    if (e && !e->isNull())
      list.append(e);
    else
      delete e;
    p = p.nextSiblingElement("Banner");
  }
  return list;
}


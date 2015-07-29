#include <QDebug>

#include "test.h"

Test::Test() {
  m = new QtTvDB::Mirrors("5C9847FB5B186042");
  nm = new QNetworkAccessManager();

  qDebug() << m;
  qDebug() << m->key();
  qDebug() << m->languagesUrl();
  qDebug() << m->languages() << m->languageId("en") << m->languageName("en");
  qDebug() << m->languageById(7);
  qDebug() << m->bannersUrl(73739);
  QNetworkReply *rep = nm->get(QNetworkRequest(m->bannersUrl(73739)));
  connect(rep, SIGNAL(finished()), this, SLOT(finished()));
}


void
Test::finished() {
  QNetworkReply *reply = dynamic_cast < QNetworkReply * > (sender());

  qDebug() << reply;
  QString data = reply->readAll();
  qDebug() << data;
  QList < QtTvDB::Banner * > list = QtTvDB::Banner::parseBanners(data);
  qDebug() << list;
  qDebug() << list[0]->map();
  reply->deleteLater();
}


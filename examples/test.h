#ifndef TEST_H
# define TEST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtTvDB>

class Test : public QObject {
  Q_OBJECT
public:
  Test();

public slots:
  void finished();

private:
  QtTvDB::Mirrors *m;
  QNetworkAccessManager *nm;
};


#endif

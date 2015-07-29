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

#ifndef QTTVDB_H
#define QTTVDB_H

#include "qttvdb_export.h"

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QUrl>
#include <QtCore/QDateTime>
#include <QtXml/QDomNode>
#include <QtCore/QVariant>
#include <QtCore/QPair>

#define TVDB_PROPERTY(type_, name_, getter_, setter_)			\
private:                                                                \
  type_ name_##_;							\
public:									\
  inline type_ & getter_() {						\
      return name_##_;							\
  }									\
  inline type_ const & getter_() const {				\
      return name_##_;							\
  }									\
  inline void setter_(type_ const & name_##__) {			\
      name_##_ = name_##__;						\
      emit name_##Changed();						\
  }

namespace QtTvDB {

   class QTTVDB_EXPORT Mirrors : public QObject {
	Q_OBJECT

	TVDB_PROPERTY(QString, key, key, setKey);
	TVDB_PROPERTY(QList<QUrl>, xmlMirrors, xmlMirrors, setXmlMirrors);
	TVDB_PROPERTY(QList<QUrl>, bannerMirrors, bannerMirrors, setBannerMirrors);
	TVDB_PROPERTY(QList<QUrl>, zipMirrors, zipMirrors, setZipMirrors);
	TVDB_PROPERTY(QStringList, languages, languages, setLanguages);

	Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged);
	Q_PROPERTY(QList<QUrl> xmlMirrors READ xmlMirrors WRITE setXmlMirrors NOTIFY xmlMirrorsChanged);
	Q_PROPERTY(QList<QUrl> bannerMirrors READ bannerMirrors WRITE setBannerMirrors NOTIFY bannerMirrorsChanged);
	Q_PROPERTY(QList<QUrl> zipMirrors READ zipMirrors WRITE setZipMirrors NOTIFY zipMirrorsChanged);
	Q_PROPERTY(QStringList languages READ languages WRITE setLanguages NOTIFY languagesChanged);

    signals:
	void keyChanged();
	void xmlMirrorsChanged();
	void bannerMirrorsChanged();
	void zipMirrorsChanged();
	void languagesChanged();

    public:
	Mirrors(QObject * parent = NULL);
	Mirrors(const QString & key, QObject *parent = NULL);
	~Mirrors();

	enum Mask {
	  XML = 1,
	  BANNER = 2,
	  ZIP = 4
	};

	QUrl mirrorsUrl();
	QUrl languagesUrl();
	QUrl serverTimeUrl();
	QUrl searchShowUrl(const QString & showName, const QString & language = QString());
	QUrl showUrl(qint64 showId);
	QUrl episodeUrl(qint64 episodeId);
	QUrl showAndEpisodesUrl(qint64 showId, const QString & language = QString());
	QUrl showAndEpisodesUrlZip(qint64 showId, const QString & language);
	QUrl updatesUrl(const QString & period);
	QUrl updatedShowsUrl(const QDateTime & period);
	QUrl updatedEpisodesUrl(const QDateTime & period);
	QUrl bannersUrl(qint64 showId);
	QUrl bannerUrl(const QString & path);
	int languageId(const QString & l);
	QString languageById(int id);
	QString languageNameById(int id);
	QString languageName(const QString & l);
	static QList< QPair < Mask, QUrl > > parseMirrors(const QString & xml);
	static QList< QPair < Mask, QUrl > > parseMirrors(const QDomNode & node);
	QUrl randomMirror(const QList<QUrl> & mirrors, bool key = false,
			  const QString & postfix = QString(), bool api = true);
    private:
	void init();
	QMap < QString, QPair < int, QString > > languagesDb_;
	QMap < int, QString > languagesById_;
    };

    class QTTVDB_EXPORT Episode : public QObject {
	Q_OBJECT


	TVDB_PROPERTY(qint64, id, id, setId);
	TVDB_PROPERTY(qint64, showId, showId, setShowId);
	TVDB_PROPERTY(qint64, seasonId, seasonId, setSeasonId);
	TVDB_PROPERTY(QString, name, name, setName);
	TVDB_PROPERTY(QString, overview, overview, setOverview);
	TVDB_PROPERTY(int, season, season, setSeason);
	TVDB_PROPERTY(int, episode, episode, setEpisode);
	TVDB_PROPERTY(QString, director, director, setDirector);
	TVDB_PROPERTY(QStringList, guestStars, guestStars, setGuestStars);
	TVDB_PROPERTY(QString, language, language, setLanguage);
	TVDB_PROPERTY(QString, productionCode, productionCode, setProductionCode);
	TVDB_PROPERTY(QString, rating, rating, setRating);
	TVDB_PROPERTY(QString, writer, writer, setWriter);
	TVDB_PROPERTY(QDateTime, firstAired, firstAired, setFirstAired);
	TVDB_PROPERTY(QString, dvdChapter, dvdChapter, setDvdChapter);
	TVDB_PROPERTY(QString, dvdDiscId, dvdDiscId, setDvdDiscId);
	TVDB_PROPERTY(QString, dvdEpisodeNumber, dvdEpisodeNumber, setDvdEpisodeNumber);
	TVDB_PROPERTY(QString, dvdSeason, dvdSeason, setDvdSeason);
	TVDB_PROPERTY(QString, image, image, setImage);
	TVDB_PROPERTY(QString, airsAfterSeason, airsAfterSeason, setAirsAfterSeason);
	TVDB_PROPERTY(QString, airsBeforeSeason, airsBeforeSeason, setAirsBeforeSeason);
	TVDB_PROPERTY(QString, airsBeforeEpisode, airsBeforeEpisode, setAirsBeforeEpisode);
	TVDB_PROPERTY(int, combinedEpisode, combinedEpisode, setCombinedEpisode);
	TVDB_PROPERTY(int, combinedSeason, combinedSeason, setCombinedSeason);
	TVDB_PROPERTY(int, absoluteNumber, absoluteNumber, setAbsoluteNumber);
	TVDB_PROPERTY(QString, epImgFlag, epImgFlag, setEpImgFlag);
	TVDB_PROPERTY(QString, imdbId, imdbId, setImdbId);
	TVDB_PROPERTY(QDateTime, lastUpdated, lastUpdated, setLastUpdated);

	Q_PROPERTY(qint64 id READ id WRITE setId NOTIFY idChanged);
	Q_PROPERTY(qint64 showId READ showId WRITE setShowId NOTIFY showIdChanged);
	Q_PROPERTY(qint64 seasonId READ seasonId WRITE setSeasonId NOTIFY seasonIdChanged);
	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged);
	Q_PROPERTY(QString overview READ overview WRITE setOverview NOTIFY overviewChanged);
	Q_PROPERTY(int season READ season WRITE setSeason NOTIFY seasonChanged);
	Q_PROPERTY(int episode READ episode WRITE setEpisode NOTIFY episodeChanged);
	Q_PROPERTY(QString director READ director WRITE setDirector NOTIFY directorChanged);
	Q_PROPERTY(QStringList guestStars READ guestStars WRITE setGuestStars NOTIFY guestStarsChanged);
	Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged);
	Q_PROPERTY(QString productionCode READ productionCode WRITE setProductionCode NOTIFY productionCodeChanged);
	Q_PROPERTY(QString rating READ rating WRITE setRating NOTIFY ratingChanged);
	Q_PROPERTY(QString writer READ writer WRITE setWriter NOTIFY writerChanged);
	Q_PROPERTY(QDateTime firstAired READ firstAired WRITE setFirstAired NOTIFY firstAiredChanged);
	Q_PROPERTY(QString dvdChapter READ dvdChapter WRITE setDvdChapter NOTIFY dvdChapterChanged);
	Q_PROPERTY(QString dvdDiscId READ dvdDiscId WRITE setDvdDiscId NOTIFY dvdDiscIdChanged);
	Q_PROPERTY(QString dvdEpisodeNumber READ dvdEpisodeNumber WRITE setDvdEpisodeNumber NOTIFY dvdEpisodeNumberChanged);
	Q_PROPERTY(QString dvdSeason READ dvdSeason WRITE setDvdSeason NOTIFY dvdSeasonChanged);
	Q_PROPERTY(QString image READ image WRITE setImage NOTIFY imageChanged);
	Q_PROPERTY(QString airsAfterSeason READ airsAfterSeason WRITE setAirsAfterSeason NOTIFY airsAfterSeasonChanged);
	Q_PROPERTY(QString airsBeforeSeason READ airsBeforeSeason WRITE setAirsBeforeSeason NOTIFY airsBeforeSeasonChanged);
	Q_PROPERTY(QString airsBeforeEpisode READ airsBeforeEpisode WRITE setAirsBeforeEpisode NOTIFY airsBeforeEpisodeChanged);
	Q_PROPERTY(int combinedEpisode READ combinedEpisode WRITE setCombinedEpisode NOTIFY combinedEpisodeChanged);
	Q_PROPERTY(int combinedSeason READ combinedSeason WRITE setCombinedSeason NOTIFY combinedSeasonChanged);
	Q_PROPERTY(int absoluteNumber READ absoluteNumber WRITE setAbsoluteNumber NOTIFY absoluteNumberChanged);
	Q_PROPERTY(QString epImgFlag READ epImgFlag WRITE setEpImgFlag NOTIFY epImgFlagChanged);
	Q_PROPERTY(QString imdbId READ imdbId WRITE setImdbId NOTIFY imdbIdChanged);
	Q_PROPERTY(QDateTime lastUpdated READ lastUpdated WRITE setLastUpdated NOTIFY lastUpdatedChanged);

    signals:
	void idChanged();
	void showIdChanged();
	void seasonIdChanged();
	void nameChanged();
	void overviewChanged();
	void seasonChanged();
	void episodeChanged();
	void directorChanged();
	void guestStarsChanged();
	void languageChanged();
	void productionCodeChanged();
	void ratingChanged();
	void writerChanged();
	void firstAiredChanged();
	void dvdChapterChanged();
	void dvdDiscIdChanged();
	void dvdEpisodeNumberChanged();
	void dvdSeasonChanged();
	void imageChanged();
	void airsAfterSeasonChanged();
	void airsBeforeSeasonChanged();
	void airsBeforeEpisodeChanged();
	void combinedEpisodeChanged();
	void combinedSeasonChanged();
	void absoluteNumberChanged();
	void epImgFlagChanged();
	void imdbIdChanged();
	void lastUpdatedChanged();

    public:
	Episode(QObject *parent = NULL);
	Episode(const QString & xml, QObject *parent = NULL);
	Episode(const QDomNode & node, QObject *parent = NULL);
	~Episode();

	bool isNull();

	static QList< Episode * > parseEpisodes(const QString & xml);
	static QList< Episode * > parseEpisodes(const QDomNode & node);

    private:
	void init();
	void init(const QDomNode &node);
    };

    class QTTVDB_EXPORT Show : public QObject {
	Q_OBJECT


	TVDB_PROPERTY(qint64, id, id, setId);
	TVDB_PROPERTY(QString, name, name, setName);
	TVDB_PROPERTY(QString, overview, overview, setOverview);
	TVDB_PROPERTY(QStringList, genre, genre, setGenre);
	TVDB_PROPERTY(QStringList, actors, actors, setActors);
	TVDB_PROPERTY(QString, network, network, setNetwork);
	TVDB_PROPERTY(QString, contentRating, contentRating, setContentRating);
	TVDB_PROPERTY(QString, rating, rating, setRating);
	TVDB_PROPERTY(QTime, runtime, runtime, setRuntime);
	TVDB_PROPERTY(QString, status, status, setStatus);
	TVDB_PROPERTY(QString, language, language, setLanguage);
	TVDB_PROPERTY(QDateTime, firstAired, firstAired, setFirstAired);
	TVDB_PROPERTY(QString, airsDay, airsDay, setAirsDay);
	TVDB_PROPERTY(QTime, airsTime, airsTime, setAirsTime);
	TVDB_PROPERTY(QString, banner, banner, setBanner);
	TVDB_PROPERTY(QString, poster, poster, setPoster);
	TVDB_PROPERTY(QString, fanArt, fanArt, setFanArt);
	TVDB_PROPERTY(QString, imdbId, imdbId, setImdbId);
	TVDB_PROPERTY(QString, seriesId, seriesId, setSeriesId);
	TVDB_PROPERTY(QString, zap2ItId, zap2ItId, setZap2ItId);
	TVDB_PROPERTY(QDateTime, lastUpdated, lastUpdated, setLastUpdated);

	Q_PROPERTY(qint64 id READ id WRITE setId NOTIFY idChanged);
	Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged);
	Q_PROPERTY(QString overview READ overview WRITE setOverview NOTIFY overviewChanged);
	Q_PROPERTY(QStringList genre READ genre WRITE setGenre NOTIFY genreChanged);
	Q_PROPERTY(QStringList actors READ actors WRITE setActors NOTIFY actorsChanged);
	Q_PROPERTY(QString network READ network WRITE setNetwork NOTIFY networkChanged);
	Q_PROPERTY(QString contentRating READ contentRating WRITE setContentRating NOTIFY contentRatingChanged);
	Q_PROPERTY(QString rating READ rating WRITE setRating NOTIFY ratingChanged);
	Q_PROPERTY(QTime runtime READ runtime WRITE setRuntime NOTIFY runtimeChanged);
	Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged);
	Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged);
	Q_PROPERTY(QDateTime firstAired READ firstAired WRITE setFirstAired NOTIFY firstAiredChanged);
	Q_PROPERTY(QString airsDay READ airsDay WRITE setAirsDay NOTIFY airsDayChanged);
	Q_PROPERTY(QTime airsTime READ airsTime WRITE setAirsTime NOTIFY airsTimeChanged);
	Q_PROPERTY(QString banner READ banner WRITE setBanner NOTIFY bannerChanged);
	Q_PROPERTY(QString poster READ poster WRITE setPoster NOTIFY posterChanged);
	Q_PROPERTY(QString fanArt READ fanArt WRITE setFanArt NOTIFY fanArtChanged);
	Q_PROPERTY(QString imdbId READ imdbId WRITE setImdbId NOTIFY imdbIdChanged);
	Q_PROPERTY(QString seriesId READ seriesId WRITE setSeriesId NOTIFY seriesIdChanged);
	Q_PROPERTY(QString zap2ItId READ zap2ItId WRITE setZap2ItId NOTIFY zap2ItIdChanged);
	Q_PROPERTY(QDateTime lastUpdated READ lastUpdated WRITE setLastUpdated NOTIFY lastUpdatedChanged);

    signals:
	void idChanged();
	void nameChanged();
	void overviewChanged();
	void genreChanged();
	void actorsChanged();
	void networkChanged();
	void contentRatingChanged();
	void ratingChanged();
	void runtimeChanged();
	void statusChanged();
	void languageChanged();
	void firstAiredChanged();
	void airsDayChanged();
	void airsTimeChanged();
	void bannerChanged();
	void posterChanged();
	void fanArtChanged();
	void imdbIdChanged();
	void seriesIdChanged();
	void zap2ItIdChanged();
	void lastUpdatedChanged();

    public:
	Show(QObject *parent = NULL);
	Show(const QString & xml, QObject *parent = NULL);
	Show(const QDomNode & node, QObject *parent = NULL);
	~Show();

	bool isNull();

	static QList< Show * > parseShows(const QString & xml);
	static QList< Show * > parseShows(const QDomNode & node);

    private:
	void init();
	void init(const QDomNode &node);
    };

    class QTTVDB_EXPORT Banner : public QObject {
	Q_OBJECT


	TVDB_PROPERTY(qint64, id, id, setId);
	TVDB_PROPERTY(QString, path, path, setPath);
	TVDB_PROPERTY(QString, type, type, setType);
	TVDB_PROPERTY(QString, type2, type2, setType2);
	TVDB_PROPERTY(QString, language, language, setLanguage);
	TVDB_PROPERTY(QString, season, season, setSeason);

	Q_PROPERTY(qint64 id READ id WRITE setId NOTIFY idChanged);
	Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged);
	Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged);
	Q_PROPERTY(QString type2 READ type2 WRITE setType2 NOTIFY type2Changed);
	Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged);
	Q_PROPERTY(QString season READ season WRITE setSeason NOTIFY seasonChanged);

    signals:
	void idChanged();
	void pathChanged();
	void typeChanged();
	void type2Changed();
	void languageChanged();
	void seasonChanged();

    public:
	Banner(QObject *parent = NULL);
	Banner(const QString & xml, QObject *parent = NULL);
	Banner(const QDomNode & node, QObject *parent = NULL);
	~Banner();

	bool isNull();

	static QList< Banner * > parseBanners(const QString & xml);
	static QList< Banner * > parseBanners(const QDomNode & node);

    private:
	void init();
	void init(const QDomNode &node);
    };
};

Q_DECLARE_METATYPE(QtTvDB::Mirrors *);
Q_DECLARE_METATYPE(QtTvDB::Episode *);
Q_DECLARE_METATYPE(QtTvDB::Show *);
Q_DECLARE_METATYPE(QtTvDB::Banner *);

#endif // QTTVDB_H

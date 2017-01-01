#include "MusicSong.h"

#include <QMediaMetaData>
#include <QTime>

MusicSong::MusicSong(QUrl url, QObject* parent)
    :url_(url)
    ,songTitle_("")
    ,songInterpret_("")
    ,songDuration_(0)
    ,albumSongNumber_(0)
    ,albumSongCount_(0)
    ,albumTitle_("")
    ,albumInterpret_("")
    ,loaded_(false)
{
    mp_ = new QMediaPlayer();
    mp_->setMedia(url_);

    // Ist die Datei geladen wird der Slot ausgel�st und die MetaDaten geladen
    connect(mp_, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(onMediaStatusChanged(QMediaPlayer::MediaStatus)));
}

MusicSong::~MusicSong()
{
    delete mp_;
}

bool MusicSong::isLoaded()
{
    return loaded_;
}

QUrl MusicSong::getUrl()
{
    return url_;
}

QString MusicSong::getSongTitle()
{
    return songTitle_;
}

QString MusicSong::getSongInterpret()
{
    return songInterpret_;
}

qint64 MusicSong::getSongDuration()
{
    return songDuration_;
}

QString MusicSong::convertSongDurationToMinuteSecond(qint64 millisecond)
{
    int secondsTotal = millisecond / 1000;
    int minutes = secondsTotal / 60;
    int seconds = secondsTotal % 60;
    QString secondsString = "";
    if (seconds < 10) secondsString = "0" + QString::number(seconds);
    else secondsString = QString::number(seconds);
    QString duration = QString::number(minutes) + ":" + secondsString;
    return duration;
}

int MusicSong::getAlbumSongNumber()
{
    return albumSongNumber_;
}

int MusicSong::getAlbumSongCount()
{
    return albumSongCount_;
}

QString MusicSong::getAlbumTitle()
{
    return albumTitle_;
}

QString MusicSong::getAlbumInterpret()
{
    return albumInterpret_;
}

void MusicSong::onMediaStatusChanged(const QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::MediaStatus::LoadedMedia)
    {
        songTitle_ = mp_->metaData(QMediaMetaData::Title).toString();
        songInterpret_ = mp_->metaData(QMediaMetaData::Author).toString();
        songDuration_ = mp_->metaData(QMediaMetaData::Duration).value<qint64>();

        albumSongNumber_ = mp_->metaData(QMediaMetaData::TrackNumber).toInt();
        albumSongCount_ = mp_->metaData(QMediaMetaData::TrackCount).toInt();
        albumTitle_ = mp_->metaData(QMediaMetaData::AlbumTitle).toString();
        albumInterpret_ = mp_->metaData(QMediaMetaData::AlbumArtist).toString();
        loaded_ = true;
        //songCoverArt_ = new QImage(mp_->metaData(QMediaMetaData::CoverArtImage).value<QImage>());
    }
}

/*
Common attributes
Value	        Description	Type
Title	        The title of the media.	QString
SubTitle	    The sub-title of the media.	QString
Author	        The authors of the media.	QStringList
Comment	        A user comment about the media.	QString
Description	    A description of the media.	QString
Category	    The category of the media.	QStringList
Genre	        The genre of the media.	QStringList
Year	        The year of release of the media.	int
Date	        The date of the media.	QDate.
UserRating	    A user rating of the media.	int [0..100]
Keywords	    A list of keywords describing the media.	QStringList
Language	    The language of media, as an ISO 639-2 code.	QString
Publisher	    The publisher of the media.	QString
Copyright	    The media's copyright notice.	QString
ParentalRating	The parental rating of the media.	QString
RatingOrganization	The organization responsible for the parental rating of the media.	QString

Media attributes
Size	        The size in bytes of the media.	qint64
MediaType	    The type of the media (audio, video, etc).	QString
Duration	    The duration in millseconds of the media.	qint64

Audio attributes
AudioBitRate	    The bit rate of the media's audio stream in bits per second.	int
AudioCodec	        The codec of the media's audio stream.	QString
AverageLevel	    The average volume level of the media.	int
ChannelCount	    The number of channels in the media's audio stream.	int
PeakValue	        The peak volume of the media's audio stream.	int
SampleRate	        The sample rate of the media's audio stream in hertz.	int

Music attributes
AlbumTitle	        The title of the album the media belongs to.	QString
AlbumArtist	        The principal artist of the album the media belongs to.	QString
ContributingArtist	The artists contributing to the media.	QStringList
Composer	        The composer of the media.	QStringList
Conductor	        The conductor of the media.	QString
Lyrics	            The lyrics to the media.	QString
Mood	            The mood of the media.	QString
TrackNumber         The track number of the media.	int
TrackCount	        The number of tracks on the album containing the media.	int
CoverArtUrlSmall	The URL of a small cover art image.	QUrl
CoverArtUrlLarge	The URL of a large cover art image.	QUrl
CoverArtImage	    An embedded cover art image.	QImage
*/
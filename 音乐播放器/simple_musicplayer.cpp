#include "simple_musicplayer.h"
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFileDialog>


simple_musicplayer::simple_musicplayer(QWidget *parent)
    : QWidget(parent)
{
    
    ui.setupUi(this);
    initWidget();
    //设置总时间
    connect(mediaPlayer, &QMediaPlayer::durationChanged, this, [=](qint64 duration) {
        ctimeLab->setText(QString("%1:%2").arg(duration / 1000 / 60, 2, 10, QChar('0')).arg(duration / 1000 % 60));
        hSlider->setRange(0, duration);
        });
    //设置当前时间
    connect(mediaPlayer, &QMediaPlayer::positionChanged, this, [=](qint64 pos) {
        ltimeLab->setText(QString("%1:%2").arg(pos / 1000 / 60, 2, 10, QChar('0')).arg(pos / 1000 % 60, 2, 10, QChar('0')));
        hSlider->setValue(pos);
        
        });
    //设置进度条
    connect(hSlider, &QSlider::sliderMoved, mediaPlayer, &QMediaPlayer::setPosition);
    //设置顺序播放
    connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            // 音频播放完毕
            curPlayIndex = (curPlayIndex + 1) % musicList.size();
            displayWidget->setCurrentRow(curPlayIndex);
            mediaPlayer->setSource(musicList[curPlayIndex]);
            mediaPlayer->play();
        }
        });
}

simple_musicplayer::~simple_musicplayer()
{
    
}
//根据按钮大小缩放图片
void btnloadimg(QPushButton *_Btn,const char path[]) {
    _Btn->setFixedSize(40, 40);
    QPixmap pixmap(path);
    pixmap = pixmap.scaled(_Btn->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QIcon icon(pixmap);
    _Btn->setIcon(icon);
    _Btn->setIconSize(pixmap.size());
    _Btn->setAttribute(Qt::WA_TranslucentBackground);
}
void simple_musicplayer::initWidget()
{   
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->resize(300, 300);
    fileBtn = new QPushButton(this);
    listBtn = new QPushButton(this);
    preBtn = new QPushButton(this);
    playBtn = new QPushButton(this);
    nextBtn = new QPushButton(this);
    audioBtn = new QPushButton(this);
    displayWidget = new QListWidget(this);
    hSlider = new QSlider(this);
    vSlider = new QSlider(this);
    ctimeLab = new QLabel("00:00", this);
    ltimeLab = new QLabel("00:00", this);

    hSlider->setOrientation(Qt::Horizontal);
    hSlider->setFixedSize(QSize(230, 15));
    vSlider->setFixedSize(QSize(15, 200));
    vSlider->move(this->width()-50, 30);
    vSlider->hide();

    btnloadimg(fileBtn, ":/resource/file_btn.png");
    btnloadimg(listBtn, ":/resource/list_btn.png");
    btnloadimg(preBtn, ":/resource/pre_btn.png");
    btnloadimg(playBtn, ":/resource/pause_btn.png");
    btnloadimg(nextBtn, ":/resource/next_btn.png");
    btnloadimg(audioBtn, ":/resource/audio_btn.png");

    connect(fileBtn, &QPushButton::clicked, this, &simple_musicplayer::on_clicked_fileBtn);
    connect(listBtn, &QPushButton::clicked, this, &simple_musicplayer::on_clicked_listBtn);
    connect(preBtn, &QPushButton::clicked, this, &simple_musicplayer::on_clicked_preBtn);
    connect(playBtn, &QPushButton::clicked, this, &simple_musicplayer::on_clicked_playBtn);
    connect(nextBtn, &QPushButton::clicked, this, &simple_musicplayer::on_clicked_nextBtn);
    connect(audioBtn, &QPushButton::clicked, this, &simple_musicplayer::on_clicked_audioBtn);
    //connect(displayWidget, &QListWidget::currentRowChanged, this, &simple_musicplayer::item_changed);
    connect(displayWidget, &QListWidget::doubleClicked, this, &simple_musicplayer::item_changed);

    QHBoxLayout* hlayout = new QHBoxLayout();
    QHBoxLayout* hlayout1 = new QHBoxLayout();
    QVBoxLayout* vlayout = new QVBoxLayout();
    QGridLayout* gridlayout = new QGridLayout(this);
    

    gridlayout->addWidget(displayWidget, 0, 0);
    vlayout->addWidget(hSlider);
    hlayout->addWidget(fileBtn);
    hlayout->addWidget(listBtn);
    hlayout->addWidget(preBtn);
    hlayout->addWidget(playBtn);
    hlayout->addWidget(nextBtn);
    hlayout->addWidget(audioBtn);
    hlayout1->addWidget(ltimeLab);
    hlayout1->addWidget(ctimeLab);
    gridlayout->addLayout(hlayout1, 1, 0);
    gridlayout->addLayout(vlayout, 2, 0);
    gridlayout->addLayout(hlayout, 3, 0);
    hlayout->setAlignment(Qt::AlignBottom);
    setLayout(gridlayout);
    
    audioOutput = new QAudioOutput(this);
    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setAudioOutput(audioOutput);
}

void simple_musicplayer::on_clicked_fileBtn()
{
    
    auto path = QFileDialog::getExistingDirectory(this, QString("请选择音乐所在目录"), "");
    QDir dir(path);
   /* auto musiclist=dir.entryList(QStringList() << "*.mp3" << "*.wav");
    displayWidget->addItems(musiclist);*/
    auto fileInfoList=dir.entryInfoList(QStringList() << "*.mp3" << "*.wav");
    for (auto i = fileInfoList.begin(); i < fileInfoList.end(); i++) {
        const QFileInfo file = *i;
        displayWidget->addItem(file.fileName());
        musicList.push_back(file.filePath()); 
        qInfo() << musicList.back();
    }
    displayWidget->setCurrentRow(0);
}

void simple_musicplayer::on_clicked_listBtn()
{
}

void simple_musicplayer::on_clicked_preBtn()
{
    if (!musicList.isEmpty()) {
        if (curPlayIndex == 0) {
            curPlayIndex = musicList.size();
        }
        curPlayIndex = (curPlayIndex - 1) % musicList.size();
        displayWidget->setCurrentRow(curPlayIndex);
        mediaPlayer->setSource(musicList[curPlayIndex]);
        mediaPlayer->play();
    }  
}

void simple_musicplayer::on_clicked_playBtn()
{
    
    if (!musicList.isEmpty()) {
        switch (mediaPlayer->playbackState()) {
        case QMediaPlayer::PlaybackState::StoppedState:
            curPlayIndex = displayWidget->currentRow();
            mediaPlayer->setSource(musicList[curPlayIndex]);
            mediaPlayer->play();
            btnloadimg(playBtn, ":/resource/play_btn.png");
            break;
        case QMediaPlayer::PlaybackState::PlayingState:
            mediaPlayer->pause();
            btnloadimg(playBtn, ":/resource/pause_btn.png");
            break;
        case QMediaPlayer::PlaybackState::PausedState:
            mediaPlayer->play();
            btnloadimg(playBtn, ":/resource/play_btn.png");
            break;
        }
    } 
}

void simple_musicplayer::on_clicked_nextBtn()
{
    if (!musicList.isEmpty()) {
        curPlayIndex = (curPlayIndex + 1) % musicList.size();
        displayWidget->setCurrentRow(curPlayIndex);
        mediaPlayer->setSource(musicList[curPlayIndex]);
        mediaPlayer->play();
    }
}

void simple_musicplayer::on_clicked_audioBtn()
{
    static bool count = true;
    if (count) {
        vSlider->show();
        count=false;
    }
    else{
        vSlider->hide();
        count = true;
    }
    
}

void simple_musicplayer::item_changed() {
    qInfo() << displayWidget->currentRow();
    curPlayIndex = displayWidget->currentRow();
    if (!musicList.isEmpty()) {
        btnloadimg(playBtn, ":/resource/play_btn.png");
        displayWidget->setCurrentRow(curPlayIndex);
        mediaPlayer->setSource(musicList[curPlayIndex]);
        mediaPlayer->play();
    }
}

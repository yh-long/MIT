#pragma once

#include <QtWidgets/QWidget>
#include "ui_simple_musicplayer.h"
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QSlider>
#include <QMediaPlayer>
#include <QAudioOutput>

class simple_musicplayer : public QWidget
{
    Q_OBJECT

public:
    simple_musicplayer(QWidget *parent = nullptr);
    ~simple_musicplayer();
    void initWidget();
    

private:
    Ui::simple_musicplayerClass ui;
    QPushButton *fileBtn;
    QPushButton *listBtn;
    QPushButton *preBtn;
    QPushButton *playBtn;
    QPushButton *nextBtn;
    QPushButton *audioBtn;
    QListWidget* displayWidget;
    QSlider* hSlider;
    QSlider* vSlider;
    QList<QUrl> musicList;
    QAudioOutput *audioOutput;
    QMediaPlayer *mediaPlayer;
    QLabel* ctimeLab;
    QLabel* ltimeLab;
    int curPlayIndex=0;

private slots:
    void on_clicked_fileBtn();
    void on_clicked_listBtn();
    void on_clicked_preBtn();
    void on_clicked_playBtn();
    void on_clicked_nextBtn();
    void on_clicked_audioBtn();
    void item_changed();


};

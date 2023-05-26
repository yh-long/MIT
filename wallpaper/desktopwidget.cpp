#include "desktopwidget.h"
#include <QHboxLayout>
#include <qt_windows.h>
#include <QDebug>
DesktopWidget::DesktopWidget(QWidget* parent):bkLabel(new QLabel)
{
	setWindowFlag(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(bkLabel);
	setPixmap(":/resource/IMG_2.JPG");
	setAllWallpaper();
}

void DesktopWidget::setAllWallpaper()
{
	HWND desktopHwd=(HWND)FindWindow(L"Program", L"Program Manager");
	if (!desktopHwd) {
		qDebug() << desktopHwd;
	}
	SetParent((HWND)this->winId(), desktopHwd);
}

void DesktopWidget::setPixmap(const QString& fileName)	
{
	if (QPixmap(fileName).isNull()) {
		return;
	}
	bkPixmap.load(fileName);
	bkLabel->setPixmap(bkPixmap);
	this->hide();
	this->showFullScreen();
}

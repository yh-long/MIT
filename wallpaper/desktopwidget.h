#pragma once
#include <qwidget.h>
#include <QLabel>
#include <QPixmap>
class DesktopWidget :
    public QWidget
{
	Q_OBJECT
public:
    DesktopWidget(QWidget* parent = nullptr);
	~DesktopWidget()
	{

	}
	void setAllWallpaper();
	void setPixmap(const QString &fileName);
private:
	QLabel* bkLabel;
	QPixmap	bkPixmap;
};


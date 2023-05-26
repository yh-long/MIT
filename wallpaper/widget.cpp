#include "widget.h"
#include <QTimer>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QDebug>
#include <QFileDialog>
Widget::Widget(QWidget* parent) :QWidget(parent),roleLabel(new QLabel(this)),curFrame(0) ,desktopWidget(new DesktopWidget){
	//背景透明
	setWindowFlags(Qt::WindowType::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	//定时器
	QTimer* updateTimer = new QTimer(this);
	updateTimer->callOnTimeout(this, &Widget::updateRoleAnimation);
	updateTimer->start(500);
	//updateRoleAnimation();
	//设置阴影
	QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
	effect->setColor(QColor(230, 231, 230, 220));
	
	this->setGraphicsEffect(effect);
	this->installEventFilter(this);

	roleLabel->resize(500, 500);
	initBtn();
	desktopWidget->show();
}
Widget::~Widget()
{
}

void Widget::updateRoleAnimation()
{
	QString qss("background-repeat:no-repeat;");
	roleLabel->setStyleSheet(qss+QString("background-image:url(:/resource/IMG_%1.JPG);").arg(curFrame));
	curFrame = (curFrame + 1) % 4;
}

bool Widget::eventFilter(QObject* watched, QEvent* ev)
{
	QMouseEvent* mouseev = static_cast<QMouseEvent*>(ev);
	static QPoint bgpos;
	if (ev->type() == QEvent::MouseButtonPress) {
		bgpos = mouseev->globalPos() - this->pos();
	
	}
	if (ev->type() == QEvent::MouseMove && mouseev->buttons() & Qt::MouseButton::LeftButton) {
		this->move(mouseev->globalPos() - bgpos);
		
	}
	return false;
}

void Widget::initBtn()
{
	closeBtn = new QPushButton(this);
	cutBtn = new QPushButton(this);
	openBtn = new QPushButton(this);
	closeBtn->setGeometry(300, 200, 32, 32);
	cutBtn->setGeometry(300, 240, 32, 32);
	openBtn->setGeometry(300, 280, 32, 32);
	closeBtn->setObjectName("closeBtn");
	QString qss("background-repeat:no-repeat;");
	//closeBtn->setStyleSheet(qss + "background-image:url(:/resource/IMG_2.JPG);");
	cutBtn->setStyleSheet(qss + "background-image:url(:/resource/IMG_2.JPG);");
	openBtn->setStyleSheet(qss + "background-image:url(:/resource/IMG_2.JPG);");
	this->setStyleSheet("QPushButton{background-color:rgb(64,173,250);\
						border:none;border-radius:5px;}\
						QPushButton#closeBtn:hover{background-color:rgb(233,31,48);}");
	connect(closeBtn, &QPushButton::pressed, this, &Widget::close);
	connect(openBtn, &QPushButton::pressed, this, [=]() {
		QString filename = QFileDialog::getOpenFileName(nullptr, "选择图片");
		if (filename.isEmpty()) {
			return;
		}
		desktopWidget->setPixmap(filename);
		});
}

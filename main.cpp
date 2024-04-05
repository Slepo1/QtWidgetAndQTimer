#include <QLoggingCategory> // подключаем штуку для вывода в консоль qDebug()
#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true); // для вывода в консоль qDebug()
	QApplication a(argc, argv);
	Widget w;
	w.show();

	//QObject::connect(&questButton, SIGNAL(clickedQuest(bool checked)), &w, SLOT(on_questButton_clicked(bool checked))); // сигнал clicked

	return a.exec();
}

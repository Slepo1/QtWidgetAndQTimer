#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget//
{
	Q_OBJECT
private:
	QString strInput;
	QString strDisplay; // outputTextEdit вот сюда эта строка нужна
	int sizeDis; // размер строки strDisplay
	QTimer *tmr; // Адресная переменная таймера
	int i = -1; // нужно для позиционирования в strDisplay, а также она будет меняться при каждом вызове слота для QTimer'a
public:
	Widget(QWidget *parent = nullptr);
	~Widget();
signals:
	void clickedQuest(bool checked);

private slots:
	void on_inputButton_clicked();

	void on_clearButton_clicked();

	void on_startThreadButton_clicked();

	void on_questButton_clicked(bool checked);

	void on_inputTextEdit_textChanged();

	void updateTime(); // слот для обновления текста в оутпуте)))

private:
	Ui::Widget *ui;
};
#endif // WIDGET_H

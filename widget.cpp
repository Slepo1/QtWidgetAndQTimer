#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::Widget)
{
	ui->setupUi(this);

	tmr = new QTimer(this);
	tmr->setInterval(2000); // каждые 2 сек будем отправлять сигнал
	connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime())); // Подключаем сигнал таймера к нашему слоту // а как в таймаут закинуть int который будет передаваться
	//tmr->start(); // запуск таймера, который будет запускаться в слоте по нажатию на кнопку!!

	this->setWindowTitle("Test example");
	ui->inputButton->setText("Input");
	ui->clearButton->setText("Clear");
	ui->startThreadButton->setText("Start all*"); // эта кнопка делает звездочки между всеми элементами
	ui->questButton->setText("Start quest*");


	this->strDisplay = ui->outputTextEdit->toPlainText();

}

Widget::~Widget()
{
	delete ui;
}

void Widget::on_inputButton_clicked() // по задумке когда переключатель активен, текст из инпута напрямую транслируется в оутпут
{
	qDebug() << "Clicked on 'Input' button";

	this->strInput = ui->inputTextEdit->toPlainText();
	this->strDisplay = this->strInput;
	ui->outputTextEdit->setPlainText(strDisplay);

	//qDebug() << strInput;
}

// теперь надо будет запустить новый поток, который будет менять мой outputTextEdit условно каждую секунду, двигая звездочку вправо на элемент

void Widget::on_clearButton_clicked()
{
	qDebug() << "Clicked on 'Clear' button";
	strDisplay.clear();
	ui->outputTextEdit->setPlainText(strDisplay);
}


void Widget::on_startThreadButton_clicked()
{
	int sizeStr = strDisplay.size();
	for(int i = 0; i < sizeStr*2 + 1; i+=2)
	{
		//qDebug() << i;
		strDisplay.insert(i, "*");
	}
	qDebug() << sizeStr;
	qDebug() << strDisplay;
	//strDisplay.insert(strDisplay.size()/2, "*");
	ui->outputTextEdit->setPlainText(strDisplay);
}


void Widget::on_questButton_clicked(bool checked)
{
	// zadacha for 'Start quest*'
	//она будет в виде переключателя, пока она активна поток будет выполнять действие на виджете и завершаться, когда пользователь снова нажмет на неё
	//Тогда надо еще на время checked == true, заблочить кнопки и поле ввода текста
	if(checked == true)
	{
		ui->inputButton->setEnabled(false); // неактивная input кнопка
		ui->startThreadButton->setEnabled(false); // неактивная кнопка start all*
		ui->clearButton->setEnabled(false); // неактивная кнопка clear
		ui->inputTextEdit->setEnabled(false); // неактивное поле ввода
		//ui->outputTextEdit->setPlainText("checked true)");

		// мейби отсюда это убрать нахуй, чтобы осталось в конструкторе, ну пока оставлю тут для теста
		/*tmr = new QTimer(this);
		tmr->setInterval(2000);*/ // каждые 2 сек будем отправлять сигнал
		//connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));// Подключаем сигнал таймера к нашему слоту
		tmr->start(); //по нажатию стартуем подавать сигналы
		// здесь нужен сигнал, который я буду посылать на outputTextEdit
		//emit quest(); //Здесь отправляется сигнал на активацию алгоритма со звёздочкой
	}
	else
	{
		ui->inputButton->setEnabled(true); // активная input кнопка
		ui->startThreadButton->setEnabled(true); // активная кнопка start all*
		ui->clearButton->setEnabled(true); // активная кнопка clear
		ui->inputTextEdit->setEnabled(true); // активное поле ввода
		// а здесь нужен дисконект наверно
		tmr->stop(); // ну не дисконект а стоп!!

	}
}

// нужжен новый слот в котором будет устанавливаться новый setPlainText для оутпута, а сигнал будет посылаться от QTimer'a , условно каждую секунду, потом будет происходить дисконект

/*void Widget::clickedQuest(bool checked)
{


}*/

void Widget::updateTime()
{
	i++;
	// могу ли я давать сигналу аргумент, если он в нем не предусмотрен??, Да могу через setProperties
	// отсчет времени надо вести как-то)))))))) супер пупер вауууу
	if(i > 0)
	{
		this->strDisplay.removeAt(i - 1);
	}
	//qDebug() << tmr->interval();
	//int i =
	this->strDisplay.insert(i, "*");

	ui->outputTextEdit->setPlainText(strDisplay);
	qDebug() << "SLOT UPDATE TIME: " << strDisplay;
	sizeDis = strDisplay.size() - 1;
	if(i == sizeDis)
	{
		this->strDisplay.removeAt(i);
		i = -1;
	}
}

void Widget::on_inputTextEdit_textChanged()
{
	// слот для inputTextEdit, который будет менять outputTextEdit при наборе символов в inputTextEdit
	this->strDisplay = ui->inputTextEdit->toPlainText();
	ui->outputTextEdit->setPlainText(strDisplay);
}


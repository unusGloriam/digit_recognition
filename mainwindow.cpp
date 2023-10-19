#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>

static const auto CONFIRMATION_SYMBOL = "✓";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* настраиваем сцену */
    pScene = new PaintScene();
    ui->graphicsView->setScene(pScene);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
    timer->start(100);

    /* настраиваем кнопки */
    connect(ui->recognizeButton, SIGNAL(clicked()), this, SLOT(onRecognizeButtonClicked()));
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(onClearButtonClicked()));
    connect(ui->learnButton, SIGNAL(clicked()), this, SLOT(onLearnButtonClicked()));

    /* настраиваем ComboBox */
    ui->comboBox->addItem(CONFIRMATION_SYMBOL);

    for (auto i = 0; i < 10; i++) {
        const auto numberString = QString::number(i);
        ui->comboBox->addItem(numberString);
    }

    const auto nItems = ui->comboBox->count();
    for (auto i = 0; i < nItems; i++) {
        ui->comboBox->setItemData(i, Qt::AlignHCenter, Qt::TextAlignmentRole);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::slotTimer() {
    timer->stop();

    ui->graphicsView->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());

    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWindow::onRecognizeButtonClicked() {
    const auto itemName = ui->comboBox->currentText();

    if (!pScene->isPainted()) { // если на сцене ничего не нарисовано
        QMessageBox::warning( // выдадим соответствующее предупреждение
            this,
            tr("Распознавание цифры"),
            tr("Невозможно распознать пустое изображение"),
            QMessageBox::Ok
        );
        return; // и завершим обработку
    }

    const auto pixMap = ui->graphicsView->grab(ui->graphicsView->sceneRect().toRect());
    pixMap.save("image.tmp.png");
}

void MainWindow::onClearButtonClicked() {
    ui->graphicsView->scene()->clear();
    pScene->setPainted(false); // считаем, что теперь на сцене ничего не нарисовано
}

void MainWindow::onLearnButtonClicked() {
    const auto itemName = ui->comboBox->currentText();

    if (!itemName[0].isDigit()) { // если правильная цифра не задана
        const auto path = QFileDialog::getExistingDirectory( // заставим пользователя выбрать каталог
            this,
            tr("Каталог с изображениями"),
            ""
        );

        if (path.isEmpty()) { // если пользователь забил на выбор каталога
            return; // значит мы забиваем на него
        }

        QDir directory(path);
        directory.setNameFilters(QStringList( // указываем искомые расширения
            "*.jpg"
        ));

        directory.setFilter(QDir::NoFilter // указываем, какие объекты выбирать
            | QDir::Files
            | QDir::NoDotAndDotDot
            | QDir::NoSymLinks
        );

        qDebug() << "Scanning: " << directory.path(); // выведем имя каталога, в котором ищем файлы
        const auto files = directory.entryList(); // получаем список подходящих файлов
        for (auto i = 0; i < files.count(); i++) {
            qDebug() << "Found file: " << files[i];
        }

        return;
    }

    const auto digit = itemName[0].toLatin1() - '0'; // реально введенная цифра

    if (!pScene->isPainted()) { // если на сцене ничего не нарисовано
        QMessageBox::warning(
            this,
            tr("Обучение цифры"),
            tr("Для начала необходимо ввести цифру"),
            QMessageBox::Ok
        );
        return;
    }




}

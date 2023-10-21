#include "mainwindow.h"

#include "main.h"
#include "perceptron.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QGraphicsTextItem>

static const auto CONFIRMATION_SYMBOL = "✓";
static const auto TEMP_FILE_NAME = "image.tmp.jpg";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* настраиваем сцену */
    pScene = new PaintScene();
    ui->graphicsView->setScene(pScene);
    ui->graphicsView->setBackgroundBrush(Qt::white);

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

    ui->graphicsView->setSceneRect( // задаем границы сцены
        1, // убираем серую границу сверху
        1, // убираем серую границу слева
        ui->graphicsView->geometry().width() - 2, // убираем серую границу справа
        ui->graphicsView->geometry().height() - 2 // убираем серую границу снизу
    );

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

    /* уменьшим изображение до 28х28 и сохраним */
    const auto pixMap = ui->graphicsView->grab(ui->graphicsView->sceneRect().toRect());
    const auto scaledPixmap = pixMap.scaled(QSize(28, 28)); // пропорционально изменим размер изображения
    scaledPixmap.save(TEMP_FILE_NAME); // сохраним изображение, нарисованное на сцене

    /* откроем изображение и сформируем матрицу признаков */
    QImage image(TEMP_FILE_NAME); // открываем изображение

    Matrix weights; // матрица для хранения
    const auto width = image.width(); // узнаем ширину изображения (в теории 28, но лучше посчитаем)
    const auto height = image.height(); // узнаем высоту изображения (в теории 28, но лучше посчитаем)

    uint32_t nWhites = 0;

    for (auto h = 0; h < height; h++) {
        auto* rowData = (QRgb*) image.scanLine(h); // получаем строку пикселей

        for (auto w = 0; w < width; w++) {
            QRgb pixelData = rowData[w]; // получаем информацию о пикселе

            const auto red = qRed(pixelData); // определяем составляющую красного цвета
            const auto green = qGreen(pixelData); // определяем составляющую зеленого цвета
            const auto blue = qBlue(pixelData); // определяем составляющую синего цвета

            if (true // если это белый цвет
                && (red >= 200) // красный полный
                && (green >= 200) // зеленый полный
                && (blue >= 200) // синий полный
            ) {
                weights[h][w] = 0; // сбрасываем признак в матрице
                nWhites++;
            }
            else {
                weights[h][w] = 1; // устанавливаем признак в матрице
            }
        }
    }

    Perceptron perceptron;
    perceptron.set_input_matrix(weights); // задаем персептрону матрицу весов
    const auto digit = perceptron.recognition(); // распознаем нарисованную цифру

    ui->graphicsView->scene()->clear(); // очищаем сцену от наших художеств

    const auto digitItem = new QGraphicsTextItem(QString::number(digit)); // создадим объект с распознанной цифрой
    digitItem->setPos(-5, -25); // зададим начальную позицию цифры
    digitItem->setScale(4); // зададим масштаб цифры
    digitItem->show(); // отобразим цифру

    ui->graphicsView->scene()->addItem(digitItem); // прикрепим цифру к сцене
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

    // здесь мы должны считать изображение из файла TEMP_FILE_NAME и начать его обучение
    // брать изображение из сцены нельзя, поскольку там отображается распознанная цифра


}

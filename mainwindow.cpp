#include "mainwindow.h"

#include "main.h"
#include "perceptron.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QGraphicsTextItem>

static const auto CONFIRMATION_SYMBOL = "✓";
static const auto TEMP_FILE_NAME = "image.tmp.jpg";
static const auto WEIGHTS_FILE_NAME = "weights.txt";

Perceptron perceptron;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* настраиваем сцену */
    pScene = new PaintScene();
    ui->graphicsView->setScene(pScene);
    ui->graphicsView->setBackgroundBrush(Qt::black);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
    timer->start(100);

    /* настраиваем кнопки */
    connect(ui->recognizeButton, SIGNAL(clicked()), this, SLOT(onRecognizeButtonClicked()));
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(onClearButtonClicked()));
    connect(ui->learnButton, SIGNAL(clicked()), this, SLOT(onLearnButtonClicked()));
    connect(ui->testButton, SIGNAL(clicked()), this, SLOT(onTestButtonClicked()));

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

    /* считываем веса из файла */
    if (QFile::exists(WEIGHTS_FILE_NAME)){ // ...только если он существует
        QVector<Matrix> weights;
        weights.resize(NUM_DIGITS);
        QFile weights_file(WEIGHTS_FILE_NAME);
        if (weights_file.open(QIODevice::ReadWrite)){ // файл открылся - читаем из него
            QTextStream stream(&weights_file);
            for (int i = 0; i < NUM_DIGITS; ++i){ // проходим по 10 числам
                for (int line = 0; line < NUM_ROWS; ++ line){ // проходим по строкам матрицы
                    QString line_str = stream.readLine();
                    QStringList weight_str = line_str.split(' ');
                    for (int weight = 0; weight < NUM_COLUMNS; ++weight){ // проходим по каждому весу
                        weights[i][line][weight] = weight_str[weight].toInt();
                    }
                }
            }
            perceptron.set_weight_matrix(weights);
            weights_file.close();
        }
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

    Matrix input_matrix; // матрица для хранения
    const auto width = image.width(); // узнаем ширину изображения (в теории 28, но лучше посчитаем)
    const auto height = image.height(); // узнаем высоту изображения (в теории 28, но лучше посчитаем)

    for (auto h = 0; h < height; h++) {
        for (auto w = 0; w < width; w++) {
            QColor pixel_color = image.pixelColor(h, w);
            if (pixel_color.red() >= 200 && pixel_color.green() >= 200 && pixel_color.blue() >= 200){ // если белый цвет
                input_matrix[h][w] = 1;
            } else {
                input_matrix[h][w] = 0;
            }
        }
    }    

    perceptron.set_input_matrix(input_matrix); // задаем персептрону матрицу весов
    const auto digit = perceptron.recognition(); // распознаем нарисованную цифру

    ui->graphicsView->scene()->clear(); // очищаем сцену от наших художеств

    const auto digitItem = new QGraphicsTextItem(QString::number(digit)); // создадим объект с распознанной цифрой
    digitItem->setPos(-5, -25); // зададим начальную позицию цифры
    digitItem->setScale(4); // зададим масштаб цифры
    digitItem->setDefaultTextColor(Qt::white);
    digitItem->show(); // отобразим цифру

    ui->graphicsView->scene()->addItem(digitItem); // прикрепим цифру к сцене
}

void MainWindow::onClearButtonClicked() {
    ui->graphicsView->scene()->clear();
    pScene->setPainted(false); // считаем, что теперь на сцене ничего не нарисовано
}

void MainWindow::onLearnButtonClicked() {
    const auto itemName = ui->comboBox->currentText();

    if (!itemName[0].isDigit()) { // если правильная цифра не задана => пользователь хочет учить по выборке из jpg картинок
        const auto path = QFileDialog::getExistingDirectory( // заставим пользователя выбрать каталог
            this,
            tr("Каталог с изображениями"),
            ""
        );

        if (path.isEmpty()) { // если пользователь забил на выбор каталога
            return; // значит мы забиваем на него
        }

        QDir full_dataset_directory(path);

        QStringList dir_filter;
        dir_filter << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9";
        full_dataset_directory.setNameFilters(dir_filter); // картинки для разных цифр выборки должны быть помещены в соответствующие директории

        // учим
        // составляем матрицу обучения
        QVector<QVector<Matrix>> num_dataset; // вектор векторов матриц входных сигналов для каждой цифры выборки
        num_dataset.resize(10);
        for (int i = 0; i < 10; ++i) { // проходим по 10 векторам, каждый - с выборкой для соответствующей цифры
            //num_dataset.push_back(QVector<Matrix>());
            QDir current_num_dir(path + "/" + static_cast<QChar>(i + '0')); // настроили путь к директории с выборками очередной цифры
            current_num_dir.setNameFilters(QStringList( // указываем искомые расширения
                    "*.jpg"
            ));
            current_num_dir.setFilter(QDir::NoFilter // указываем, какие объекты выбирать
                | QDir::Files
                | QDir::NoDotAndDotDot
                | QDir::NoSymLinks
            );
            const auto files = current_num_dir.entryList();
            num_dataset[i].resize(files.count());
            for (int j = 0; j < files.count(); ++j) { // проходим по содержимому папки с выборками для конкретной цифры i

                /* откроем изображение и сформируем матрицу признаков */
                QImage image(current_num_dir.absolutePath() + "/" + files[j]); // открываем изображение
                Matrix input_matrix; // матрица для хранения
                const auto width = image.width(); // узнаем ширину изображения
                const auto height = image.height(); // узнаем высоту изображения

                for (auto h = 0; h < height; h++) {
                    for (auto w = 0; w < width; w++) {

                        QColor pixel_color = image.pixelColor(h, w);
                        if (pixel_color.red() >= 200 && pixel_color.green() >= 200 && pixel_color.blue() >= 200){ // если белый цвет
                            input_matrix[h][w] = 1;
                        } else {
                            input_matrix[h][w] = 0;
                        }
                    }
                }

                num_dataset[i][j] = input_matrix;
            }
        }

        Teacher perceptron_teacher(num_dataset); // создали учителя
        perceptron_teacher.teach(); // учитель обучил...
        perceptron.set_weight_matrix(perceptron_teacher.get_weight_matrix()); // ...и передал полученные веса персептрону...
        // ...и мы записали эти веса в текстовый файл, чтобы при след. запуске не переобучать
        if (QFile::exists(WEIGHTS_FILE_NAME)){ // файл с весами уже существует - удалим
            QFile::remove(WEIGHTS_FILE_NAME);
        }
        QFile weights_file(WEIGHTS_FILE_NAME);
        if (weights_file.open(QIODevice::ReadWrite)){ // файл создался и открылся - пишем в него
            QTextStream stream(&weights_file);
            QVector<Matrix> weights_to_write = perceptron_teacher.get_weight_matrix();
            for (int i = 0; i < NUM_DIGITS; ++i){ // проходим по 10 (вроде как) векторам, соотв. цифрам 0-9, с их матрицами весов
                for (size_t line = 0; line < NUM_COLUMNS; ++line){ // проходим по строкам матрицы весов для очередной i цифры
                    for (size_t weight = 0; weight < NUM_ROWS; ++weight){ // проходим по каждому весу в очередной строке очередной матрицы весов
                        stream << weights_to_write[i][line][weight] << " ";
                        stream.flush();
                    }
                    stream << Qt::endl;
                    stream.flush();
                }
            }
            weights_file.close();
        }

        QMessageBox messageBox;
        messageBox.setText("Обучение завершено");
        messageBox.exec();

        return;
    }

    if (!pScene->isPainted()) { // если на сцене ничего не нарисовано
        QMessageBox::warning(
            this,
            tr("Обучение цифры"),
            tr("Для начала необходимо ввести цифру"),
            QMessageBox::Ok
        );
        return;
    }

    // считываем изображение

    QImage image(TEMP_FILE_NAME); // открываем изображение

    Matrix input_matrix; // матрица для хранения
    const auto width = image.width(); // узнаем ширину изображения (в теории 28, но лучше посчитаем)
    const auto height = image.height(); // узнаем высоту изображения (в теории 28, но лучше посчитаем)

    for (auto h = 0; h < height; h++) {
        for (auto w = 0; w < width; w++) {
            QColor pixel_color = image.pixelColor(h, w);
            if (pixel_color.red() >= 200 && pixel_color.green() >= 200 && pixel_color.blue() >= 200){ // если белый цвет
                input_matrix[h][w] = 1;
            } else {
                input_matrix[h][w] = 0;
            }
        }
    }

    // дообучаем по изображению
    perceptron.teach(itemName[0].digitValue());
    // перезапись файла с весами
    if (QFile::exists(WEIGHTS_FILE_NAME)){ // файл с весами уже существует - удалим
        QFile::remove(WEIGHTS_FILE_NAME);
    }
    QFile weights_file(WEIGHTS_FILE_NAME);
    if (weights_file.open(QIODevice::ReadWrite)){ // файл создался и открылся - пишем в него
        QTextStream stream(&weights_file);
        QVector<Matrix> weights_to_write = perceptron.get_weight_matrix();
        for (int i = 0; i < weights_to_write.size(); ++i){ // проходим по 10 (вроде как) векторам, соотв. цифрам 0-9, с их матрицами весов
            for (size_t line = 0; line < weights_to_write[i].size(); ++line){ // проходим по строкам матрицы весов для очередной i цифры
                for (size_t weight = 0; weight < weights_to_write[i][line].size(); ++weight){ // проходим по каждому весу в очередной строке очередной матрицы весов
                    stream << weights_to_write[i][line][weight] << " ";
                    stream.flush();
                }
                stream << Qt::endl;
                stream.flush();
            }
        }
        weights_file.close();
    }
}

void MainWindow::onTestButtonClicked() {
    ui->label->setText("Тест...");

    const auto path = QFileDialog::getExistingDirectory( // заставим пользователя выбрать каталог
        this,
        tr("Каталог с изображениями"),
        ""
    );

    if (path.isEmpty()) { // если пользователь забил на выбор каталога
        return; // значит мы забиваем на него
    }

    QDir full_dataset_directory(path);

    QStringList dir_filter;
    dir_filter << "0" << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9";
    full_dataset_directory.setNameFilters(dir_filter); // картинки для разных цифр выборки должны быть помещены в соответствующие директории

    size_t total_picks = 0; // всего картинок в тестовой выборке
    size_t guessed = 0;

    // составляем матрицу тестирования
    QVector<QVector<Matrix>> num_dataset; // вектор векторов матриц входных сигналов для каждой цифры выборки
    num_dataset.resize(10);
    for (int i = 0; i < 10; ++i) { // проходим по 10 векторам, каждый - с выборкой для соответствующей цифры
        QDir current_num_dir(path + "/" + static_cast<QChar>(i + '0')); // настроили путь к директории с выборками очередной цифры
        current_num_dir.setNameFilters(QStringList( // указываем искомые расширения
                "*.jpg"
        ));
        current_num_dir.setFilter(QDir::NoFilter // указываем, какие объекты выбирать
            | QDir::Files
            | QDir::NoDotAndDotDot
            | QDir::NoSymLinks
        );
        const auto files = current_num_dir.entryList();
        num_dataset[i].resize(files.count());
        total_picks += files.count();
        for (int j = 0; j < files.count(); ++j) { // проходим по содержимому папки с выборками для конкретной цифры i

            /* откроем изображение и сформируем матрицу признаков */
            QImage image(current_num_dir.absolutePath() + "/" + files[j]); // открываем изображение
            //QString debug_line;
            Matrix input_matrix; // матрица для хранения
            const auto width = image.width(); // узнаем ширину изображения
            const auto height = image.height(); // узнаем высоту изображения

            for (auto h = 0; h < height; h++) {
                for (auto w = 0; w < width; w++) {

                    QColor pixel_color = image.pixelColor(h, w);
                    if (pixel_color.red() >= 200 && pixel_color.green() >= 200 && pixel_color.blue() >= 200){ // если белый цвет
                        input_matrix[h][w] = 1;
                    } else {
                        input_matrix[h][w] = 0;
                    }
                }
            }
            // для отладочных целей преобразуем обратно в картинку
            num_dataset[i][j] = input_matrix;
        }
    }

    // тесты
    for (int i = 0; i < NUM_DIGITS; ++i){ // идём по папкам по порядку (0-9)
        for (int j = 0; j < num_dataset[i].size(); ++j){ // идём по цифрам в этих папках
            perceptron.set_input_matrix(num_dataset[i][j]);
            if (perceptron.recognition() == i){
                ++guessed;
            }
        }
    }

    // покажем результат
    double result = static_cast<double>(guessed) / static_cast<double>(total_picks);
    result *= 100;
    QString result_str = QString::number(result);
    ui->label->setText(result_str + "%");
}

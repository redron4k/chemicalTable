#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadFromFile("data.csv", vec);
    std::copy(vec.begin(), vec.end(), std::back_inserter(found));
    connect(ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(onCheckBoxTicked()));
    connect(ui->checkBox_2, SIGNAL(stateChanged(int)), this, SLOT(onCheckBoxTicked()));
    connect(ui->checkBox_3, SIGNAL(stateChanged(int)), this, SLOT(onCheckBoxTicked()));
    connect(ui->checkBox_4, SIGNAL(stateChanged(int)), this, SLOT(onCheckBoxTicked()));
    model = new QStandardItemModel();

    add = new AddDialog();
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onAddButtonClicked()));
    connect(add, SIGNAL(onBtnClickedSignal(elem)), this, SLOT(addElem(elem)));

    del = new DelDialog();
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(onDelButtonClicked()));
    connect(del, SIGNAL(onBtnClickedSignal(int)), this, SLOT(delElem(int)));

    graph = new Graph(this);
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(onGraphButtonClicked()));
    connect(this, &toBuildGraph, graph, &Graph::buildGraph);

    onUpdate();
}

MainWindow::~MainWindow()
{
    saveToFile("data.csv", vec);
    delete ui;
}

void MainWindow::saveToFile(const std::string& filename,
                            const std::vector<elem>& data) {
    std::ofstream out;
    out.open(filename);
    if (out.is_open()) {
        for (auto s : data) {
            out << s.number.toStdString() << ',' << s.name.toStdString() << ','
                << s.mass.toStdString() << ',' << s.conductivity.toStdString() << "\n";
        }
    }
    out.close();
}

void MainWindow::loadFromFile(const std::string& filename,
                              std::vector<elem>& outData) {
    std::ifstream in;
    in.open(filename);
    if (in.is_open()) {
        elem e;
        std::string s;
        while (std::getline(in, s, ',')) {
            e.number = QString(s.c_str());
            std::getline(in, s, ',');
            e.name = QString(s.c_str());
            std::getline(in, s, ',');
            e.mass = QString(s.c_str());
            std::getline(in, s, '\n');
            e.conductivity = QString(s.c_str());
            outData.push_back(e);
        }
    }
    in.close();
}

void MainWindow::onUpdate() {
    delete model;
    model = new QStandardItemModel(found.size(), 4, this);
    QModelIndex index;
    QStringList lst = {"Номер", "Название", "Масса", "Проводимость"};
    model->setHorizontalHeaderLabels(lst);
    ui->tableView->setModel(model);
    for (unsigned i = 0; i < found.size(); ++i) {
        index = model->index(i, 0, QModelIndex());
        model->setData(index, found[i].number);
        index = model->index(i, 1, QModelIndex());
        model->setData(index, found[i].name);
        index = model->index(i, 2, QModelIndex());
        model->setData(index, found[i].mass);
        index = model->index(i, 3, QModelIndex());
        model->setData(index, found[i].conductivity);
    }
}

void MainWindow::onCheckBoxTicked() {
    found.clear();
    if (ui->checkBox->checkState() == Qt::Checked) {
        std::copy_if(vec.begin(), vec.end(), std::back_inserter(found), [](elem e) {return e.conductivity == QString("Проводник");});
    }
    if (ui->checkBox_2->checkState() == Qt::Checked) {
        std::copy_if(vec.begin(), vec.end(), std::back_inserter(found), [](elem e) {return e.conductivity == QString("Полупроводник");});
    }
    if (ui->checkBox_3->checkState() == Qt::Checked) {
        std::copy_if(vec.begin(), vec.end(), std::back_inserter(found), [](elem e) {return e.conductivity == QString("Изолятор");});
    }
    if (ui->checkBox_4->checkState() == Qt::Checked) {
        std::vector<elem> temp;
        std::copy(found.begin(), found.end(), std::back_inserter(temp));
        found.clear();
        float m = ui->lineEdit->text().toFloat();
        std::copy_if(temp.begin(), temp.end(), std::back_inserter(found), [&m](elem e) {return e.mass.toFloat() <= m;});
    }
    std::sort(found.begin(), found.end(), [](elem a, elem b) {return a.number.toInt() < b.number.toInt();});
    onUpdate();
}

void MainWindow::onAddButtonClicked() {
    add->show();
}

void MainWindow::onDelButtonClicked() {
    del->show();
}

void MainWindow::onGraphButtonClicked() {
    QVector<double> mas;
    QVector<double> num;
    for (unsigned i = 0; i < vec.size(); ++i) {
        mas.append(vec[i].mass.toDouble());
        num.append(vec[i].number.toDouble());
    }
    emit toBuildGraph(mas, num);
    graph->show();
}

void MainWindow::addElem(elem e) {
    vec.push_back(e);
    // std::sort(vec.begin(), vec.end(), [](elem a, elem b) {return a.number.toInt() < b.number.toInt();});
    onCheckBoxTicked();
}

void MainWindow::delElem(int i) {
    for (unsigned j = 0; j < vec.size(); ++j) {
        if (vec[j].number.toInt() == i) {
            vec.erase(vec.begin() + j);
        }
    }
    onCheckBoxTicked();
}

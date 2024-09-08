#include "graph.h"

Graph::Graph(QWidget *parent)
    : QDialog(parent) {
    plot = new QCustomPlot(this);
    plot->addGraph();
    this->setFixedSize(300, 250);
    plot->setFixedSize(280, 230);
    //plot->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

Graph::~Graph() {}

void Graph::buildGraph(QVector<double> mas, QVector<double> num) {
    plot->graph(0)->setData(num, mas);
    plot->rescaleAxes();
    plot->replot();
}

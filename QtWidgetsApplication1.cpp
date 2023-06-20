#include "QtWidgetsApplication1.h"
#include <QGridLayout>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include<qmessagebox.h>
#include <QTreeView>
#include <QHBoxLayout>
#include <QStandardItemModel>

QtWidgetsApplication1::QtWidgetsApplication1(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	opWindow = new OpenGLWindow(this);
	opWindow->setObjectName("myOpenGLWidget");


	QPushButton* intersetionButton = new QPushButton("Intersection");
	QPushButton* resetButton = new QPushButton("Reset");

	ui.horizontalLayout->addWidget(ui.lineButton);
	ui.horizontalLayout->addWidget(ui.rectangleButton);
	ui.horizontalLayout->addWidget(intersetionButton);
	ui.horizontalLayout->addWidget(resetButton);
	ui.horizontalLayout_2->addWidget(opWindow);

	ui.gridLayout_4->addWidget(treeView);
	treeView->setModel(model);

	// ** EXTRACTING ALL THE BUTTONS FROM THE WHOLE WINDOW VIA CENTRALWIDGET ** //
	QList<QPushButton*> buttonList = ui.centralWidget->findChildren<QPushButton*>();

	// ** ITERATING AND APPLYING ** //
	for (QPushButton* button : buttonList) {
		button->setCursor(Qt::PointingHandCursor);
		button->setCheckable(true);
	}

	intersetionButton->setCheckable(false);
	resetButton->setCheckable(false);

	ui.lineButton->setStyleSheet("QPushButton:pressed { background-color: gray; border: 3px;}");
	ui.rectangleButton->setStyleSheet("QPushButton:pressed { background-color: gray; border: 3px;}");
	ui.circleButton->setStyleSheet("QPushButton:pressed { background-color: gray; border: 3px;}");
	resetButton->setStyleSheet("QPushButton:pressed { background-color: red; border: 3px;}");
	intersetionButton->setStyleSheet("QPushButton:pressed { background-color: yellow; border: 3px;}");

	connect(ui.lineButton, SIGNAL(clicked(void)), this, SLOT(createLine()));
	connect(ui.circleButton, SIGNAL(clicked(void)), this, SLOT(createCircle()));
	connect(ui.rectangleButton, SIGNAL(clicked(void)), this, SLOT(createRectangle()));
	connect(intersetionButton, SIGNAL(clicked(void)), this, SLOT(intersectionFinder()));
	connect(resetButton, SIGNAL(clicked(void)), this, SLOT(resetFunction()));

	treeView->setSelectionMode(QAbstractItemView::MultiSelection);

	connect(treeView->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this]() {
		QModelIndexList selectedIndexes = treeView->selectionModel()->selectedIndexes();
		if (!selectedIndexes.isEmpty()) {
			QModelIndex selectedIndex = selectedIndexes.last();

			int ind = selectedIndex.row();

			// Add to highlighItems
			opWindow->highlightItemList.push_back(opWindow->itemList[ind]);

			// Add intersection to this thing 
			// -> Compare every other item in the itemlist to this item and find intersection
			//for each (DataBase::Item item in opWindow->itemList)
			//{

			//	if (opWindow->itemList[ind].entityName != item.entityName || opWindow->itemList[ind].itemNumber != item.itemNumber) {
			//		
			//		opWindow->it.findIntersectionBetItems(opWindow->itemList[ind], item);
			//		//opWindow->renderIntersection();
			//	}
			//}

			for (const auto& item : opWindow->highlightItemList) {
				if (opWindow->itemList[ind].entityName != item.entityName || opWindow->itemList[ind].itemNumber != item.itemNumber) {

					opWindow->it.findIntersectionBetItems(opWindow->itemList[ind], item);
					//opWindow->renderIntersection();
				}
			}
			
			OpenGLWindow::highlightMode = true;
			opWindow->update();
			if (opWindow->highlightItemList.size() > 2) {
				opWindow->highlightItemList.clear();
				opWindow->it.intersectionPointList.clear();
				treeView->selectionModel()->clearSelection();
			}
		}
		});

	
}

QtWidgetsApplication1::~QtWidgetsApplication1()
{}

void QtWidgetsApplication1::createLine() {

	if (ui.lineButton->isChecked()) {
		//actionThread->start();
	OpenGLWindow::drawLineMode = true;
	OpenGLWindow::drawCircleMode = false;
	OpenGLWindow::drawRectangleMode = false;

	//ui.lineButton->setChecked(true);
	ui.rectangleButton->setChecked(false);
	ui.circleButton->setChecked(false);
	//opWindow->drawLine();
	
	}
	else
	{
		OpenGLWindow::drawLineMode = false;
	}
	model->clear();
	for (const auto& line : opWindow->itemList) {
		QString q = line.entityName + QString::number(line.itemNumber);
		QStandardItem* item1 = new QStandardItem();
		item1->setText(q);
		model->appendRow(item1);
		treeView->update();
	}

	/*else {
		actionThread->quit();
		actionThread->wait();
	}*/

}

void QtWidgetsApplication1::createCircle() {
	if (ui.circleButton->isChecked())
	{
		//opWindow->drawCircle();
		OpenGLWindow::drawLineMode = false;
		OpenGLWindow::drawCircleMode = true;
		OpenGLWindow::drawRectangleMode = false;

		ui.lineButton->setChecked(false);
		//ui.circleButton->setChecked(true);
		ui.rectangleButton->setChecked(false);
		
	}
	else {
		OpenGLWindow::drawCircleMode = false;
	}
	model->clear();
	for (const auto& line : opWindow->itemList) {
		QString q = line.entityName + QString::number(line.itemNumber);
		QStandardItem* item1 = new QStandardItem();
		item1->setText(q);
		model->appendRow(item1);
		treeView->update();
	}
}

void QtWidgetsApplication1::createRectangle() {
	if (ui.rectangleButton->isChecked()) {
		//opWindow->drawRectangle();
		OpenGLWindow::drawLineMode = false;
		OpenGLWindow::drawCircleMode = false;
		OpenGLWindow::drawRectangleMode = true;

		ui.lineButton->setChecked(false);
		ui.circleButton->setChecked(false);
		//ui.rectangleButton->setChecked(true);
		
	}
	else {
		OpenGLWindow::drawRectangleMode = false;
	}
	model->clear();
	for (const auto& line : opWindow->itemList) {
		QString q = line.entityName + QString::number(line.itemNumber);
		QStandardItem* item1 = new QStandardItem();
		item1->setText(q);
		model->appendRow(item1);
		treeView->update();
	}
}

void QtWidgetsApplication1::intersectionFinder() {
	opWindow->renderIntersection();
	model->clear();
	for (const auto& line : opWindow->itemList) {
		QString q = line.entityName + QString::number(line.itemNumber);
		QStandardItem* item1 = new QStandardItem();
		item1->setText(q);
		model->appendRow(item1);
		treeView->update();
	}
}

void QtWidgetsApplication1::resetFunction() {

	opWindow->reset();
	model->clear();
	for (const auto& line : opWindow->itemList) {
		QString q = line.entityName + QString::number(line.itemNumber);
		QStandardItem* item1 = new QStandardItem();
		item1->setText(q);
		model->appendRow(item1);
		treeView->update();
	}
}

#include <CWdgScene.h>
#include <CWdgSelectionMenu.h>
#include "CMainWidget.h"
#include "./ui_cmainwidget.h"

CMainWidget::CMainWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::CMainWidget)
{
	ui->setupUi(this);
	CWdgScene* wdgScene = new CWdgScene;
	ui->horizontalLayout->addWidget(wdgScene);
	CWdgSelectionMenu* wdgSelectionMenu = new CWdgSelectionMenu;
	ui->horizontalLayout->addWidget(wdgSelectionMenu);
	connect(wdgSelectionMenu, &CWdgSelectionMenu::addElementToScene, wdgScene, &CWdgScene::addElementToScene);
}

CMainWidget::~CMainWidget()
{
	delete ui;
}


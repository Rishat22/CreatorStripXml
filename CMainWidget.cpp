#include <CWdgScene.h>
#include <CWdgSelectionMenu.h>
#include <CStripLoader.h>
#include "CMainWidget.h"
#include "./ui_cmainwidget.h"

CMainWidget::CMainWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::CMainWidget)
{
	ui->setupUi(this);
	m_wdgScene = new CWdgScene;
	ui->horizontalLayout->addWidget(m_wdgScene);

	CWdgSelectionMenu* wdgSelectionMenu = new CWdgSelectionMenu;
	ui->horizontalLayout->addWidget(wdgSelectionMenu);
	connect(wdgSelectionMenu, &CWdgSelectionMenu::addElementToScene, m_wdgScene, &CWdgScene::addElementToScene);
	connect(wdgSelectionMenu, &CWdgSelectionMenu::saveData, this, &CMainWidget::saveData);

}

CMainWidget::~CMainWidget()
{
	delete ui;
}

void CMainWidget::saveData(const std::string& strFileName)
{
	CStripLoader stripLoader;
	stripLoader.saveStripItem(strFileName);
	auto stripItemsList = std::move(m_wdgScene->GetStripItemsList());
	for(StripItem& stripItem : stripItemsList)
	{
		qDebug() << QString::fromStdString(stripItem.name) << stripItem.rect << QString::fromStdString(stripItem.interaction.action);
	}
}



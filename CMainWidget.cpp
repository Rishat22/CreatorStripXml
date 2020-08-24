#include <QHBoxLayout>
#include <CWdgScene.h>
#include <CWdgSelectionMenu.h>
#include <CStripLoader.h>
#include "CMainWidget.h"

CMainWidget::CMainWidget(QWidget *parent)
	: QWidget(parent)
{
	auto mainLayout = new QHBoxLayout(this);

	m_wdgScene = new CWdgScene;
	mainLayout->addWidget(m_wdgScene);
	m_wdgSelectionMenu = new CWdgSelectionMenu;
	mainLayout->addWidget(m_wdgSelectionMenu);

	connect(m_wdgSelectionMenu, &CWdgSelectionMenu::addElementToScene, m_wdgScene, &CWdgScene::addElementToScene);
	connect(m_wdgScene, &CWdgScene::selectedItemConfig, m_wdgSelectionMenu, &CWdgSelectionMenu::setStripItemConfig);
	connect(m_wdgSelectionMenu, &CWdgSelectionMenu::loadData, this, &CMainWidget::loadData);
	connect(m_wdgSelectionMenu, &CWdgSelectionMenu::saveData, this, &CMainWidget::saveData);
	setLayout(mainLayout);
	loadData("/home/userme/Документы/NewFile.xml");
}

CMainWidget::~CMainWidget()
{
}

void CMainWidget::loadData(const std::string& strFileName)
{
	if(strFileName.empty())
	{
		return;
	}
	CStripLoader stripLoader;
	auto stripItemsConfigs = stripLoader.load(strFileName);
	if(stripItemsConfigs.empty())
	{
		printf("File was not loaded. \n");
		return;
	}
	m_wdgScene->setElementsToScene(stripItemsConfigs);
	m_wdgSelectionMenu->setStripItemConfig(*stripItemsConfigs.begin());
}
void CMainWidget::saveData(const std::string& strFileName)
{
	if(strFileName.empty())
	{
		return;
	}
	CStripLoader stripLoader;
	stripLoader.setData(std::move(m_wdgScene->GetStripItemsParams()));
	stripLoader.save(strFileName);
}



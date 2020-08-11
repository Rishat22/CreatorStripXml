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
	auto wdgSelectionMenu = new CWdgSelectionMenu;
	mainLayout->addWidget(wdgSelectionMenu);

	connect(wdgSelectionMenu, &CWdgSelectionMenu::addElementToScene, m_wdgScene, &CWdgScene::addElementToScene);
	connect(wdgSelectionMenu, &CWdgSelectionMenu::loadData, this, &CMainWidget::loadData);
	connect(wdgSelectionMenu, &CWdgSelectionMenu::saveData, this, &CMainWidget::saveData);
	setLayout(mainLayout);
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
	stripLoader.load(strFileName);
}
void CMainWidget::saveData(const std::string& strFileName)
{
	if(strFileName.empty())
	{
		return;
	}
	CStripLoader stripLoader;
	stripLoader.setData(std::move(m_wdgScene->GetStripItemsList()));
	stripLoader.save(strFileName);
}



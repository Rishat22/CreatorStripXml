#include "CWdgSelectionMenu.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

CWdgSelectionMenu::CWdgSelectionMenu(QWidget *parent)
	: QWidget(parent)
{
	auto hBoxLayout = new QHBoxLayout;
	AddCreateElementsButton(hBoxLayout);
	hBoxLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(hBoxLayout);
}

void CWdgSelectionMenu::AddCreateElementsButton(QLayout* layoutToInsert)
{
	auto createElementsButton = new QPushButton("Add element");
	connect(createElementsButton, &QPushButton::pressed, this, &CWdgSelectionMenu::AddElementToScene);
	layoutToInsert->addWidget(createElementsButton);
}

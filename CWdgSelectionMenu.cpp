#include <QPushButton>
#include <QCompleter>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <Galaxy/CItemInfoGetter.h>
#include "CWdgSelectionMenu.h"

CWdgSelectionMenu::CWdgSelectionMenu(QWidget *parent)
	: QWidget(parent)
{
	auto vBoxLayout = new QVBoxLayout;

	fillTypeItemsList();
	auto itemNamesBoxLayout = createComboBoxWithDescription(m_typeItemsList, "Select the item type:");
	fillActionNamesList();
	auto actionsBoxLayout = createComboBoxWithDescription(m_actionNamesList, "Select the action names:");

	vBoxLayout->addLayout(itemNamesBoxLayout);
	vBoxLayout->addLayout(actionsBoxLayout);
	vBoxLayout->addStretch();
	addCreateElementsButton(vBoxLayout);
	setLayout(vBoxLayout);
}

void CWdgSelectionMenu::fillTypeItemsList()
{
	CItemInfoGetter itemInfoGetter;
	auto listWithTypeNames = itemInfoGetter.getListWithTypeNames();
	fillStringListByVector(m_typeItemsList, listWithTypeNames);
}

void CWdgSelectionMenu::fillActionNamesList()
{
	CItemInfoGetter itemInfoGetter;
	auto listWithTypeNames = itemInfoGetter.getListWithActionNames();
	fillStringListByVector(m_actionNamesList, listWithTypeNames);
}

void CWdgSelectionMenu::fillStringListByVector(QStringList& listToFill, std::vector<std::string> vecFromGet)
{
	for(auto& typeNames : vecFromGet)
	{
		listToFill.push_back(QString::fromStdString(std::move(typeNames)));
	}
}

QLayout* CWdgSelectionMenu::createComboBoxWithDescription(const QStringList& typeItemsList, const std::string& textDescription)
{
	auto comboBoxLayout = new QVBoxLayout;
	comboBoxLayout->setSizeConstraint(QLayout::SetMinimumSize);
	auto descriptionLabel = createDescription(textDescription);
	comboBoxLayout->addWidget(descriptionLabel);
	auto comboBox = createComboBox(typeItemsList);
	comboBoxLayout->addWidget(comboBox);
	return comboBoxLayout;
}

QLabel* CWdgSelectionMenu::createDescription(const std::string& textDescriptions)
{
	QLabel* descriptionLabel = new QLabel(QString::fromStdString(textDescriptions));
	descriptionLabel->setFixedHeight(50);
	return descriptionLabel;
}

QComboBox* CWdgSelectionMenu::createComboBox(const QStringList& typeItemsList)
{
	QCompleter* completer = new QCompleter(typeItemsList, this);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	auto comboBox = new QComboBox();
	comboBox->addItems(typeItemsList);
	comboBox->setEditable(true);
	comboBox->setCompleter(completer);
	return comboBox;
}
void CWdgSelectionMenu::addCreateElementsButton(QBoxLayout* layoutToInsert)
{
	auto createElementsButton = new QPushButton("Add element");
	connect(createElementsButton, &QPushButton::pressed, this, &CWdgSelectionMenu::addElementToScene);
	layoutToInsert->addWidget(createElementsButton);
}

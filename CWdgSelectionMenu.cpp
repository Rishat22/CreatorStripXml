#include <QPushButton>
#include <QCompleter>
#include <QVBoxLayout>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QFileDialog>
#include <Galaxy/CItemInfoGetter.h>
#include <StripItem.h>
#include "CWdgSelectionMenu.h"

CWdgSelectionMenu::CWdgSelectionMenu(QWidget *parent)
	: QWidget(parent)
{
	auto vBoxLayout = new QVBoxLayout;


	auto itemNamesBoxLayout = createComboBox(TypeItemParam::Name, "Select item type:");

	vBoxLayout->addLayout(itemNamesBoxLayout);
	vBoxLayout->addWidget(createInteraction());
	addCreateItemButton(vBoxLayout);
	vBoxLayout->addStretch();
	addSaveButton(vBoxLayout);
	setLayout(vBoxLayout);
}


QGroupBox* CWdgSelectionMenu::createInteraction()
{
	auto groupBox = new QGroupBox;
	auto vInteractionLayout = new QVBoxLayout;
	auto actionsBoxLayout = createComboBox(TypeItemParam::Action, "Select action name:");
	auto triggersBoxLayout = createComboBox(TypeItemParam::Trigger, "Select trigger:");
	vInteractionLayout->addLayout(actionsBoxLayout);
	vInteractionLayout->addLayout(triggersBoxLayout);
	groupBox->setLayout(vInteractionLayout);
	return groupBox;
}

QLayout* CWdgSelectionMenu::createComboBox(const TypeItemParam typeParam, const QString& textDescription)
{
	auto comboBoxLayout = new QVBoxLayout;
	comboBoxLayout->setSizeConstraint(QLayout::SetMinimumSize);
	auto descriptionLabel = createDescription(textDescription);
	comboBoxLayout->addWidget(descriptionLabel);

	QStringList parameterNamesList = std::move(getListByType(typeParam));
	auto comboBox = createComboBox(parameterNamesList);
	connect(comboBox, &QComboBox::editTextChanged,
			[=](const QString& curValue){ m_itemParams[typeParam] =  curValue; });
	comboBoxLayout->addWidget(comboBox);
	return comboBoxLayout;
}

QStringList CWdgSelectionMenu::getListByType(const TypeItemParam typeParam)
{
	CItemInfoGetter itemInfoGetter;
	std::vector<std::string> vecParams;
	switch (typeParam)
	{
		case TypeItemParam::Name:
		{
			vecParams = itemInfoGetter.getListWithTypeNames();
			break;
		}
		case TypeItemParam::Action:
		{
			vecParams = itemInfoGetter.getListWithActionNames();
			break;
		}
		case TypeItemParam::Trigger:
		{
			vecParams = itemInfoGetter.getListWithTriggers();
			break;
		}
		default: break;
	}
	QStringList listParams;
	fillStringListByVector(listParams, vecParams);
	return listParams;
}

void CWdgSelectionMenu::fillStringListByVector(QStringList& listToFill, std::vector<std::string> vecFromGet)
{
	for(auto& typeNames : vecFromGet)
	{
		listToFill.push_back(QString::fromStdString(std::move(typeNames)));
	}
}

QLabel* CWdgSelectionMenu::createDescription(const QString& textDescriptions)
{
	QLabel* descriptionLabel = new QLabel(textDescriptions);
	descriptionLabel->setFixedHeight(20);
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
void CWdgSelectionMenu::addCreateItemButton(QBoxLayout* layoutToInsert)
{
	auto createItemButton = new QPushButton("Add Item");
	connect(createItemButton, &QPushButton::pressed, this, &CWdgSelectionMenu::createGraphicsItem);
	layoutToInsert->addWidget(createItemButton);
}

void CWdgSelectionMenu::addSaveButton(QBoxLayout* layoutToInsert)
{
	auto saveAllButton = new QPushButton("Save strip items");
	connect(saveAllButton, &QPushButton::pressed,
			[=]()
	{
		QString filter = "XML files (*.xml)";
		QString fileName = QFileDialog::getSaveFileName(this, "Select the path to save", "../", filter);
		saveData(std::move(fileName.toStdString()));
	});
	layoutToInsert->addWidget(saveAllButton);
}

void CWdgSelectionMenu::createGraphicsItem()
{
	StripItem stripItem;
	for(auto param : m_itemParams)
	{
		stripItem.setDataByType(param.first, param.second.toStdString());

	}
	addElementToScene(stripItem);
}

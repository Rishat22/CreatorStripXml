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


    auto itemNamesBoxLayout = createComboBox(StripItemParam::Name, "Select the item type:");
    auto actionsBoxLayout = createComboBox(StripItemParam::Action, "Select the action names:");

	vBoxLayout->addLayout(itemNamesBoxLayout);
	vBoxLayout->addLayout(actionsBoxLayout);
	vBoxLayout->addStretch();
	addCreateElementsButton(vBoxLayout);
	setLayout(vBoxLayout);
}

QLayout* CWdgSelectionMenu::createComboBox(const StripItemParam typeParam, const QString& textDescription)
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

QStringList CWdgSelectionMenu::getListByType(const StripItemParam typeParam)
{
    CItemInfoGetter itemInfoGetter;
    std::vector<std::string> vecParams;
    switch (typeParam)
    {
    case StripItemParam::Name:
    {
        vecParams = itemInfoGetter.getListWithTypeNames();
        break;
    }
    case StripItemParam::Action:
    {
        vecParams = itemInfoGetter.getListWithActionNames();
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
    connect(createElementsButton, &QPushButton::pressed, this, &CWdgSelectionMenu::createGraphicsItem);
	layoutToInsert->addWidget(createElementsButton);
}

void CWdgSelectionMenu::createGraphicsItem()
{
    for(auto param : m_itemParams)
    {
        qDebug() << param.second;
    }
    addElementToScene();
}

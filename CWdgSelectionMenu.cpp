#include <QPushButton>
#include <QComboBox>
#include <QCompleter>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "CWdgSelectionMenu.h"

CWdgSelectionMenu::CWdgSelectionMenu(QWidget *parent)
	: QWidget(parent)
{
	auto vBoxLayout = new QVBoxLayout;
	const auto typeItemsList = fillTypeItemsFilst();
	addComboBoxWithTypeItems(typeItemsList, vBoxLayout);
	addCreateElementsButton(vBoxLayout);
	vBoxLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(vBoxLayout);
}

QStringList& CWdgSelectionMenu::fillTypeItemsFilst()
{
	m_typeItemsList << "One" << "two" << "three" << "four" << "five";
	return m_typeItemsList;
}

void CWdgSelectionMenu::addComboBoxWithTypeItems(const QStringList& typeItemsList, QBoxLayout* layoutToInsert)
{
	auto vBoxLayout = new QVBoxLayout;
	QCompleter* completer = new QCompleter(typeItemsList, this);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	auto comboBox = new QComboBox();
	comboBox->addItems(typeItemsList);
	comboBox->setEditable(true);
	comboBox->setCompleter(completer);
	const auto textExplanations = new QLabel("Select the item type:");
	textExplanations->setFixedHeight(50);
	vBoxLayout->addWidget(textExplanations);
	vBoxLayout->addWidget(comboBox);
	vBoxLayout->setSizeConstraint(QLayout::SetMinimumSize);
	layoutToInsert->addLayout(vBoxLayout);
}
void CWdgSelectionMenu::addCreateElementsButton(QBoxLayout* layoutToInsert)
{
	auto createElementsButton = new QPushButton("Add element");
	connect(createElementsButton, &QPushButton::pressed, this, &CWdgSelectionMenu::addElementToScene);
	layoutToInsert->addWidget(createElementsButton);
}

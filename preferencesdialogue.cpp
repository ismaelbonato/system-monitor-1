/*
 * Copyright (C) 2017 Lily Rivers (VioletDarkKitty)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2
 * of the License only.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
#include "preferencesdialogue.h"
#include "ui_preferencesdialogue.h"
#include <QCheckBox>

PreferencesDialogue::PreferencesDialogue(QWidget *parent, QSettings *settings) :
    QDialog(parent),
    ui(new Ui::PreferencesDialogue)
{
    ui->setupUi(this);
    this->settings = settings;

    QCheckBox *divideByCpuCheckbox = this->findChild<QCheckBox*>("divideByCpuCheckbox");
    connect(divideByCpuCheckbox,SIGNAL(clicked(bool)),this,SLOT(toggleDivideCpuCheckbox(bool)));
    divideByCpuCheckbox->setChecked(settings->value("divide process cpu by cpu count", false).toBool());

    QDoubleSpinBox *updateIntervalProcessesSpinner = this->findChild<QDoubleSpinBox*>("updateIntervalProcessesSpinner");
    connect(updateIntervalProcessesSpinner,SIGNAL(valueChanged(double)),this,SLOT(updateProcessesIntervalSpinner(double)));
    updateIntervalProcessesSpinner->setValue(settings->value("processes update interval", 1.0).toDouble());

    QDoubleSpinBox *updateIntervalResourcesSpinner = this->findChild<QDoubleSpinBox*>("updateIntervalResourcesSpinner");
    connect(updateIntervalResourcesSpinner,SIGNAL(valueChanged(double)),this,SLOT(updateResourcesIntervalSpinner(double)));
    updateIntervalResourcesSpinner->setValue(settings->value("resources update interval", 1.0).toDouble());

    IECStandard = this->findChild<QRadioButton*>("IECButton");
    connect(IECStandard,SIGNAL(toggled(bool)),this,SLOT(updateStandardsRadioButton()));
    JEDECStandard = this->findChild<QRadioButton*>("JEDECButton");
    connect(JEDECStandard,SIGNAL(toggled(bool)),this,SLOT(updateStandardsRadioButton()));
    SIStandard = this->findChild<QRadioButton*>("SIButton");
    connect(SIStandard,SIGNAL(toggled(bool)),this,SLOT(updateStandardsRadioButton()));
    checkStandardsRadioButtonBasedOnSettingValue();

    QCheckBox* stackedCpuCheckbox = this->findChild<QCheckBox*>("stackedCpuCheckbox");
    connect(stackedCpuCheckbox,SIGNAL(clicked(bool)),this,SLOT(toggleStackedCpuCheckbox(bool)));
    stackedCpuCheckbox->setChecked(settings->value("draw cpu area stacked", false).toBool());
}

PreferencesDialogue::~PreferencesDialogue()
{
    delete ui;
}

void PreferencesDialogue::toggleDivideCpuCheckbox(bool checked)
{
    settings->setValue("divide process cpu by cpu count",checked);
}

void PreferencesDialogue::toggleStackedCpuCheckbox(bool checked)
{
    settings->setValue("draw cpu area stacked",checked);
}

void PreferencesDialogue::updateProcessesIntervalSpinner(double value)
{
    settings->setValue("processes update interval", value);
}

void PreferencesDialogue::updateResourcesIntervalSpinner(double value)
{
    settings->setValue("resources update interval", value);
}

void PreferencesDialogue::updateStandardsRadioButton()
{
    const QString settingName = "unit prefix standards";
    // find out which radio button is pressed and write the setting to the file
    if (IECStandard->isChecked()) {
        settings->setValue(settingName, "IEC");
    } else if (JEDECStandard->isChecked()) {
        settings->setValue(settingName, "JEDEC");
    } else if (SIStandard->isChecked()) { // check even though there are only 3!
        settings->setValue(settingName, "SI");
    }
}

void PreferencesDialogue::checkStandardsRadioButtonBasedOnSettingValue()
{
    const QString settingName = "unit prefix standards";
    // find if the setting is set to the correct name and then set the radio buttons
    const QString value = settings->value(settingName, "JEDEC").toString();
    if (value == "IEC") {
        IECStandard->setChecked(true);
    } else if (value == "JEDEC") {
        JEDECStandard->setChecked(true);
    } else if (value == "SI") {
        SIStandard->setChecked(true);
    }
}

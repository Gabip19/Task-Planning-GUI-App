#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProiectPlanificareaActivitatilorGUI.h"

class ProiectPlanificareaActivitatilorGUI : public QMainWindow
{
    Q_OBJECT

public:
    ProiectPlanificareaActivitatilorGUI(QWidget *parent = Q_NULLPTR);

private:
    Ui::ProiectPlanificareaActivitatilorGUIClass ui;
};

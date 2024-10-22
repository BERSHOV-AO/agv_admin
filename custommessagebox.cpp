#include "custommessagebox.h"

CustomMessageBox::CustomMessageBox(const QString &message, QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Подтверждение удаления");

    // Устанавливаем цвет фона
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(255, 100, 100)); // Цвет фона
    setPalette(palette);

    layout = new QVBoxLayout(this);
    label = new QLabel(message, this);
    layout->addWidget(label);

    yesButton = new QPushButton("Да", this);
    noButton = new QPushButton("Нет", this);

    layout->addWidget(yesButton);
    layout->addWidget(noButton);

    connect(yesButton, &QPushButton::clicked, this, &CustomMessageBox::accept);
    connect(noButton, &QPushButton::clicked, this, &CustomMessageBox::reject);
}

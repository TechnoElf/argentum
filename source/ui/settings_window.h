/*
 * Created by janis on 2024-01-31
 */

#pragma once

#include <QDialog>
#include <QSettings>
#include <QTabWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>

namespace ag {
    struct SettingsWindow : public QDialog {
    public:
        explicit SettingsWindow(QSettings& settings, QWidget* parent = nullptr);

        SettingsWindow(const SettingsWindow& other) = delete;
        SettingsWindow& operator=(const SettingsWindow& other) = delete;
        SettingsWindow(SettingsWindow&& other) = delete;
        SettingsWindow& operator=(SettingsWindow&& other) = delete;

    private:
        [[maybe_unused]] QSettings& settings;

        QGridLayout layout = QGridLayout(this);
        QTabWidget tabs = QTabWidget(this);

        QWidget general_tab = QWidget(&this->tabs);
        QGridLayout general_tab_layout = QGridLayout(&this->general_tab);
        QLabel sumup_api_key_label = QLabel(&this->general_tab);
        QLineEdit sumup_api_key_input = QLineEdit(&this->general_tab);
        QLabel timeline_size_label = QLabel(&this->general_tab);
        QLineEdit timeline_size_input = QLineEdit(&this->general_tab);

        QIntValidator int_validator = QIntValidator(this);
    };
}

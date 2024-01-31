/*
 * Created by janis on 2024-01-31
 */

#include "settings_window.h"

namespace ag {
    SettingsWindow::SettingsWindow(QSettings& settings, QWidget* parent) : QDialog(parent), settings(settings) {
        this->sumup_api_key_label.setText("SumUp API Key");
        this->general_tab_layout.addWidget(&this->sumup_api_key_label, 0, 0, 1, 1);
        this->sumup_api_key_input.setText(this->settings.value("api/key").toString());
        this->general_tab_layout.addWidget(&this->sumup_api_key_input, 0, 1, 1, 1);

        this->timeline_size_label.setText("Timeline Size");
        this->general_tab_layout.addWidget(&this->timeline_size_label, 1, 0, 1, 1);
        this->timeline_size_input.setValidator(&int_validator);
        this->timeline_size_input.setText(this->settings.value("ui/timeline_size").toString());
        this->general_tab_layout.addWidget(&this->timeline_size_input, 1, 1, 1, 1);

        this->general_tab_layout.setAlignment(Qt::AlignmentFlag::AlignTop);
        this->general_tab.setLayout(&this->general_tab_layout);
        this->tabs.addTab(&general_tab, "General");

        this->layout.setContentsMargins(0, 0, 0, 0);
        this->layout.addWidget(&this->tabs, 0, 0, 1, 1);

        this->setModal(true);
        this->setSizeGripEnabled(true);
        this->setLayout(&this->layout);

        connect(this, &QDialog::rejected, this, [this](){
            this->settings.setValue("api/key", this->sumup_api_key_input.text());
            this->settings.setValue("ui/timeline_size", this->timeline_size_input.text().toInt());
        });
    }
}
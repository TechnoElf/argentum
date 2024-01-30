/*
 * Created by janis on 2024-01-25
 */

#pragma once

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QSettings>
#include <QDockWidget>
#include <QTreeView>
#include <QFileSystemModel>
#include <QStatusBar>

#include "transaction_list_window.h"
#include "timeline_window.h"
#include "../data/transactions_model.h"

namespace ag {
    struct Window : public QMainWindow {
    public:
        explicit Window(QSettings& settings, QWidget *parent = nullptr);

        Window(const Window& other) = delete;
        Window& operator=(const Window& other) = delete;
        Window(Window&& other) = delete;
        Window& operator=(Window&& other) = delete;

    private:
        QSettings& settings;
        TransactionsModel transactions_model = TransactionsModel(this->settings.value("api/key").toString().toUtf8().constData(), this);

        QAction transaction_list_window_action = QAction("Transaction List", this);
        QAction timeline_window_action = QAction("Timeline", this);
        QAction export_action = QAction("Export", this);
        QAction settings_action = QAction("Settings", this);

        QWidget status_bar = QWidget(this);
        QHBoxLayout status_bar_layout = QHBoxLayout(&this->status_bar);
        QLabel flavor_label = QLabel(&this->status_bar);
        QLabel status_label = QLabel(&this->status_bar);
        TransactionListWindow transaction_list_window = TransactionListWindow(this->transactions_model, this);
        TimelineWindow timeline_window = TimelineWindow(this);

        void define_actions();
    };
}
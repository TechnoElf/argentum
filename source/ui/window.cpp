/*
 * Created by janis on 2024-01-25
 */

#include "window.h"
#include "../util/flavor.h"

#include <QMenuBar>
#include <QNetworkReply>

namespace ag {
    Window::Window(QSettings& settings, QWidget *parent) : QMainWindow(parent), settings(settings) {
        this->define_actions();
        [[maybe_unused]] QMenu* file_menu = this->menuBar()->addMenu("File");
        file_menu->addAction(&this->export_action);
        file_menu->addAction(&this->settings_action);
        [[maybe_unused]] QMenu* edit_menu = this->menuBar()->addMenu("Edit");
        [[maybe_unused]] QMenu* view_menu = this->menuBar()->addMenu("View");
        view_menu->addAction(&this->transaction_list_window_action);
        view_menu->addAction(&this->timeline_window_action);

        this->setDockNestingEnabled(true);
        connect(&this->timeline_window, &TimelineWindow::selection_changed, this, [&](){
            this->status_label.setText("fetching");
            this->transactions_model.fetch(this->timeline_window.start, this->timeline_window.end);
        });
        this->addDockWidget(Qt::TopDockWidgetArea, &this->transaction_list_window);
        this->addDockWidget(Qt::TopDockWidgetArea, &this->timeline_window);

        this->flavor_label.setText(Flavor::random());
        this->status_bar_layout.addWidget(&this->flavor_label);
        this->status_bar_layout.addStretch(1);
        connect(&this->transactions_model, &QAbstractItemModel::dataChanged, this, [this](){
            this->status_label.setText("done");
        });
        connect(&this->timeline_window, &TimelineWindow::selection_changed, this, [this](){
            this->status_label.setText("fetching");
        });
        this->status_bar_layout.addWidget(&this->status_label);

        this->status_bar_layout.setContentsMargins(0, 0, 0, 0);
        this->statusBar()->addPermanentWidget(&this->status_bar, 1);

        this->transactions_model.fetch(this->timeline_window.start, this->timeline_window.end);
    }

    void Window::define_actions() {
        this->transaction_list_window_action.setStatusTip("Transaction List");
        this->transaction_list_window_action.setCheckable(true);
        this->transaction_list_window_action.setChecked(true);
        connect(&this->transaction_list_window_action, &QAction::triggered, this, [&](){
            this->transaction_list_window.setVisible(!this->transaction_list_window.isVisible());
        });
        connect(&this->transaction_list_window, &QDockWidget::visibilityChanged, this, [&](){
            this->transaction_list_window_action.setChecked(this->transaction_list_window.isVisible());
        });

        this->timeline_window_action.setStatusTip("Timeline");
        this->timeline_window_action.setCheckable(true);
        this->timeline_window_action.setChecked(true);
        connect(&this->timeline_window_action, &QAction::triggered, this, [&](){
            this->timeline_window.setVisible(!this->timeline_window.isVisible());
        });
        connect(&this->timeline_window, &QDockWidget::visibilityChanged, this, [&](){
            this->timeline_window_action.setChecked(this->timeline_window.isVisible());
        });

        this->export_action.setStatusTip("Export");
        connect(&this->export_action, &QAction::triggered, this, [&](){

        });

        this->settings_action.setStatusTip("Settings");
        connect(&this->settings_action, &QAction::triggered, this, [&](){

        });
    }
}
/*
 * Created by janis on 2024-01-25
 */

#include "window.h"

#include <QMenuBar>
#include <QNetworkReply>

namespace ag {
    Window::Window(QSettings& settings, QWidget *parent) : QMainWindow(parent), settings(settings) {
        this->define_actions();

        connect(&this->timeline_window, &TimelineWindow::selection_changed, this, [&](){
            this->transactions_model.fetch(this->timeline_window.start, this->timeline_window.end);
        });

        [[maybe_unused]] QMenu* file_menu = this->menuBar()->addMenu("File");
        file_menu->addAction(&this->fetch_action);
        file_menu->addAction(&this->export_action);
        file_menu->addAction(&this->settings_action);
        [[maybe_unused]] QMenu* edit_menu = this->menuBar()->addMenu("Edit");
        [[maybe_unused]] QMenu* view_menu = this->menuBar()->addMenu("View");
        view_menu->addAction(&this->transaction_list_window_action);
        view_menu->addAction(&this->timeline_window_action);

        this->setDockNestingEnabled(true);
        this->addDockWidget(Qt::TopDockWidgetArea, &this->transaction_list_window);
        this->addDockWidget(Qt::TopDockWidgetArea, &this->timeline_window);
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

        this->fetch_action.setStatusTip("Fetch");
        connect(&this->fetch_action, &QAction::triggered, this, [&](){

        });

        this->export_action.setStatusTip("Export");
        connect(&this->export_action, &QAction::triggered, this, [&](){

        });

        this->settings_action.setStatusTip("Settings");
        connect(&this->settings_action, &QAction::triggered, this, [&](){

        });
    }
}
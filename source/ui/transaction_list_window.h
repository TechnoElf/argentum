/*
 * Created by janis on 2024-01-26
 */

#pragma once

#include <QDockWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QGridLayout>
#include <QLabel>

#include "../data/transactions_model.h"

namespace ag {
    struct TransactionListWindow : public QDockWidget {
    public:
        explicit TransactionListWindow(TransactionsModel& transactions, QWidget* parent = nullptr);

        TransactionListWindow(const TransactionListWindow& other) = delete;
        TransactionListWindow& operator=(const TransactionListWindow& other) = delete;
        TransactionListWindow(TransactionListWindow&& other) = delete;
        TransactionListWindow& operator=(TransactionListWindow&& other) = delete;

    private:
        TransactionsModel& transactions;

        QWidget window = QWidget(this);
        QGridLayout layout = QGridLayout(&this->window);
        QTreeView transaction_list_view = QTreeView(&this->window);
        QLabel count_label = QLabel(&this->window);
        QLabel total_label = QLabel(&this->window);
    };
}
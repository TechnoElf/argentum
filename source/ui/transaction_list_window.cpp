/*
 * Created by janis on 2024-01-26
 */

#include "transaction_list_window.h"

namespace ag {
    TransactionListWindow::TransactionListWindow(TransactionsModel& transactions, QWidget* parent) : QDockWidget("Transaction List", parent), transactions(transactions) {
        this->transaction_list_view.setModel(&this->transactions);
        this->transaction_list_view.setRootIsDecorated(false);
        this->transaction_list_view.setItemsExpandable(false);
        this->layout.addWidget(&this->transaction_list_view, 0, 0, 1, 2);

        this->count_label.setText("Count: ");
        connect(&this->transactions, &QAbstractItemModel::dataChanged, this, [this](){
            this->count_label.setText(QString("Count: %1").arg(this->transactions.cache.size()));
        });
        this->layout.addWidget(&this->count_label, 1, 0, 1, 1);

        this->total_label.setText("Total: ");
        connect(&this->transactions, &QAbstractItemModel::dataChanged, this, [this](){
            double total = std::accumulate(this->transactions.cache.cbegin(), this->transactions.cache.cend(), 0.0, [](double acc, const Transaction& t){
                return acc + t.amount;
            });
            this->total_label.setText(QString("Total: %1").arg(total));
        });
        this->layout.addWidget(&this->total_label, 1, 1, 1, 1);

        this->layout.setContentsMargins(0, 0, 0, 0);
        this->setWidget(&this->window);
    }
}

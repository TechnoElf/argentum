/*
 * Created by janis on 2024-01-26
 */

#include "transaction_list_window.h"

namespace ag {
    TransactionListWindow::TransactionListWindow(TransactionsModel& transactions, QWidget* parent) : QDockWidget("Transaction List", parent), transactions(transactions) {
        this->status_filter_label.setText("Status");
        this->filter_layout.addWidget(&this->status_filter_label, 0, 0, 1, 1);
        for (const auto& [k, n, a] : Status::kinds) {
            this->status_filter.addItem(n);
        }
        connect(&this->status_filter, &QComboBox::currentTextChanged, this, [this](){
            this->transactions.set_status_filter(Status::from_string(this->status_filter.currentText().toUtf8().constData()));
        });
        this->filter_layout.addWidget(&this->status_filter, 0, 1, 1, 1);

        this->type_filter_label.setText("Type");
        this->filter_layout.addWidget(&this->type_filter_label, 0, 2, 1, 1);
        for (const auto& [k, n, a] : TransactionType::kinds) {
            this->type_filter.addItem(n);
        }
        connect(&this->type_filter, &QComboBox::currentTextChanged, this, [this](){
            this->transactions.set_type_filter(TransactionType::from_string(this->type_filter.currentText().toUtf8().constData()));
        });
        this->filter_layout.addWidget(&this->type_filter, 0, 3, 1, 1);

        this->user_filter_label.setText("User");
        this->filter_layout.addWidget(&this->user_filter_label, 0, 4, 1, 1);
        connect(&this->user_filter, &QLineEdit::textChanged, this, [this](){
            this->transactions.set_user_filter(this->user_filter.text().toUtf8().constData());
        });
        this->filter_layout.addWidget(&this->user_filter, 0, 5, 1, 1);

        this->filter_layout.setContentsMargins(0, 0, 0, 0);
        this->filters.setLayout(&this->filter_layout);
        this->layout.addWidget(&this->filters, 0, 0, 1, 2);

        this->transaction_list_view.setModel(&this->transactions);
        this->transaction_list_view.setRootIsDecorated(false);
        this->transaction_list_view.setItemsExpandable(false);
        this->layout.addWidget(&this->transaction_list_view, 1, 0, 1, 2);

        this->count_label.setText("Count: ");
        connect(&this->transactions, &QAbstractItemModel::dataChanged, this, [this](){
            this->count_label.setText(QString("Count: %1").arg(this->transactions.current.size()));
        });
        this->layout.addWidget(&this->count_label, 2, 0, 1, 1);

        this->total_label.setText("Total: ");
        connect(&this->transactions, &QAbstractItemModel::dataChanged, this, [this](){
            double total = std::accumulate(this->transactions.current.cbegin(), this->transactions.current.cend(), 0.0, [](double acc, const Transaction& t){
                return acc + t.amount;
            });
            this->total_label.setText(QString("Total: %1 €").arg(total));
        });
        this->layout.addWidget(&this->total_label, 2, 1, 1, 1);

        this->layout.setContentsMargins(0, 0, 0, 0);
        this->window.setLayout(&this->layout);
        this->setWidget(&this->window);
    }
}

/*
 * Created by janis on 2024-01-26
 */

#include "transaction_list_window.h"

namespace ag {
    TransactionListWindow::TransactionListWindow(TransactionsModel& transactions, QWidget* parent) : QDockWidget("Transaction List", parent), transactions(transactions) {
        this->list_view.setModel(&this->transactions);
        this->list_view.setRootIsDecorated(false);
        this->list_view.setItemsExpandable(false);

        this->setWidget(&this->list_view);
    }
}

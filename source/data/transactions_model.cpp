/*
 * Created by janis on 2024-01-26
 */

#include "transactions_model.h"

#include <QNetworkReply>
#include <utility>

namespace ag {
    QModelIndex TransactionsModel::index(int row, [[maybe_unused]] int column, [[maybe_unused]] const QModelIndex& parent) const {
        return this->createIndex(row, column, nullptr);
    }

    QModelIndex TransactionsModel::parent([[maybe_unused]] const QModelIndex& child) const {
        return {};
    }

    int TransactionsModel::rowCount([[maybe_unused]] const QModelIndex& parent) const {
        return this->cache.size();
    }

    int TransactionsModel::columnCount([[maybe_unused]] const QModelIndex& parent) const {
        return 4;
    }

    QVariant TransactionsModel::data(const QModelIndex& index, int role) const {
        if (!index.isValid()) { return {}; }
        if (role != Qt::DisplayRole) { return {}; }
        if (index.row() >= this->rowCount()) { return {}; }

        switch (index.column()) {
            case 0: return this->cache[index.row()].id.c_str();
            case 1: return this->cache[index.row()].amount;
            case 2: return this->cache[index.row()].status.c_str();
            case 3: return this->cache[index.row()].timestamp.c_str();
            default: return "Error";
        }
    }

    QVariant TransactionsModel::headerData(int section, Qt::Orientation orientation, int role) const {
        if (role != Qt::DisplayRole) { return {}; }

        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0: return "ID";
                case 1: return "Amount";
                case 2: return "Status";
                case 3: return "Time";
                default: return "Error";
            }
        } else {
            return QStringLiteral("%1").arg(section);
        }
    }

    Qt::ItemFlags TransactionsModel::flags([[maybe_unused]] const QModelIndex& index) const {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    void TransactionsModel::fetch(const QDate& oldest, const QDate& newest) {
        this->sumup_api.transactions_history(
            {oldest, {0, 0}},
            {newest.addDays(1), {0, 0}},
            [&](std::vector<Transaction>&& res) {
                this->cache = res;
                this->layoutChanged();
                this->dataChanged(this->createIndex(0, 0), this->createIndex(this->cache.size(), this->columnCount()));
            }
        );
    }
}
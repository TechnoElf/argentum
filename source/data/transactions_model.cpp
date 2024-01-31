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
        return this->current.size();
    }

    int TransactionsModel::columnCount([[maybe_unused]] const QModelIndex& parent) const {
        return 5;
    }

    QVariant TransactionsModel::data(const QModelIndex& index, int role) const {
        if (!index.isValid()) { return {}; }
        if (role != Qt::DisplayRole) { return {}; }
        if (index.row() >= this->rowCount()) { return {}; }

        switch (index.column()) {
            case 0: return this->current[index.row()].timestamp.toLocalTime();
            case 1: return QString("%1 %2").arg(this->current[index.row()].amount).arg(this->current[index.row()].currency.to_symbol());
            case 2: return this->current[index.row()].status.to_string();
            case 3: return this->current[index.row()].type.to_string();
            case 4: return this->current[index.row()].user.c_str();
            default: return "Error";
        }
    }

    QVariant TransactionsModel::headerData(int section, Qt::Orientation orientation, int role) const {
        if (role != Qt::DisplayRole) { return {}; }

        if (orientation == Qt::Horizontal) {
            switch (section) {
                case 0: return "Time";
                case 1: return "Amount";
                case 2: return "Status";
                case 3: return "Type";
                case 4: return "User";
                default: return "Error";
            }
        } else {
            return QStringLiteral("%1").arg(section);
        }
    }

    Qt::ItemFlags TransactionsModel::flags([[maybe_unused]] const QModelIndex& index) const {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    void TransactionsModel::set_key(std::string&& key) {
        this->sumup_api.set_key(std::move(key));
    }

    void TransactionsModel::fetch(const QDate& oldest, const QDate& newest) {
        this->sumup_api.transactions_history(
            {oldest, {0, 0}},
            {newest.addDays(1), {0, 0}},
            [&](std::vector<Transaction>&& res) {
                this->cache = res;
                this->apply();
            }
        );
    }

    void TransactionsModel::set_status_filter(Status status) {
        this->status_filter = status;
        this->apply();
    }

    void TransactionsModel::set_type_filter(TransactionType type) {
        this->type_filter = type;
        this->apply();
    }

    void TransactionsModel::set_user_filter(const char* user) {
        this->user_filter = user;
        this->apply();
    }

    void TransactionsModel::apply() {
        this->current.clear();
        std::copy_if(this->cache.begin(), this->cache.end(), std::back_inserter(this->current), [this](const Transaction& t) {
            return t.status == this->status_filter &&
                t.type == this->type_filter &&
                t.user.contains(user_filter);
        });

        this->layoutChanged();
        this->dataChanged(this->createIndex(0, 0), this->createIndex(this->cache.size(), this->columnCount()));
    }
}
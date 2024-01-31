/*
 * Created by janis on 2024-01-26
 */

#pragma once

#include <QAbstractItemModel>
#include <QNetworkAccessManager>

#include "transaction.h"
#include "../api/sumup.h"

namespace ag {
    struct TransactionsModel : QAbstractItemModel {
        std::vector<Transaction> current;

    public:
        explicit TransactionsModel(std::string&& api_key, QObject* parent = nullptr) : QAbstractItemModel(parent), sumup_api(std::move(api_key), this) {}

        TransactionsModel(const TransactionsModel& other) = delete;
        TransactionsModel& operator=(const TransactionsModel& other) = delete;
        TransactionsModel(TransactionsModel&& other) = delete;
        TransactionsModel& operator=(TransactionsModel&& other) = delete;

        [[nodiscard]] QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
        [[nodiscard]] QModelIndex parent(const QModelIndex& child) const override;
        [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        [[nodiscard]] int columnCount(const QModelIndex& parent = QModelIndex()) const override;
        [[nodiscard]] QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
        [[nodiscard]] Qt::ItemFlags flags(const QModelIndex& index) const override;

        void set_key(std::string&& key);

        void fetch(const QDate& oldest, const QDate& newest);
        void set_status_filter(Status status);
        void set_user_filter(const char* user);

    private:
        SumupApi sumup_api;

        std::vector<Transaction> cache;

        Status status_filter = {StatusKind::Any};
        std::string user_filter = "";

        void apply();
    };
}
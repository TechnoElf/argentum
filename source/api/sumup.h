/*
 * Created by janis on 2024-01-27
 */

#pragma once

#include <QNetworkAccessManager>

#include "../data/transaction.h"

namespace ag {
    struct SumupApi : QObject {
    public:
        SumupApi(std::string&& api_key, QObject* parent = nullptr) : QObject(parent), api_key(api_key) {}

        SumupApi(const SumupApi& other) = delete;
        SumupApi& operator=(const SumupApi& other) = delete;
        SumupApi(SumupApi&& other) = delete;
        SumupApi& operator=(SumupApi&& other) = delete;

        void set_key(std::string&& api_key);

        void transactions_history(const QDateTime& oldest, const QDateTime& newest, const std::function<void(std::vector<Transaction>&&)>& callback);

    private:
        QNetworkAccessManager network_manager = QNetworkAccessManager(this);
        std::string api_key;

        const std::string api_url = "https://api.sumup.com/v0.1/";

        void transactions_recurse(const std::string& args, const std::function<void(QJsonArray&&)>& callback);
    };
}
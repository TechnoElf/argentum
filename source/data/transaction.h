/*
 * Created by janis on 2024-01-25
 */

#pragma once

#include <vector>

#include <QByteArray>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "../util/error.h"

namespace ag {
    struct Transaction {
        double amount;
        std::string currency;
        std::string id;
        int installments_count;
        std::string payment_type;
        std::string status;
        std::string timestamp ;
        std::string transaction_code;
        std::string payout_plan;
        int payouts_received;
        double payouts_total;
        std::string product_summary;
        std::string card_type;
        std::string transaction_id;
        std::string type;
        std::string user;

    public:
        static Result<Transaction> try_parse(QJsonObject&& json);

    private:
    };

    Result<std::vector<Transaction>> try_parse_transactions(QJsonArray&& items);
}
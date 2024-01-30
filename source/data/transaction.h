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
    enum class StatusKind {
        Any,
        Successful,
        Failed,
        Unknown
    };

    struct Status {
        StatusKind kind;

        static constexpr std::array<std::pair<StatusKind, const char*>, 3> kinds = {
            std::pair(StatusKind::Any, "Any"),
            std::pair(StatusKind::Successful, "Successful"),
            std::pair(StatusKind::Failed, "Failed")
        };

    public:
        bool operator==(const Status& other) const;

        static Status from_string(const std::string& v);
        const char* to_string() const;

        static Status from_api_string(const std::string& v);
    };

    struct Transaction {
        double amount;
        std::string currency;
        std::string id;
        int installments_count;
        std::string payment_type;
        Status status;
        std::string timestamp;
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
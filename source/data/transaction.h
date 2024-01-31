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
        Cancelled,
        Failed,
        Pending,
        Unknown
    };

    struct Status {
        StatusKind kind;

        static constexpr std::array<std::tuple<StatusKind, const char*, const char*>, 5> kinds = {
            std::tuple(StatusKind::Any, "Any", ""),
            std::tuple(StatusKind::Successful, "Successful", "SUCCESSFUL"),
            std::tuple(StatusKind::Cancelled, "Cancelled", "CANCELLED"),
            std::tuple(StatusKind::Failed, "Failed", "FAILED"),
            std::tuple(StatusKind::Pending, "Pending", "PENDING")
        };

    public:
        bool operator==(const Status& other) const;

        static Status from_string(const std::string& v);
        const char* to_string() const;

        static Status from_api_string(const std::string& v);
    };

    enum class CurrencyKind {
        Any,
        Eur,
        Unknown
    };

    struct Currency {
        CurrencyKind kind;

        static constexpr std::array<std::tuple<CurrencyKind, const char*, const char*, const char*>, 2> kinds = {
            std::tuple(CurrencyKind::Any, "Any", "", "?"),
            std::tuple(CurrencyKind::Eur, "Euro", "EUR", "€")
        };

    public:
        bool operator==(const Currency& other) const;

        static Currency from_string(const std::string& v);
        const char* to_string() const;

        static Currency from_api_string(const std::string& v);
        const char* to_symbol() const;
    };

    enum class TransactionTypeKind {
        Any,
        Payment,
        Refund,
        ChargeBack,
        Unknown
    };

    struct TransactionType {
        TransactionTypeKind kind;

        static constexpr std::array<std::tuple<TransactionTypeKind, const char*, const char*>, 4> kinds = {
            std::tuple(TransactionTypeKind::Any, "Any", ""),
            std::tuple(TransactionTypeKind::Payment, "Payment", "PAYMENT"),
            std::tuple(TransactionTypeKind::Refund, "Refund", "REFUND"),
            std::tuple(TransactionTypeKind::ChargeBack, "Chargeback", "CHARGE_BACK")
        };

    public:
        bool operator==(const TransactionType& other) const;

        static TransactionType from_string(const std::string& v);
        const char* to_string() const;

        static TransactionType from_api_string(const std::string& v);
    };

    struct Transaction {
        double amount;
        Currency currency;
        std::string id;
        int installments_count;
        std::string payment_type;
        Status status;
        QDateTime timestamp;
        std::string transaction_code;
        std::string payout_plan;
        int payouts_received;
        int payouts_total;
        std::string product_summary;
        std::string card_type;
        std::string transaction_id;
        TransactionType type;
        std::string user;

    public:
        static Result<Transaction> try_parse(QJsonObject&& json);

    private:
    };

    Result<std::vector<Transaction>> try_parse_transactions(QJsonArray&& items);
}
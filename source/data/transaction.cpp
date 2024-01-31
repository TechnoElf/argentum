/*
 * Created by janis on 2024-01-25
 */

#include "transaction.h"

namespace ag {
    bool Status::operator==(const Status& other) const {
        return this->kind == other.kind || this->kind == StatusKind::Any || other.kind == StatusKind::Any;
    }

    Status Status::from_string(const std::string& v) {
        for (const auto& [k, n, a] : Status::kinds) {
            if (v == n) {
                return {k};
            }
        }
        return {StatusKind::Unknown};
    }
    
    const char* Status::to_string() const {
        for (const auto& [k, n, a] : Status::kinds) {
            if (this->kind == k) {
                return n;
            }
        }
        return "Unknown";
    }

    Status Status::from_api_string(const std::string& v) {
        for (const auto& [k, n, a] : Status::kinds) {
            if (v == a) {
                return {k};
            }
        }
        return {StatusKind::Unknown};
    }

    bool Currency::operator==(const Currency& other) const {
        return this->kind == other.kind || this->kind == CurrencyKind::Any || other.kind == CurrencyKind::Any;
    }

    Currency Currency::from_string(const std::string& v) {
        for (const auto& [k, n, a, s] : Currency::kinds) {
            if (v == n) {
                return {k};
            }
        }
        return {CurrencyKind::Unknown};
    }

    const char* Currency::to_string() const {
        for (const auto& [k, n, a, s] : Currency::kinds) {
            if (this->kind == k) {
                return n;
            }
        }
        return "Unknown";
    }

    Currency Currency::from_api_string(const std::string& v) {
        for (const auto& [k, n, a, s] : Currency::kinds) {
            if (v == a) {
                return {k};
            }
        }
        return {CurrencyKind::Unknown};
    }

    const char* Currency::to_symbol() const {
        for (const auto& [k, n, a, s] : Currency::kinds) {
            if (this->kind == k) {
                return s;
            }
        }
        return "?";
    }

    bool TransactionType::operator==(const TransactionType& other) const {
        return this->kind == other.kind || this->kind == TransactionTypeKind::Any || other.kind == TransactionTypeKind::Any;
    }

    TransactionType TransactionType::from_string(const std::string& v) {
        for (const auto& [k, n, a] : TransactionType::kinds) {
            if (v == n) {
                return {k};
            }
        }
        return {TransactionTypeKind::Unknown};
    }

    const char* TransactionType::to_string() const {
        for (const auto& [k, n, a] : TransactionType::kinds) {
            if (this->kind == k) {
                return n;
            }
        }
        return "Unknown";
    }

    TransactionType TransactionType::from_api_string(const std::string& v) {
        for (const auto& [k, n, a] : TransactionType::kinds) {
            if (v == a) {
                return {k};
            }
        }
        return {TransactionTypeKind::Unknown};
    }

    Result<Transaction> ag::Transaction::try_parse(QJsonObject&& json) {
        double amount = json["amount"].toDouble();
        Currency currency = Currency::from_api_string(json["currency"].toString().toUtf8().constData());
        std::string id = json["id"].toString().toUtf8().constData();
        int installments_count = json["installments_count"].toInt();
        std::string payment_type = json["payment_type"].toString().toUtf8().constData();
        Status status = Status::from_api_string(json["status"].toString().toUtf8().constData());
        QDateTime timestamp = QDateTime::fromString(json["timestamp"].toString(), Qt::ISODate);
        std::string transaction_code = json["transaction_code"].toString().toUtf8().constData();
        std::string payout_plan = json["payout_plan"].toString().toUtf8().constData();
        int payouts_received = json["payouts_received"].toInt();
        int payouts_total = json["payouts_total"].toInt();
        std::string product_summary = json["product_summary"].toString().toUtf8().constData();
        std::string card_type = json["card_type"].toString().toUtf8().constData();
        std::string transaction_id = json["transaction_id"].toString().toUtf8().constData();
        TransactionType type = TransactionType::from_api_string(json["type"].toString().toUtf8().constData());
        std::string user = json["user"].toString().toUtf8().constData();

        return {{
            .amount = amount,
            .currency = currency,
            .id = id,
            .installments_count = installments_count,
            .payment_type = payment_type,
            .status = status,
            .timestamp = timestamp,
            .transaction_code = transaction_code,
            .payout_plan = payout_plan,
            .payouts_received = payouts_received,
            .payouts_total = payouts_total,
            .product_summary = product_summary,
            .card_type = card_type,
            .transaction_id = transaction_id,
            .type = type,
            .user = user
        }};
        //return std::unexpected(Error(ErrorKind::Unknown));
    }

    Result<std::vector<Transaction>> try_parse_transactions(QJsonArray&& items) {
        std::vector<Transaction> transactions;

        for (QJsonValue item_ref : items) {
            auto res = Transaction::try_parse(item_ref.toObject());
            if (res.has_value()) {
                transactions.push_back(std::move(*res));
            }
        }

        return {std::move(transactions)};
    }
}
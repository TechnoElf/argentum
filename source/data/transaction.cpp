/*
 * Created by janis on 2024-01-25
 */

#include "transaction.h"

namespace ag {
    const char* Currency::to_symbol() const {
        for (const auto& [k, name, api_name, symbol] : Currency::kinds) {
            if (this->kind == k) {
                return symbol;
            }
        }
        return "?";
    }

    Result<Transaction> ag::Transaction::try_parse(QJsonObject&& json) {
        double amount = json["amount"].toDouble();
        Enum<Currency> currency = Enum<Currency>::from_api_string(json["currency"].toString().toUtf8().constData());
        std::string id = json["id"].toString().toUtf8().constData();
        int installments_count = json["installments_count"].toInt();
        Enum<PaymentType> payment_type = Enum<PaymentType>::from_api_string(json["payment_type"].toString().toUtf8().constData());
        Enum<Status> status = Enum<Status>::from_api_string(json["status"].toString().toUtf8().constData());
        QDateTime timestamp = QDateTime::fromString(json["timestamp"].toString(), Qt::ISODate);
        std::string transaction_code = json["transaction_code"].toString().toUtf8().constData();
        Enum<PayoutPlan> payout_plan = Enum<PayoutPlan>::from_api_string(json["payout_plan"].toString().toUtf8().constData());
        int payouts_received = json["payouts_received"].toInt();
        int payouts_total = json["payouts_total"].toInt();
        std::string product_summary = json["product_summary"].toString().toUtf8().constData();
        Enum<CardType> card_type = Enum<CardType>::from_api_string(json["card_type"].toString().toUtf8().constData());
        std::string transaction_id = json["transaction_id"].toString().toUtf8().constData();
        Enum<TransactionType> type = Enum<TransactionType>::from_api_string(json["type"].toString().toUtf8().constData());
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
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
#include "../util/enum.h"

namespace ag {
    struct Currency {
        enum class Kind {
            Any,
            Eur,
            Unknown
        } kind;

        static constexpr std::array<std::tuple<Kind, const char*, const char*, const char*>, 2> kinds = {
            std::tuple(Kind::Any, "Any", "", "?"),
            std::tuple(Kind::Eur, "Euro", "EUR", "€")
        };

        const char* to_symbol() const;
    };

    struct PaymentType {
        enum class Kind {
            Any,
            Ecom,
            Recurring,
            Boleto,
            Unknown
        } kind;

        static constexpr std::array<std::tuple<Kind, const char*, const char*>, 4> kinds = {
            std::tuple(Kind::Any, "Any", ""),
            std::tuple(Kind::Ecom, "Ecom", "ECOM"),
            std::tuple(Kind::Recurring, "Recurring", "RECURRING"),
            std::tuple(Kind::Boleto, "Boleto", "BOLETO"),
        };
    };

    struct Status {
        enum class Kind {
            Any,
            Successful,
            Cancelled,
            Failed,
            Pending,
            Unknown
        } kind;

        static constexpr std::array<std::tuple<Kind, const char*, const char*>, 5> kinds = {
            std::tuple(Kind::Any, "Any", ""),
            std::tuple(Kind::Successful, "Successful", "SUCCESSFUL"),
            std::tuple(Kind::Cancelled, "Cancelled", "CANCELLED"),
            std::tuple(Kind::Failed, "Failed", "FAILED"),
            std::tuple(Kind::Pending, "Pending", "PENDING")
        };
    };

    struct PayoutPlan {
        enum class Kind {
            Any,
            SinglePayment,
            TrueInstallment,
            AcceleratedInstallment,
            Unknown
        } kind;

        static constexpr std::array<std::tuple<Kind, const char*, const char*>, 4> kinds = {
            std::tuple(Kind::Any, "Any", ""),
            std::tuple(Kind::SinglePayment, "Single payment", " SINGLE_PAYMENT"),
            std::tuple(Kind::TrueInstallment, "True installment", "TRUE_INSTALLMENT"),
            std::tuple(Kind::AcceleratedInstallment, "Accelerated installment", "ACCELERATED_INSTALLMENT"),
        };
    };

    struct CardType {
        enum class Kind {
            Any,
            Visa,
            Amex,
            Cup,
            Diners,
            Discover,
            Elo,
            Elv,
            Hipercard,
            Jcb,
            Maestro,
            Mastercard,
            VisaElectron,
            VisaVpay,
            Unknown
        } kind;

        static constexpr std::array<std::tuple<Kind, const char*, const char*>, 14> kinds = {
            std::tuple(Kind::Any, "Any", ""),
            std::tuple(Kind::Visa, "Visa", "VISA"),
            std::tuple(Kind::Amex, "American Express", "AMEX"),
            std::tuple(Kind::Cup, "Cup", "CUP"),
            std::tuple(Kind::Diners, "Diners Club", "DINERS"),
            std::tuple(Kind::Discover, "Discover", "DISCOVER"),
            std::tuple(Kind::Elo, "Elo", "ELO"),
            std::tuple(Kind::Elv, "Elv", "ELV"),
            std::tuple(Kind::Hipercard, "Hipercard", "HIPERCARD"),
            std::tuple(Kind::Jcb, "JCB", "JCB"),
            std::tuple(Kind::Maestro, "Maestro", "MAESTRO"),
            std::tuple(Kind::Mastercard, "Mastercard", "MASTERCARD"),
            std::tuple(Kind::VisaElectron, "Visa Electron", "VISA_ELECTRON"),
            std::tuple(Kind::VisaVpay, "Visa V Pay ", "VISA_VPAY")
        };
    };

    struct TransactionType {
        enum class Kind {
            Any,
            Payment,
            Refund,
            ChargeBack,
            Unknown
        } kind;

        static constexpr std::array<std::tuple<Kind, const char*, const char*>, 4> kinds = {
            std::tuple(Kind::Any, "Any", ""),
            std::tuple(Kind::Payment, "Payment", "PAYMENT"),
            std::tuple(Kind::Refund, "Refund", "REFUND"),
            std::tuple(Kind::ChargeBack, "Chargeback", "CHARGE_BACK")
        };
    };

    struct Transaction {
        double amount;
        Enum<Currency> currency;
        std::string id;
        int installments_count;
        Enum<PaymentType> payment_type;
        Enum<Status> status;
        QDateTime timestamp;
        std::string transaction_code;
        Enum<PayoutPlan> payout_plan;
        int payouts_received;
        int payouts_total;
        std::string product_summary;
        Enum<CardType> card_type;
        std::string transaction_id;
        Enum<TransactionType> type;
        std::string user;

    public:
        static Result<Transaction> try_parse(QJsonObject&& json);

    private:
    };

    Result<std::vector<Transaction>> try_parse_transactions(QJsonArray&& items);
}
// Copyright (c) 2019-2020 The Open-Transactions developers
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <QObject>
#include <QSortFilterProxyModel>
#include <QString>
#include <QVariant>

class QModelIndex;

namespace opentxs
{
namespace ui
{
class AccountActivityQt;
}  // namespace ui
}  // namespace opentxs

namespace metier::model
{
class AccountActivity final : public QSortFilterProxyModel
{
    Q_OBJECT

signals:
    void sync(int, int) const;

public:
    int columnCount([[maybe_unused]] const QModelIndex& parent) const final
    {
        return 3;
    }
    QVariant data(const QModelIndex& index, int role) const final;
    Q_INVOKABLE QString getDepositAddress(const int chain = 0) const noexcept;
    Q_INVOKABLE bool sendToAddress(
        const QString& address,
        const QString& amount,
        const QString& memo) const noexcept;
    Q_INVOKABLE bool validateAddress(const QString& address) const noexcept;
    Q_INVOKABLE QString validateAmount(const QString& amount) const noexcept;

    using QSortFilterProxyModel::setSourceModel;
    void setSourceModel(opentxs::ui::AccountActivityQt* sourceModel);

    AccountActivity();

private:
    using ot_super = QSortFilterProxyModel;

    opentxs::ui::AccountActivityQt* ot_model_;

    auto filterAcceptsColumn(
        int source_column,
        const QModelIndex& source_parent) const -> bool final;

    AccountActivity(const AccountActivity&) = delete;
    AccountActivity(AccountActivity&&) = delete;
    AccountActivity& operator=(const AccountActivity&) = delete;
    AccountActivity& operator=(AccountActivity&&) = delete;
};
}  // namespace metier::model
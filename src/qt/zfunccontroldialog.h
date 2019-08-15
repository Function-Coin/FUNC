// Copyright (c) 2017-2018 The PIVX developers
// Copyright (c) 2019 The CryptoDev developers
// Copyright (c) 2019 The FunCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZFUNCCONTROLDIALOG_H
#define ZFUNCCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "zfunc/zerocoin.h"
#include "privacydialog.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZFuncControlDialog;
}

class CZFuncControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CZFuncControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CZFuncControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CZFuncControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class ZFuncControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZFuncControlDialog(QWidget *parent);
    ~ZFuncControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::ZFuncControlDialog *ui;
    WalletModel* model;
    PrivacyDialog* privacyDialog;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
        COLUMN_PRECOMPUTE,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
    friend class CZFuncControlWidgetItem;

private slots:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZFUNCCONTROLDIALOG_H

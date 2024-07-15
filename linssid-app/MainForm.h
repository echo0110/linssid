/*
 * File:   mainForm.h
 * Author: warren
 *
 * Created on October 25, 2012, 11:43 AM
 */

#ifndef _MAINFORM_H
#define	_MAINFORM_H

#include <iostream>
#include <fstream>
#include <QEvent>
#include <QString>
#include <QFont>
#include <qwt.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_scale_draw.h>
#include "ui_MainForm.h"
#include "Custom.h"
#include "DataStruct.h"
#include <QProcess>
#include <QTextEdit>

// forward declare
class DataLogger;
class DataReadyEvent;
class Getter;
class PrefsHandler;
class prefsDialog;
class VendorDb;
class ViewFilterDialog;

class QStandardItem;
class QStandardItemModel;
class DataProxyModel;

class MainForm : public QMainWindow {
    Q_OBJECT
public:

    MainForm();
    virtual ~MainForm();
    void init();
    void getUserID();
    void addInterfaces();
    void setInterface(int);
    int getNapTime();
    std::string getCurrentInterface();
    int getReadyBlockNo();
    void postDataReadyEvent(const int);
    void drawTable();
    void setVisibleCols();
    void fillTable();
    class Chan24ScaleDraw;
    class Chan5ScaleDraw;
    void initColtoAction();
    void initPlotGrids();
    void initStatusBar();
    void drawChan24Plot();
    void drawChan5Plot();
    void drawTimePlot();
    void fillPlots();
    void fillStatus();
    void initNewCell(std::string, int);
    void extractData(std::string, int &, int &);
    void resolveMesh(int);

    static Getter* pGetter; // a pointer to the instance of the Getter that calls this MainForm
    static QThread* pGetterThread; // a pointer to the getter's thread
    static QFont tblFnt;
    static QString fntSizes[];
    static int numFntSizes;
    static QAction* colToQAction[MAX_TABLE_COLS];
    static int columnWidth[MAX_TABLE_COLS];

public slots:
    void doRun();
    void doPlotAll();
    void doPlotNone();
    void doTableClicked(const QModelIndex &);
    void reDrawTable();
    void showAboutBox();
    void showPrefsDlg();
    void showViewFilterDlg();
    void handleFilterDialogClosed();
    void columnWidthSave(int, int, int);
    void updatePlotPrefs(QString, int, int, bool, bool);
    void logPrefChanged(int);
    void updateOnlineStatus();
    void readPingOutput();
    void updateNetworkInfo();
    void startPing();
    void restartPing();
    void handleError(QProcess::ProcessError error);
    //void onWifiDoubleClicked(int row, int column);
    // void connectToWifi(const QString &ssid, const QString &password);
    // //void onMainTableViewDoubleClicked(const QModelIndex &index);
    void onConnectButtonClicked(const QString& ssid, const QString& bssid, const QString& password);
    void onTableDoubleClicked(const QModelIndex &index);
    void connectToWifi(const QString &bssid, const QString &password);
private:
    Ui::mainForm mainFormWidget;
    void customEvent(QEvent*) override;
    void closeEvent(QCloseEvent*) override;
    void handleDataReadyEvent(const DataReadyEvent*);

private:
    void savePrefs();
    void loadPrefs();
    void applyPlotPrefs(int fntSize, int plotMin, int plotMax, bool showGrid);
    bool shouldBePlot(int tbi);

private:
    std::unique_ptr<prefsDialog> prefsDlg_;
    std::unique_ptr<ViewFilterDialog> viewFilterDlg_;

    std::unique_ptr<DataProxyModel> proxyModel_;
    std::unique_ptr<QStandardItemModel> model_;
    std::unique_ptr<DataLogger> dataLogger_;
    std::unique_ptr<VendorDb> vendorDb_;
    std::unique_ptr<PrefsHandler> prefsHandler_;
    std::unique_ptr<QLabel> statusCounts_;
    std::unique_ptr<QwtPlotGrid> chan24Grid_;
    std::unique_ptr<QwtPlotGrid> chan5Grid_;
    std::unique_ptr<QwtPlotGrid> timeGrid_;
    Stats stats_;

    // Internal states variables
    int logDataState_;
    bool plotShowLabel_ = true;
    bool firstScan_ = false;
    long runStartTime_;
    long blockSampleTime_; // time of the block relative to runStartTime
    long now_; // absolute time of the block
    CellData::Vector cellDataRay_; // The data table
    int maxTableIndex_; // holds the highest index pointer into cellData
private:
    QLabel* onlineStatusLabel;
    QLineEdit *gatewayLineEdit;
    QProcess *pingProcess;
    QTextEdit *pingOutputTextEdit;
    QProcess *networkInfoProcess;
    QPushButton *pingButton;
    QLabel *ssidLabel;
    QLabel *bssidLabel;
    QString wirelessInterface;
    //QTableWidget *wifiTable;
    //void connectToWifi(const QString &ssid, const QString &password);
    static const int BSSID_COLUMN_INDEX = 2;
    
};

#endif	/* _MAINFORM_H */

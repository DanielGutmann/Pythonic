/*
 * This file is part of Pythonic.

 * Pythonic is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Pythonic is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Pythonic. If not, see <https://www.gnu.org/licenses/>
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QRect>
#include <QLoggingCategory>
#include <QVector>
#include <QScrollArea>
#include <QSizeGrip>
#include <QLabel>
#include <QSet>
#include <QMap>
#include <QDialog>
#include <QTextEdit>
#include <QSplitter>
#include <QSizePolicy>
#include <QFontMetrics>
#include <QDir>

#include "helper.h"
#include "websocket.h"
#include "workingarea.h"
#include "menubar.h"
#include "toolbox.h"
#include "messagearea.h"
#include "wall_of_fame.h"


#define N_WORKING_GRIDS 3

#define INIT_ELEMENTSTATES_DELAY    5


//https://stackoverflow.com/questions/39931734/qt-specific-difference-of-stack-vs-heap-attributes


template<typename T>
struct DelayedInitCommand {
    void        (T::*init)();
    quint32     delay;
};

/*! @brief MainWindow is the base widget for all graphical elements

    Detailed description follows here.
    @author Stephan Avenwedde
    @date October 2020
    @copyright [GPLv3](../../../LICENSE)
    */



class MainWindow : public QMainWindow
{
    Q_OBJECT
    static constexpr QSize m_default_size{1200, 800};
    static constexpr QSize m_default_area_size {m_default_size - QSize(10, 200)};
    static constexpr int   m_max_log_messages{20};
    static constexpr int   m_max_out_messages{20};

public:
    explicit MainWindow(QWidget *parent = nullptr);
    /*! \brief Global instance of Logger
      *
      * Used to log at websocket /log of PythonicWebDaemon
      */
    ~ MainWindow();

    Websocket   m_wsCtrl{"ws://localhost:7000/ctrl", this};
    Websocket   m_wsRcv{"ws://localhost:7000/rcv", this};

signals:
    void updateCurrentWorkingArea(WorkingArea* currentWokringArea);

public slots:

    void wsCtrl(const QJsonObject cmd);

    //! Slot is called when starting execution and
    //! after editing an element (by clicking on the Save button)
    void saveConfig();
    //! Set the text on the bottom of the Windows
    void setInfoText(QString text);

private slots:

    //! Send log-message to daemon
    void logMessage(const QString msg, const LogLvl lvl);
    //! Send control command to daemon
    //! Receives commands from the daemon
    void wsRcv(const QString &message);
    //! Forward message to working area
    void fwrdWsRcv(const QJsonObject cmd);
    //! Reconnect to daemon
    void reconnect();
    //! Sets the current WorkingArea
    void setCurrentWorkingArea(const int tabIndex);
    //! Start execution of specific element
    void startExec(const quint32 id);
    //! Stop execution of specific element
    void stopExec(const quint32 id);
    //! Start all elements
    void startAll();
    //! Stop alle elements
    void stopAll();
    //! Kill all processes
    void killAll();
    /* DBG Slot */
    void testSlot(bool checked);
    //! Load config from daemon */
    void loadSavedConfig(const QJsonObject &config);
    //! Load Toolbox
    void loadToolbox(const QJsonObject &toolbox);
    //! Query config */
    void queryConfig();
    //! Query Toolbox elements
    void queryToolbox();
    //! Query running states of element (for highlighting)
    void queryElementStates();
    //! Proceed with initialization when connection is established
    void connectionEstablished();
    //! Opens a file browser window to upload the config
    void uploadConfig();
    //! Opens a file browser to upload an executable
    void uploadExecutable();
    //! Open/close the log message area
    void toggleMessageArea();
    //! Open/close the output area
    void toggleOutputArea();
    //! Open the Wall of Fame
    void openWallOfFame();

private:

    //! Websocket is only active when config or executable is uploaded
    QWebSocket              m_wsUploadFile;

    //! Incremented by heartbeat
    quint32                 m_refTimer;

    /* Die Reihenfolge hier ist entscheidend */
    QPushButton             *m_sendDebugMessage;

    QVBoxLayout             m_WrkAreaToolBoxLayout;



    //! Central widget: Parent for all other widgets
    QWidget                 m_mainWidget;
    QVBoxLayout             m_mainWidgetLayout;

    //! Icon bar (New workflow, save worklow etc ... */

    MenuBar                 m_menuBar;        

    //! Bottom Area (Toolbox, WorkingArea, Output and Logging)
    QSplitter               m_bottomArea;

    //! The famous Wall of Fame
    WallOfFame*             m_ptrWallOfFame;


    /* Working Area (Grids) */ // self.scrollArea

    /*!
     * m_toolboxTabs muss unnnterhalb von m_bottomArea eingeordnet werden da
     * m_bottomArea der parent ist
     */

    QTabWidget              m_workingTabs;
    QVector<QScrollArea*>   m_arr_workingTabs;
    QVector<WorkingArea*>   m_arr_workingArea;

    //! The Toolbox shows the available elements
    Toolbox                 m_toolBox;

    //! OutputArea shows the output of elements
    MessageArea             m_outputArea{"Element Output", m_max_out_messages};
    //! MessageArea shows the logging messages of elements
    MessageArea             m_messageArea{"Log Messages", m_max_log_messages};


    /* Bottom Border (Info Text & Size Grip) */

    QWidget                 m_bottomBorder;
    QHBoxLayout             m_bottomBorderLayout;

    QLabel                  m_datetimeText;
    QLabel                  m_infoText;
    QLabel                  m_heartBeatText;



    const QVector<char>     m_spinner{'-', '\\', '|', '/' };
    QVector<char>::const_iterator it_spinner;

    QVector<DelayedInitCommand<MainWindow> >    m_delayedInitializations;
    void                                        (MainWindow::*ptrTmp)();

    const QLoggingCategory        logC{"MainWindow"};

};




#endif // MAINWINDOW_H


//===========================================
//  Lumina-DE source code
//  Copyright (c) 2014-2017, Ken Moore
//  Available under the 3-clause BSD license
//  See the LICENSE file for full details
//===========================================
//  This class is a quick sample desktop plugin
//===========================================
#ifndef _LUMINA_DESKTOP_DESKTOP_PLUGIN_APPLICATION_LAUNCHER_H
#define _LUMINA_DESKTOP_DESKTOP_PLUGIN_APPLICATION_LAUNCHER_H

#include <QToolButton>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QProcess>
#include <QFile>
#include <QFileSystemWatcher>
#include <QTimer>
#include <QMenu>
#include <QCursor>

#include "../LDPlugin.h"

#include <LuminaXDG.h>

class AppLauncherPlugin : public LDPlugin{
	Q_OBJECT
public:
	AppLauncherPlugin(QWidget* parent, QString ID);
	~AppLauncherPlugin(){}

	void Cleanup(); //special function for final cleanup

private:
	QToolButton *button;
	QFileSystemWatcher *watcher;
	//QMenu *menu;
	QInputDialog *inputDLG;
	QString iconID;
	int icosize;

private slots:
	void loadButton();
	void buttonClicked(bool openwith = false);
	void iconLoaded(QString);

	//void openContextMenu();

	//void increaseIconSize();
	//void decreaseIconSize();
	//void deleteFile();

	void actionTriggered(QAction *act);
	void openWith();
	void fileProperties();
	void fileDelete();
	void fileCut();
	void fileCopy();
	void fileRename();
	void renameFinished(int result);

public slots:
	void LocaleChange(){
	  loadButton(); //force reload
	}

protected:
	void resizeEvent(QResizeEvent *ev){
	  LDPlugin::resizeEvent(ev);
	  QTimer::singleShot(100, this, SLOT(loadButton()) );
	}
	void changeEvent(QEvent *ev){
	  LDPlugin::changeEvent(ev);
	  QEvent::Type tmp = ev->type();
	  if(tmp == QEvent::StyleChange || tmp==QEvent::ThemeChange || tmp==QEvent::LanguageChange || tmp==QEvent::LocaleChange){ loadButton(); }
	}
};
#endif

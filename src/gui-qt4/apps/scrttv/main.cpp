/***************************************************************************
 *   Copyright (C) by GFZ Potsdam                                          *
 *                                                                         *
 *   You can redistribute and/or modify this program under the             *
 *   terms of the SeisComP Public License.                                 *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   SeisComP Public License for more details.                             *
 ***************************************************************************/




#define SEISCOMP_COMPONENT RTTV

#include <seiscomp3/logging/log.h>
#include <seiscomp3/gui/core/application.h>
#include "mainwindow.h"

using namespace Seiscomp::Gui;
using namespace Seiscomp::Applications;

class TraceViewApp : public Kicker<Seiscomp::Applications::TraceView::MainWindow> {
	public:
		TraceViewApp(int& argc, char** argv, int flags = DEFAULT) :
		  Kicker<Seiscomp::Applications::TraceView::MainWindow>(argc, argv, flags) {
			_filterName = "BW(3, 0.5, 10.0)";
			_initStartTime = false;
			_automaticResort = true;
			_showPicks = true;
			_inventoryEnabled = true;
			_maxDelay = 0;
		}

	protected:
		void createCommandLineDescription() {
			Kicker<Seiscomp::Applications::TraceView::MainWindow>::createCommandLineDescription();

			commandline().addGroup("Mode");
			commandline().addOption("Mode", "filter", "Sets the filter to use",  (std::string*)NULL);
			commandline().addOption("Mode", "offline", "Do not connect to a messaging server and do not use the database");
			commandline().addOption("Mode", "no-inventory", "Do not wait for all data when using a file as input but read threaded");
			commandline().addOption("Mode", "end-time", "Set the end time of acquisition, default: 'gmt'", (std::string*)NULL);
			commandline().addOption("Mode", "buffer-size", "Sets the size of the waveformbuffer in seconds, default: 1800", (int*)NULL);
			commandline().addOption("Mode", "max-delay", "The maximum delay in seconds to keep a trace visible (0 to disable)", (int*)NULL);
			commandline().addOption("Mode", "initially-visible-all", "Show all traces initially");
		}

		bool validateParameters() {
			if ( !Kicker<Seiscomp::Applications::TraceView::MainWindow>::validateParameters() )
				return false;

			bool offline = false;
			_inventoryEnabled = true;

			if ( commandline().hasOption("offline") )
				offline = true;

			if ( commandline().hasOption("no-inventory") )
				_inventoryEnabled = false;

			try {
				_initStartTime = configGetBool("allTracesInitiallyVisible");
			}
			catch ( ... ) {}

			_initStartTime = commandline().hasOption("initially-visible-all");

			try {
				_maxDelay = commandline().option<int>("max-delay");
			}
			catch ( ... ) {}

			try {
				_maxDelay = configGetInt("maxDelay");
			}
			catch ( ... ) {}

			try {
				_automaticResort = configGetBool("resortAutomatically");
			}
			catch ( ... ) {}

			try {
				_showPicks = configGetBool("showPicks");
			}
			catch ( ... ) {}

			std::vector<std::string> unnamedOptions;
			unnamedOptions = commandline().unrecognizedOptions();
			bool hasPositionals = false;
			for ( size_t i = 0; i < unnamedOptions.size(); ++i ) {
				if ( unnamedOptions[i].substr(0,1) != "-" ) {
					hasPositionals = true;
					break;
				}
			}

			if ( hasPositionals )
				offline = true;

			if ( offline ) {
				setMessagingEnabled(false);
				setDatabaseEnabled(false, false);
			}

			// Disable database access if an inventory xml file is given
			// as a command line argument.
			if ( !isInventoryDatabaseEnabled() && !isConfigDatabaseEnabled() )
				setDatabaseEnabled(false, false);

			if ( commandline().hasOption("record-file") ) {
				//setMessagingEnabled(false);
				setDatabaseEnabled(false, false);
			}

			try {
				_filterName = configGetString("filter");
			}
			catch ( ... ) {}

			try {
				_filterName = commandline().option<std::string>("filter");
			}
			catch ( ... ) {}

			try {
				std::string dt = SCApp->commandline().option<std::string>("end-time");
				_endTime = Seiscomp::Core::Time::FromString(dt.c_str(), "%F %T");
				if ( !_endTime.valid() ) {
					std::cerr << "ERROR: passed endtime is not valid, expect format \"YYYY-mm-dd HH:MM:SS\"" << std::endl
					          << "       example: --end-time \"2010-01-01 12:00:00\"" << std::endl;
					return false;
				}

				std::cout << "Set defined endtime: " << _endTime.toString("%F %T") << std::endl;
			}
			catch ( ... ) {}

			_bufferSize = 1800;

			try {
				_bufferSize = configGetInt("bufferSize");
			}
			catch ( ... ) {}

			try {
				_bufferSize = (size_t)SCApp->commandline().option<int>("buffer-size");
			}
			catch ( ... ) {}

			return true;
		}

		virtual void setupUi(Seiscomp::Applications::TraceView::MainWindow* w) {
			if ( _initStartTime )
				w->setStartTime(Seiscomp::Core::Time::GMT());
			w->setMaximumDelay(_maxDelay);
			w->setEndTime(_endTime);
			w->setBufferSize(_bufferSize);
			w->setAutomaticSortEnabled(_automaticResort);
			w->setShowPicks(_showPicks);
			w->setInventoryEnabled(_inventoryEnabled);
			w->start();
			w->setFilterByName(_filterName);
		}

	private:
		int _maxDelay;
		std::string _filterName;
		Seiscomp::Core::Time _endTime;
		bool _initStartTime;
		bool _automaticResort;
		bool _showPicks;
		bool _inventoryEnabled;
		size_t _bufferSize;
};

int main(int argc, char *argv[])
{
	int retCode;

	{
		TraceViewApp app(argc, argv, Application::DEFAULT | Application::LOAD_STATIONS | Application::LOAD_CONFIGMODULE);
		app.setPrimaryMessagingGroup("GUI");
		app.addMessagingSubscription("PICK");
		app.addMessagingSubscription("EVENT");
		app.addMessagingSubscription("LOCATION");
		app.addMessagingSubscription("GUI");
		app.addMessagingSubscription("CONFIG");
		app.setLoadCitiesEnabled(false);
		retCode = app();
		SEISCOMP_DEBUG("Number of remaining objects before destroying application: %d", Seiscomp::Core::BaseObject::ObjectCount());
	}

	SEISCOMP_DEBUG("Number of remaining objects after destroying application: %d", Seiscomp::Core::BaseObject::ObjectCount());
	return retCode;
}
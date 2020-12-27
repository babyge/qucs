/***************************************************************************
copyright            : 2016, 2020 Felix Salfelder
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

// attach plugins.
// basic functionality inspired by gnucap.

#include <iostream>
#include <map>
#include <ctype.h>

#include "platform.h"
#include "command.h"
#include "ap.h"
#include "io_trace.h"
#include "globals.h"
#include <unistd.h>	// TODO: io_.h

std::string findfile(const std::string& filename, const std::string& path, int mode);

namespace{

class plugins : public Command{
public:
	explicit plugins() : Command(){
	}
public:
  ~plugins(){
    for (std::map<std::string, void*>::iterator ii = attach_list.begin();
	ii != attach_list.end(); ++ii) {
      void* m=ii->second;
      if(m){
	dlclose(m);
      }
    }
  }

  std::string compile(std::string what) const{
	  // TODO: compile contents and return plugin name.
	  //    better cache results...
	  incomplete();
	  return what;
  }

  void attach(std::string what) const{
    // RTLD_NOW means to resolve symbols on loading
    // RTLD_LOCAL means symbols defined in a plugin are local
    int dl_scope = RTLD_LOCAL;
    int check = RTLD_NOW;
    void* handle;

    handle = dlopen((what).c_str(), check | dl_scope);
    if (handle) {
      attach_list[what] = handle;
    }else{
      std::cerr << "failed to attach " << what << " (" << errno << ")\n";
      std::cerr << dlerror() << "\n";
      exit(1); // temporary, should actually throw.
      //	throw Exception_something(dlerror());
    }
  }

private:
  void do_it(istream_t&, SchematicModel*) override;
private:
  mutable std::map<std::string, void*> attach_list;
} my_plugins;
Dispatcher<Command>::INSTALL p(&command_dispatcher, "load|attach", &my_plugins);

static std::string plugpath()
{
  const char* ppenv=getenv("QUCS_PLUGPATH");
  if(!ppenv){ untested();
    unreachable();
	 return "";
  }else{
    return ppenv;
  }
}

void plugins::do_it(istream_t& cs, SchematicModel*)
{
	cs.reset();
	if(cs.umatch("attach") || cs.umatch("load")){
		auto path = plugpath();
		std::string stem;
		cs >> stem;

		std::string what = stem + SOEXT;

		std::string full_file_name;
		if(what.size()==0){ untested();
		}else if(what[0]=='.'){
			full_file_name = what;
		}else{
			full_file_name = findfile(what, path, R_OK);
		}

		if (full_file_name != "") {
			// found it, with search
		}else{
			trace2("try _", stem, path);
			full_file_name = findfile(stem + "/_", path, R_OK);
		}

		if (full_file_name != "") {
		}else{untested();
			std::cerr << "cannot find plugin " + what + " in " +path + "\n";
			std::cerr << "(something wrong with installation?)\n";
			exit(1);
		}

		// if(is_directory){ untested();
		// 	full_file_name = compile(full_file_name);
		// }else{ untested();
		// }
		attach(full_file_name);

	}else{ untested();
		incomplete();
	}
}

}

#ifndef __eventdispatcher
#define __eventdispatcher

#include "eventhandler.hh"
#include <map>
#include <utility>

namespace otk {

typedef std::map<unsigned int, OtkEventHandler *> OtkEventMap;

class OtkEventDispatcher {
public:

  OtkEventDispatcher();
  virtual ~OtkEventDispatcher();

  virtual void clearAllHandlers(void);
  virtual void registerHandler(Window id, otk::OtkEventHandler *handler);
  virtual void clearHandler(Window id);
  virtual void dispatchEvents(void);

  inline void setFallbackHandler(otk::OtkEventHandler *fallback)
  { _fallback = fallback; }
  otk::OtkEventHandler *getFallbackHandler(void) const { return _fallback; }

  //! Sets an event handler that gets all events for all handlers after
  //! any specific handlers have received them
  inline void setMasterHandler(otk::OtkEventHandler *master)
  { _master = master; }
  otk::OtkEventHandler *getMasterHandler(void) const { return _master; }

  otk::OtkEventHandler *findHandler(Window win);

  inline Time lastTime() const { return _lasttime; }
  
private:
  OtkEventMap _map;
  OtkEventHandler *_fallback;
  OtkEventHandler *_master;

  //! The time at which the last XEvent with a time was received
  Time _lasttime;

  void dispatch(Window win, const XEvent &e);
};

}

#endif

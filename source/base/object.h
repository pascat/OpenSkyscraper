#ifndef OSS_BASE_OBJECT_H
#define OSS_BASE_OBJECT_H

#include "managedmemory.h"

//Legacy stuff we need to get rid of
#include "../general.h"
#include "baseevent.h"

#define OSSObjectLog std::cout << this->description() << " " << __FUNCTION__ << ": "
#define OSSObjectError std::cout << this->description() << " " << __FUNCTION__ << ": *** "


namespace OSS {
	namespace Base {
		class Object : public ManagedMemory {
		public:		
			//Runtime Type Information
			bool isKindOfClass(const std::type_info & typeidClass);
			virtual std::string className();
			virtual std::string instanceName();
			
			//Description
			virtual std::string description();
			
			//Events
			virtual bool handleEvent(Event * event);
			
			/**
			 * Event Handlers
			 *
			 * The following are convenience event handlers. The purpose of the handleEvent()
			 * function is to analyse the incoming event and calling the appropriate event
			 * handler function. The argument the event handler takes should be as far down
			 * the event union hierarchy as possible, so that the relevant information is accessible
			 * as fast as possible from within the handler.
			 *
			 * If another section of the engine defines other events, the engine should also provide
			 * another object class which implements the handleEvent() function, calls the parent's
			 * implementation and tries to handle the new events whenever the parent function returned
			 * false.
			 *
			 * All handler functions should be virtual (but NOT purely virtual) and return false by
			 * default. Whenever an object handles an event it should return true. If a subclass of
			 * "Object" relays events to its children, it should keep on relaying the events until one
			 * of the children returned true, at which point the subclass should also return true.
			 * This enables a convenient event handling where only ONE object gets to handle the event.
			 *
			 * It is the decision of each subclass of "Object" whether the event handling should be
			 * depth-first or depth-last. To achieve depth-first handling, the subclass should first
			 * pass on the event to its children and only handle it itself as a last resort if none of
			 * the children did. For depth-last the subclass should first try to handle the event itself
			 * by calling the parent's implementation of handleEvent() and only proceeding to its
			 * children if the parent returned false.
			 */
			virtual bool eventSDL(SDL_Event * event);
			
			virtual bool eventKey(SDL_Event * event);
			virtual bool eventKeyDown(SDL_Event * event)	{ return false; }
			virtual bool eventKeyUp(SDL_Event * event)		{ return false; }
			
			virtual bool eventMouse(SDL_Event * event);
			virtual bool eventMouseDown(SDL_Event * event)	{ return false; }
			virtual bool eventMouseMoved(SDL_Event * event)	{ return false; }
			virtual bool eventMouseUp(SDL_Event * event)	{ return false; }
			virtual bool eventMouseWheel(SDL_Event * event)	{ return false; }
		};
	}
}

//DEBUG: Autouse the base namespace until we've got things right
using namespace OSS::Base;


#endif

/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#ifndef GWEN_EVENTS_H
#define GWEN_EVENTS_H

#include <vector>
#include <list>
#include "Gwen/Exports.h"
#include "Gwen/Structures.h"
#include "Gwen/fastdelegate.h"

namespace Gwen 
{
	namespace Controls
	{
		class Base;
	}

	namespace Event
	{
		typedef fastdelegate::FastDelegate0<> fdcallback_empty;
		typedef fastdelegate::FastDelegate1<Gwen::Controls::Base*> fdcallback_control;
		typedef fastdelegate::FastDelegate1<const Gwen::String&> fdcallback_string;

		class Caller;

		// A class must be derived from this 
		class GWEN_EXPORT Handler
		{
			public:

				Handler();
				virtual ~Handler();

				void RegisterCaller( Caller* );
				void UnRegisterCaller( Caller* );

			protected:

				void CleanLinks();
				std::list<Caller*>	m_Callers;

			public:

				typedef void (Handler::*Function)( Gwen::Controls::Base* pFromPanel );
				typedef void (Handler::*FunctionWithControl)( Gwen::Controls::Base* pFromPanel, Gwen::Controls::Base* pStoredPanel );
				typedef void (Handler::*FunctionBlank)();
				typedef void (Handler::*FunctionStr)( const Gwen::String& string );

		};



		//
		//
		//
		class GWEN_EXPORT Caller
		{
			public:

				Caller();
				~Caller();

				void operator += (fdcallback_empty delegate)
				{
					_callbacks_empty.push_back(delegate);
				}

				void operator += (fdcallback_control delegate)
				{
					_callbacks_control.push_back(delegate);
				}

				void operator += (fdcallback_string delegate)
				{
					_callbacks_string.push_back(delegate);
				}

				void Call( Controls::Base* pThis );

				template <typename T>
				void Add( Event::Handler* ob, T f )
				{
					AddInternal( ob, static_cast<Handler::Function>(f) );
				}

				template <typename T>
				void Add( Event::Handler* ob, T f, Controls::Base* pObj )
				{
					AddInternal( ob, static_cast<Handler::FunctionWithControl>(f), pObj );
				}

				template <typename T>
				void Add( Event::Handler* ob, void (T::*f)() )
				{
					AddInternal( ob, static_cast<Handler::FunctionBlank>(f) );
				}

				void RemoveHandler( Event::Handler* pObject );

			protected:

				void CleanLinks();
				void AddInternal( Event::Handler* pObject, Handler::Function pFunction );
				void AddInternal( Event::Handler* pObject, Handler::FunctionWithControl pFunction, Gwen::Controls::Base* pControl );
				void AddInternal( Event::Handler* pObject, Handler::FunctionBlank pFunction );

				std::vector<fdcallback_empty> _callbacks_empty;
				std::vector<fdcallback_control> _callbacks_control;
				std::vector<fdcallback_string> _callbacks_string;

				struct handler
				{
					handler()
					{
						fnFunction = NULL;
						fnFunctionWithPanel = NULL;
						fnFunctionBlank = NULL;
						pObject = NULL;
						pControl = NULL;
					}

					Handler::Function				fnFunction;
					Handler::FunctionWithControl	fnFunctionWithPanel;
					Handler::FunctionBlank			fnFunctionBlank;

					

					Event::Handler*			pObject;

					// Available Data Slots
					Gwen::Controls::Base*	pControl;
				};

				std::list<handler> m_Handlers;
		};

	}

}
#endif

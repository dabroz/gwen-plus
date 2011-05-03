/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#include <list>
#include "Gwen/Exports.h"
#include "Gwen/Structures.h"

// TODO: REMOVE THIS - IT SUCKS. Template the function instead.
#define GWEN_MCALL( fnc ) this, (Gwen::Event::Function)&fnc

namespace Gwen 
{
	namespace Controls
	{
		class Base;
	}

	namespace Event
	{

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

		};

		typedef void (Event::Handler::*Function)( Controls::Base* pFromPanel );
		typedef void (Event::Handler::*FunctionStr)( const Gwen::String& string );

		//
		//
		//
		class GWEN_EXPORT Caller
		{
			public:

				Caller();
				~Caller();

				void Call( Controls::Base* pThis );

				template <typename T>
				void Add( Event::Handler* ob, T f )
				{
					AddInternal( ob, (Function) f );
				}
				
				void RemoveHandler( Event::Handler* pObject );

			protected:

				void CleanLinks();
				void AddInternal( Event::Handler* pObject, Function pFunction );

				struct handler
				{
					Function		fnFunction;
					Event::Handler*		pObject;
				};

				std::list<handler> m_Handlers;
		};

	}

}
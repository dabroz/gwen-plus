#include "Gwen/UnitTest/UnitTest.h"
#include "Gwen/Controls/TreeControl.h"

using namespace Gwen;

class Window : public GUnit
{
	public:

	GWEN_CONTROL_INLINE( Window, GUnit )
	{
		Controls::Button* pButton = new Controls::Button( this );
		pButton->SetText( "Open a Window" );
		pButton->onPress.AddBlank( this, &ThisClass::OpenWindow );

		m_iWindowCount = 1;
	}

	void OpenWindow()
	{
		Controls::WindowControl* pWindow = new Controls::WindowControl( GetCanvas() );
		pWindow->SetTitle( Utility::Format( L"Window %i", m_iWindowCount ) );
		pWindow->SetSize( 200+rand()%100, 200+rand()%100 );
		pWindow->SetPos( rand()%700, rand()%400 );

		m_iWindowCount++;
	}

	int m_iWindowCount;

};



DEFINE_UNIT_TEST( Window, L"Window" );
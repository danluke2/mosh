#include <stdio.h>
#include <wctype.h>

#include "parseraction.hpp"
#include "terminal.hpp"

using namespace Parser;

std::string Action::str( void )
{
  char thechar[ 10 ] = { 0 };
  if ( char_present ) {
    snprintf( thechar, 10, iswprint( ch ) ? "(%lc)" : "(0x%x)", ch );
  }

  return name() + std::string( thechar );
}

void Print::act_on_terminal( Terminal::Emulator *emu ) const
{
  emu->print( this );
}

void Execute::act_on_terminal( Terminal::Emulator *emu ) const
{
  emu->execute( this );
}

void Clear::act_on_terminal( Terminal::Emulator *emu ) const
{
  emu->dispatch.clear( this );
}

void Param::act_on_terminal( Terminal::Emulator *emu ) const
{
  emu->dispatch.newparamchar( this );
}

void Collect::act_on_terminal( Terminal::Emulator *emu ) const
{
  emu->dispatch.collect( this );
}

void CSI_Dispatch::act_on_terminal( Terminal::Emulator *emu ) const
{
  emu->CSI_dispatch( this );
}

void Esc_Dispatch::act_on_terminal( Terminal::Emulator *emu ) const
{
  emu->Esc_dispatch( this );
}

void OSC_Put::act_on_terminal( Terminal::Emulator *emu ) const
{
  emu->dispatch.OSC_put( this );
}

void OSC_Start::act_on_terminal( Terminal::Emulator *emu ) const
{
  emu->dispatch.OSC_start( this );
}

void OSC_End::act_on_terminal( Terminal::Emulator *emu ) const
{
  emu->OSC_end( this );
}

void UserByte::act_on_terminal( Terminal::Emulator *emu ) const
{
  emu->dispatch.terminal_to_host.append( emu->user.input( this,
							  emu->fb.ds.application_mode_cursor_keys ) );
}

void Resize::act_on_terminal( Terminal::Emulator *emu ) const
{
  emu->resize( width, height );
  handled = true;
}

bool Action::operator==( const Action &other ) const
{
  return ( char_present == other.char_present )
    && ( ch == other.ch )
    && ( handled == other.handled );
}
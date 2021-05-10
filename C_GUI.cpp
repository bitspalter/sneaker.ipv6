//////////////////////////////////////////////////////////////////////////////////
// [ C_GUI_Class_Source ]
//////////////////////////////////////////////////////////////////////////////////

#include "C_GUI.hpp"

//////////////////////////////////////////////////////////////////////////////////
// [ Konstructor ]  
//////////////////////////////////////////////////////////////////////////////////
C_GUI::C_GUI(){

   this->set_default_size(1000, 600);

   /////////////////////////////////////////////////
   // Button
   
   sbutton.start.set_label("start");
   sbutton.start.set_size_request(100, 30);
   
   sbutton.stop.set_label("stop");
   sbutton.stop.set_size_request(100, 30);
   sbutton.stop.set_sensitive(false);

   /////////////////////////////////////////////////
   // scombo
   
   scombo.interface.set_size_request(100, 30); 

   /////////////////////////////////////////////////
   // TreeView
   
   stview.host.view.setWindow(this);
   stview.host.window.add(stview.host.view);
   stview.host.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
   
   auto column = stview.host.view.get_column(0);
   column->set_title("Host");
   
   stview.packet.view.setWindow(this);
   stview.packet.window.add(stview.packet.view);
   stview.packet.window.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

   column = stview.packet.view.get_column(0);
   column->set_title("Packet");
   
   /////////////////////////////////////////////////
   // Paned
   
   spaned.ph.add1(stview.packet.window);
   spaned.ph.add2(stview.host.window);
   
   spaned.ph.set_position(300);
   
   //////////////////////////////////////////////////////////////
   // HeaderBar
   
   set_titlebar(header);
   
   header.set_title("sneaker.ipv6.0.1");
   header.set_subtitle("Welcome");
   header.set_show_close_button();
   
   header.pack_start(scombo.interface);
   header.pack_start(sbutton.start);
   header.pack_start(sbutton.stop);
   
   ///////////////////////////////////////////////////////

   add(spaned.ph);
}

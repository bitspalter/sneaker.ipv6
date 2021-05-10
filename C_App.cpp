//////////////////////////////////////////////////////////////////////////////////
// [ APP_Class_Source ]
//////////////////////////////////////////////////////////////////////////////////

#include "C_App.hpp"

//////////////////////////////////////////////////////////////////////////////////
// [ Konstructor ]  
//////////////////////////////////////////////////////////////////////////////////
C_App::C_App(){

   if(geteuid()){

      cap_flag_value_t cap_flag_value;  
      cap_t caps = cap_get_proc();
      
      if(caps){
         
         if(cap_get_flag(caps, CAP_NET_RAW, CAP_EFFECTIVE, &cap_flag_value) == 0){
         
            if(cap_flag_value != CAP_SET){
               
               Gtk::MessageDialog dialog(*this, "You have to be ROOT or need CAP_NET_RAW capabilities!", false, Gtk::MESSAGE_ERROR);
               dialog.run();
               
               cap_free(caps);
               exit(EXIT_FAILURE);
            }
         }

         cap_free(caps);
      }
   }

   /////////////////////////////////////////////
   
   if(CNet.init() != C_NET_READY){
      cout << "ERROR: CNet.init" << endl;
      Gtk::MessageDialog dialog(*this, "Network Error", false, Gtk::MESSAGE_ERROR);
      dialog.run();
      return;
   }
   
   /////////////////////////////////////////////
   //Fill the interface combo:
   const vector<S_Net_Interface>* pDA_Interface = CNet.CNInterface.get_pDA_Interface();

   for(auto iface : *pDA_Interface) scombo.interface.append(iface.ps_Name);

   int nInterface = CNet.CNInterface.get_First_Active();
   
   if(nInterface == -1){
      scombo.interface.set_sensitive(false);
      sbutton.start.set_sensitive(false);
      Gtk::MessageDialog dialog(*this, "no active network interface", false, Gtk::MESSAGE_ERROR);
      dialog.run();
   }else{
      scombo.interface.set_active(nInterface);
   }

   scombo.interface.signal_changed().connect(sigc::mem_fun(*this, &C_App::on_device_changed));
   
   //////////////////////////////////////////////////////////////
   // Button

   sbutton.start.signal_clicked().connect(sigc::mem_fun(*this, &C_App::on_button_start));
   sbutton.stop.signal_clicked().connect(sigc::mem_fun(*this, &C_App::on_button_stop));

   ////////////////////////
   
   signal_configure_event().connect(sigc::mem_fun(*this, &C_App::on_configure_changed), false);
   
   ////////////////////////
   
   /////////////////////////////////////////////
   // signal

   CNet.sig_packet.connect(sigc::mem_fun(*this, &C_App::on_packet));

   ////////////////////////
   
   show_all_children();
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_button_start ]
//////////////////////////////////////////////////////////////////////////////////
void C_App::on_button_start(){

   const S_Net_Interface* pSInterface = 0;
   
   pSInterface = CNet.CNInterface.get_pInterface(scombo.interface.get_active_row_number());
   
   if(pSInterface == nullptr){
      cout << "Error get_pInterface:" << scombo.interface.get_active_row_number() << endl;  
      return; 
   }
   
   //////////////////////////////

   stview.host.view.m_LStore->clear();
   stview.packet.view.m_LStore->clear();
   
   //////////////////////////////
   
   if(bRun) return;
   
   TpSInterface = pSInterface;

   pWorker = new std::thread([this]{this->sneak();});

   bRun = true;
   
   this->set_title("sneaking ... ");

   //////////////////////////////

   sbutton.stop.set_sensitive(true);
   sbutton.start.set_sensitive(false);
   scombo.interface.set_sensitive(false);
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_button_stop ]
//////////////////////////////////////////////////////////////////////////////////
void C_App::on_button_stop(){

   CNet.stop();
   
   if(pWorker->joinable())
      pWorker->join();
   delete pWorker;
   pWorker = nullptr;
   
   bRun = false;
   
   finish();
   
   sbutton.stop.set_sensitive(false);
   sbutton.start.set_sensitive(true);
   scombo.interface.set_sensitive(true);
   
   this->set_title("sneaker.ipv6.0.1");
}
//////////////////////////////////////////////////////////////////////////////////
// [ sneak ] (THREAD)
//////////////////////////////////////////////////////////////////////////////////
void C_App::sneak(){
   CNet.start(TpSInterface);
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_packet ]
//////////////////////////////////////////////////////////////////////////////////
void C_App::on_packet(){

   if(CNet.CDA_Result.empty()) return;
   
   auto iTRes = CNet.CDA_Result.back();
    
   S_host_Result* iTResult = &iTRes;
   
   char pItemIP[256];

   inet_ntop(AF_INET6, iTResult->IP, pItemIP, 256);
   
   char pItemMAC[256];

   sprintf(pItemMAC, "%02X:%02X:%02X:%02X:%02X:%02X", 
          (int)iTResult->MAC[0], (int)iTResult->MAC[1], 
          (int)iTResult->MAC[2], (int)iTResult->MAC[3],
          (int)iTResult->MAC[4], (int)iTResult->MAC[5]);

   ///////////////////////////////////////////////////

   Gtk::TreeModel::iterator iter = stview.packet.view.m_LStore->append();
   Gtk::TreeModel::Row row       = *iter;

   row.set_value(0, stview.packet.view.m_LStore->children().size());
   row.set_value(1, (Glib::ustring)pItemIP);
   row.set_value(2, (Glib::ustring)pItemMAC);

   // autoscroll
   Gtk::TreeModel::Path path = stview.packet.view.m_LStore->get_path(iter);
   stview.packet.view.scroll_to_row(path);
}
//////////////////////////////////////////////////////////////////////////////////
// [ finish ]
//////////////////////////////////////////////////////////////////////////////////
void C_App::finish(){
   list<S_host_Result> CDA_TResult; 
   list<S_host_Result>::iterator iResult;
   list<S_host_Result>::iterator iTResult;
   bool bInsert = true;
   
   ///////////////////////////////////////////////////////
   
   for(iResult = CNet.CDA_Result.begin(); iResult != CNet.CDA_Result.end(); ++iResult){
      
      if(*((QWORD*)iResult->IP) == 0 && *((QWORD*)iResult->IP + 1) == 0)
         continue;
      
      //if(*((DWORD*)iResult->IP) == 0 || (*((DWORD*)iResult->IP) & 0x00FFFFFF) != TpSInterface->dw_Network)
      //   continue;
      
      bInsert = true;

      for(iTResult = CDA_TResult.begin(); iTResult != CDA_TResult.end(); ++iTResult){

         if(*((QWORD*)iResult->IP)     == *((QWORD*)iTResult->IP) &&  
            *((QWORD*)iResult->IP + 1) == *((QWORD*)iTResult->IP + 1)){
            
            bInsert = false;
            break;
         }
      }
      
      if(bInsert) CDA_TResult.push_back(*iResult);
   }

   ///////////////////////////////////////////////////////

   CDA_TResult.sort(this->SortByIp);
   
   for(iTResult = CDA_TResult.begin(); iTResult != CDA_TResult.end(); ++iTResult){

      char pItemIP[256];

      inet_ntop(AF_INET6, iTResult->IP, pItemIP, 256);
      
      char pItemMAC[256];

      sprintf(pItemMAC, "%02X:%02X:%02X:%02X:%02X:%02X", 
             (int)iTResult->MAC[0], (int)iTResult->MAC[1], 
             (int)iTResult->MAC[2], (int)iTResult->MAC[3],
             (int)iTResult->MAC[4], (int)iTResult->MAC[5]);

      ///////////////////////////////////////////////////

      Gtk::TreeModel::iterator iter = stview.host.view.m_LStore->append();
      Gtk::TreeModel::Row row       = *iter;

      row.set_value(0, stview.host.view.m_LStore->children().size());
      row.set_value(1, (Glib::ustring)pItemIP);
      row.set_value(2, (Glib::ustring)pItemMAC);

      // autoscroll
      Gtk::TreeModel::Path path = stview.host.view.m_LStore->get_path(iter);
      stview.host.view.scroll_to_row(path);
   }
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_configure_changed ]
//////////////////////////////////////////////////////////////////////////////////
bool C_App::on_configure_changed(GdkEventConfigure* configure_event){

   if(configure_event->send_event) return(false);
   
   if(!this->is_maximized()){
      spaned.ph.set_position(configure_event->width / 2 - 20);
   }else{
      spaned.ph.set_position(configure_event->width / 2);
   }

   return(false);
}
//////////////////////////////////////////////////////////////////////////////////
// [ on_device_changed ]
//////////////////////////////////////////////////////////////////////////////////
void C_App::on_device_changed(){
   
   const S_Net_Interface* pSInterface = nullptr;
   
   pSInterface = CNet.CNInterface.get_pInterface(scombo.interface.get_active_row_number());

   if(!pSInterface->uc_Active || pSInterface->uc_LoopBack) 
      sbutton.start.set_sensitive(false);
   else 
      sbutton.start.set_sensitive(true);
}

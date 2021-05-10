//////////////////////////////////////////////////////////////////////////////////
// [ APP_Class_Header ]
//////////////////////////////////////////////////////////////////////////////////
//
// sneaker.ipv6 ver:0.1
//
// [::Last modi: 10.05.21 L.ey (µ~)::]
//
//
#ifndef _C_APP_H_
 #define _C_APP_H_

 #include <iostream>
 #include <thread>
  
 using namespace std;
 
 #include <sys/capability.h> // test

 #include "C_GUI.hpp"
 #include "C_Net.hpp"
 
//////////////////////////////////////////////////////////////////////////////////
// CONSTANT
//////////////////////////////////////////////////////////////////////////////////
 
 const int C_APP_ERROR = 0x00;
 const int C_APP_READY = 0x01;

//////////////////////////////////////////////////////////////////////////////////
// STRUCT
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////
// CLASS
//////////////////////////////////////////////////////////////////////////////////

 class C_App : public C_GUI { 
    
    public:
        
       C_App();
       virtual ~C_App(){};

    protected:

       static bool SortByIp(const S_host_Result& lhs, const S_host_Result& rhs){

          return(be64toh(*((QWORD*)lhs.IP))     < be64toh(*((QWORD*)rhs.IP)) || 
                 be64toh(*((QWORD*)lhs.IP + 1)) < be64toh(*((QWORD*)rhs.IP + 1)));
       }
       
       void finish();
       
       //////////////////////////////////
       //Signal handlers:
       
       void on_button_start();
       void on_button_stop();

       void on_packet();

       bool on_configure_changed(GdkEventConfigure* configure_event);
       
       void on_device_changed();
       
       /////////////////////////////////
       
       C_Net CNet;

       /////////////////////////////////
       
       // ((( SEND THREAD )))
       thread* pWorker = {nullptr};
       
       void sneak();
       bool bRun = {false};

       const S_Net_Interface* TpSInterface = {nullptr};
 };

#endif // _C_APP_H_

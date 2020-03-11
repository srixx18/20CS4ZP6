// since implementation of Comm requires access to Wallet's stuff, 
// we have to put the implementation of Wallet here

// unblock _com_debug to see the message traffic as passed on by comm
//#define _com_debug

#ifndef _comm_impl_hpp
#define _comm_imp_hpp

Comm::Comm(Wallet *w1,Wallet *w2) {  // initialization for wdialogue
   this->w1 = w1;
   this->w2 = w2;
   this->mint = 0;
#ifdef _com_debug
   sprintf_s(name1,"wallet %d",w1->walletid);
   sprintf_s(name2,"wallet %d",w2->walletid);
#endif
}//end constr Comm

Comm::Comm(Wallet *w1,Mint* mint) {  // initialization for mdialogue
   this->w1 = w1;
   this->w2 = 0;
   this->mint = mint;
#ifdef _com_debug
   sprintf_s(name1,"wallet %d",w1->walletid);
   sprintf_s(name2,"mint");
#endif
}//end constr Comm



void Comm::wcomm(Message& m) {
   while(true) {
      if (m.x_code == Message::x_start) {
#ifdef _com_debug
          printf("-------------wcomm: passing %s to %s",m.sx(),name2);
          GETCHAR();
          strcpy_s(m.message,name1);
#endif
          m = w2->wdialogue(m);
          if (m.x_code == Message::x_hup) {
#ifdef _com_debug
             printf("-------------wcomm: passing %s to %s",m.sx(),name1);
             GETCHAR();
#endif
             w1->wdialogue(m);
             return;
          }
#ifdef _com_debug
          printf("-------------wcomm: passing %s to %s",m.sx(),name1);
          GETCHAR();
#endif
          m = w1->wdialogue(m);
          continue;
      }
      if (m.x_code == Message::x_ok) {
#ifdef _com_debug
         printf("-------------wcomm: passing %s to %s",m.sx(),name2);
         GETCHAR();
#endif
         m = w2->wdialogue(m);
         if (m.x_code == Message::x_hup) {
#ifdef _com_debug
            printf("-------------wcomm: passing %s to %s",m.sx(),name1);
            GETCHAR();
#endif
            w1->wdialogue(m);
            return;
         }
#ifdef _com_debug
         printf("-------------wcomm: passing %s to %s",m.sx(),name1);
         GETCHAR();
#endif
         m = w1->wdialogue(m);
         continue;
      }
      
      if (m.x_code == Message::x_message) {
#ifdef _com_debug
         printf("-------------wcomm: passing %s to %s",m.sx(),name2);
         GETCHAR();
#endif
         m = w2->wdialogue(m);
         if (m.x_code == Message::x_hup) {
#ifdef _com_debug
            printf("-------------wcomm: passing %s to %s",m.sx(),name1);
            GETCHAR();
#endif
            w1->wdialogue(m);
            return;
         }
#ifdef _com_debug
         printf("-------------wcomm: passing %s to %s",m.sx(),name1);
         GETCHAR();
#endif
         m = w1->wdialogue(m);
         continue;
      }
      
      if (m.x_code == Message::x_hup) {
#ifdef _com_debug
         printf("-------------wcomm: passing %s to %s",m.sx(),name2);
         GETCHAR();
#endif
         m = w2->wdialogue(m);
         return;
      }
   }//endwhile
}//end Comm::wcomm



void Comm::mcomm(Message& m) {
   while(true) {

     if (m.x_code == Message::x_start) {
#ifdef _com_debug
       printf("-------------mcomm: passing %s to %s",m.sx(),name2);
       GETCHAR();
       strcpy_s(m.message,name1);
#endif
       m = mint->mdialogue(m);
       if (m.x_code == Message::x_hup) {
#ifdef _com_debug
         printf("-------------mcomm: passing %s to %s",m.sx(),name1);
         GETCHAR();
#endif
         w1->mdialogue(m);
         return;
       }
#ifdef _com_debug
       printf("-------------mcomm: passing %s to %s",m.sx(),name1);
       GETCHAR();
#endif
       m = w1->mdialogue(m);
       continue;
     }
      
     if (m.x_code == Message::x_ok) {
#ifdef _com_debug
       printf("-------------mcomm: passing %s to %s",m.sx(),name2);
       GETCHAR();
#endif
       m = mint->mdialogue(m);
       if (m.x_code == Message::x_hup) {
#ifdef _com_debug
         printf("-------------mcomm: passing %s to %s",m.sx(),name1);
         GETCHAR();
#endif
         w1->mdialogue(m);
         return;
       }
#ifdef _com_debug
       printf("-------------mcomm: passing %s to %s",m.sx(),name1);
       GETCHAR();
#endif
       m = w1->mdialogue(m);
       continue;
     }
      
     if (m.x_code == Message::x_message) {
#ifdef _com_debug
       printf("-------------mcomm: passing %s to %s",m.sx(),name2);
       GETCHAR();
#endif
       m = mint->mdialogue(m);
       if (m.x_code == Message::x_hup) {
#ifdef _com_debug
         printf("-------------mcomm: passing %s to %s",m.sx(),name1);
         GETCHAR();
#endif
         w1->mdialogue(m);
         return;
       }
#ifdef _com_debug
       printf("-------------mcomm: passing %s to %s",m.sx(),name1);
       GETCHAR();
#endif
       m = w1->mdialogue(m);
       continue;
     }
      
     if (m.x_code == Message::x_hup) {
#ifdef _com_debug
       printf("-------------mcomm: passing %s to %s",m.sx(),name2);
       GETCHAR();
#endif
       m = mint->mdialogue(m);
       return;
     }
   }//endwhile
}//end Comm::comm

#endif

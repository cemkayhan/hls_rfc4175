#include "hls_rfc4175.h"

int main()
{
  hls::stream<ap_axiu<24,1,1,1> > Vid_Data;
  hls::stream<ap_axiu<8,1,1,1> > Rfc4175_Data;
  ap_uint<16> Width=1920;
  ap_uint<16> Height=10;
  ap_uint<7> Payload_Type=96;
  ap_uint<32> Ssrc=0xFFEEDDCC;
  ap_uint<32> Time_Stamp=0x01020304;

  ap_axiu<24,1,1,1> Vid_Data_;
  for(auto I=0;I<Height;++I){
    for(auto J=0;J<Width-1;++J){
      Vid_Data_.data=I*Width+J;
      Vid_Data_.last=0;
      Vid_Data<<Vid_Data_;
    }
    Vid_Data_.data=0xFFFF;
    Vid_Data_.last=1;
    Vid_Data<<Vid_Data_;
  }

  //ap_axiu<24,1,1,1> Vid_Data_;
  for(auto I=0;I<Height;++I){
    for(auto J=0;J<Width-1;++J){
      Vid_Data_.data=I*Width+J;
      Vid_Data_.last=0;
      Vid_Data<<Vid_Data_;
    }
    Vid_Data_.data=0xFFFF;
    Vid_Data_.last=1;
    Vid_Data<<Vid_Data_;
  }

  D_TOP_(
    Vid_Data,
    Rfc4175_Data,
    Width,
    Height,
    Payload_Type,
    Ssrc,
    Time_Stamp
  );

  D_TOP_(
    Vid_Data,
    Rfc4175_Data,
    Width,
    Height,
    Payload_Type,
    Ssrc,
    Time_Stamp
  );

  while(!Rfc4175_Data.empty()){
    Rfc4175_Data.read();
  }
}

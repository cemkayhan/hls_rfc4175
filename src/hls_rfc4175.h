#if !defined(HLS_RFC4175_H_INCLUDE_GUARD_)
#define HLS_RFC4175_H_INCLUDE_GUARD_

#include "ap_int.h"
#include "ap_axi_sdata.h"
#include "hls_stream.h"

void D_TOP_(
  hls::stream<ap_axiu<24,1,1,1> >& Vid_Data,
  hls::stream<ap_axiu<8,1,1,1> >& Rfc4175_Data,
  ap_uint<16> Width,
  ap_uint<16> Height,
  ap_uint<7> Payload_Type,
  ap_uint<32> Ssrc,
  ap_uint<32> Time_Stamp
);

template<int ID>
static void Packetize_Lines(
  hls::stream<ap_axiu<24,1,1,1> >& Vid_Data,
  hls::stream<ap_axiu<8,1,1,1> >& Rfc4175_Data,
  ap_uint<16> Width,
  ap_uint<16> Height,
  ap_uint<7> Payload_Type,
  ap_uint<32> Ssrc,
  ap_uint<32> Time_Stamp
){
  static ap_uint<16> Line_Cntr=0;
#pragma HLS RESET variable=Line_Cntr

  static ap_uint<32> Sequence_Num=0;
#pragma HLS RESET variable=Sequence_Num

  static ap_uint<1> M;
#pragma HLS RESET variable=M

  if(Height-1==Line_Cntr)
    M=1;
  else
    M=0;

  loopPix: for(auto I=0;I<10+Width;++I){
#pragma HLS PIPELINE II=2
    if(0==I){
      Rfc4175_Data<< ap_axiu<8,1,1,1> {0x80,-1,-1,0,0,0,0};
      Rfc4175_Data<< ap_axiu<8,1,1,1> {(M,Payload_Type),-1,-1,0,0,0,0};
    }
    else if(1==I){
      Rfc4175_Data<< ap_axiu<8,1,1,1> {Sequence_Num(15,8),-1,-1,0,0,0,0};
      Rfc4175_Data<< ap_axiu<8,1,1,1> {Sequence_Num(7,0),-1,-1,0,0,0,0};
    }
    else if(2==I){
      Rfc4175_Data<< ap_axiu<8,1,1,1> {Time_Stamp(31,24),-1,-1,0,0,0,0};
      Rfc4175_Data<< ap_axiu<8,1,1,1> {Time_Stamp(23,16),-1,-1,0,0,0,0};
    }
    else if(3==I){
      Rfc4175_Data<< ap_axiu<8,1,1,1> {Time_Stamp(15,8),-1,-1,0,0,0,0};
      Rfc4175_Data<< ap_axiu<8,1,1,1> {Time_Stamp(7,0),-1,-1,0,0,0,0};
    }
    else if(4==I){
      Rfc4175_Data<< ap_axiu<8,1,1,1> {Ssrc(31,24),-1,-1,0,0,0,0};
      Rfc4175_Data<< ap_axiu<8,1,1,1> {Ssrc(23,16),-1,-1,0,0,0,0};
    }
    else if(5==I){
      Rfc4175_Data<< ap_axiu<8,1,1,1> {Ssrc(15,8),-1,-1,0,0,0,0};
      Rfc4175_Data<< ap_axiu<8,1,1,1> {Ssrc(7,0),-1,-1,0,0,0,0};
    }
    else if(6==I){
      Rfc4175_Data<< ap_axiu<8,1,1,1> {Sequence_Num(31,24),-1,-1,0,0,0,0};
      Rfc4175_Data<< ap_axiu<8,1,1,1> {Sequence_Num(23,16),-1,-1,0,0,0,0};
    }
    else if(7==I){
      Rfc4175_Data<< ap_axiu<8,1,1,1> {Width(14,7),-1,-1,0,0,0,0};
      Rfc4175_Data<< ap_axiu<8,1,1,1> {ap_uint<8> {(Width(6,0),ap_uint<1> {0})},-1,-1,0,0,0,0};
    }
    else if(8==I){
      Rfc4175_Data<< ap_axiu<8,1,1,1> {Line_Cntr(15,8),-1,-1,0,0,0,0};
      Rfc4175_Data<< ap_axiu<8,1,1,1> {Line_Cntr(7,0),-1,-1,0,0,0,0};
    }
    else if(9==I){
      Rfc4175_Data<< ap_axiu<8,1,1,1> {0,-1,-1,0,0,0,0};
      Rfc4175_Data<< ap_axiu<8,1,1,1> {0,-1,-1,0,0,0,0};
    }
    else {
      ap_axiu<24,1,1,1> Vid_Data_;
      Vid_Data>>Vid_Data_;
      Rfc4175_Data<< ap_axiu<8,1,1,1> {Vid_Data_.data(15,8),-1,-1,0,0,0,0};
      Rfc4175_Data<< ap_axiu<8,1,1,1> {Vid_Data_.data(7,0),-1,-1,0,Vid_Data_.last,0,0};
    }
  }

  ++Sequence_Num;
  if(Height-1==Line_Cntr)
    Line_Cntr=0;
  else
    ++Line_Cntr;
}

#endif

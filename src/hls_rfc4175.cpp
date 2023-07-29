#include "hls_rfc4175.h"

void D_TOP_(
  hls::stream<ap_axiu<24,1,1,1> >& Vid_Data,
  hls::stream<ap_axiu<8,1,1,1> >& Rfc4175_Data,
  ap_uint<16> Width,
  ap_uint<16> Height,
  ap_uint<7> Payload_Type,
  ap_uint<32> Ssrc,
  ap_uint<32> Time_Stamp
){
#pragma HLS INTERFACE axis port=Vid_Data
#pragma HLS INTERFACE axis port=Rfc4175_Data

#pragma HLS INTERFACE ap_none port=Time_Stamp
#pragma HLS STABLE variable=Time_Stamp

#if 1==D_RETURN_S_AXILITE_
#pragma HLS INTERFACE s_axilite bundle=Ctrl             port=return
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x10 port=Width
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x18 port=Height
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x20 port=Payload_Type
#pragma HLS INTERFACE s_axilite bundle=Ctrl offset=0x28 port=Ssrc
#pragma HLS STABLE variable=Width
#pragma HLS STABLE variable=Height
#pragma HLS STABLE variable=Payload_Type
#pragma HLS STABLE variable=Ssrc
#endif

#if 1==D_RETURN_AP_CTRL_HS_
#pragma HLS INTERFACE ap_none port=Width
#pragma HLS INTERFACE ap_none port=Height
#pragma HLS INTERFACE ap_none port=Payload_Type
#pragma HLS INTERFACE ap_none port=Ssrc
#pragma HLS STABLE variable=Width
#pragma HLS STABLE variable=Height
#pragma HLS STABLE variable=Payload_Type
#pragma HLS STABLE variable=Ssrc
#endif

  loopLines: for(auto I=0;I<Height;++I){
#pragma HLS DATAFLOW
    Packetize_Lines<0>(
      Vid_Data,
      Rfc4175_Data,
      Width,
      Height,
      Payload_Type,
      Ssrc,
      Time_Stamp
    );
  }
}

#!/bin/sh

D_RETURN_S_AXILITE_=1
D_RETURN_AP_CTRL_HS_=0
D_ID_=$(cat ../ID)
D_TOP_=$(cat ../TOP)_Id${D_ID_}

CFLAGS=""
CFLAGS="$CFLAGS -DD_RETURN_S_AXILITE_=$D_RETURN_S_AXILITE_"
CFLAGS="$CFLAGS -DD_RETURN_AP_CTRL_HS_=$D_RETURN_AP_CTRL_HS_"
CFLAGS="$CFLAGS -DD_TOP_=$D_TOP_"

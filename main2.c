#include"time.h"
#include"choose.h"
#include"prog_bar.h"
#include"zip.h"
#include"unzip.h"
#include"ppm_lib.h"

int main(){
PPM_IMG *is;
	is=ppmNew(64,7,255,3);
int r=0;int g=0;int b=255;
int pix=pixel(r,g,b);
for(int i=0;i<7;i++){
	for(int j=0;j<64;j++){
		ppmWrite(is,j,i,pix);
	}
b=b-30;
pix=pixel(r,g,b);
}
ppmSave(is,"projet_image/test64");
ppmClose(is);
return 0;
}

#include"time.h"
#include"choose.h"
#include"zip.h"
#include"unzip.h"

int main(){
int i,j;
 PPM_IMG *is;
	is=ppmNew(63,10,255,3);
int r=0;int g=0;int b=255;
int pix=pixel(r,g,b);
for( i=0;i<5;i++){
	for( j=0;j<63;j++){
		ppmWrite(is,j,i,pix);
	}
r=r+50;b=b+50;
pix=pixel(r,g,b);
}
r=0; g=0; b=255;
 pix=pixel(r,g,b);
for( i=5;i<10;i++){
	for( j=0;j<63;j++){
		ppmWrite(is,j,i,pix);
	}
r=r+50;b=b+50;
pix=pixel(r,g,b);
}
ppmSave(is,"projet_image/imageindex");
ppmClose(is);
return 0;
}

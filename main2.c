#include"time.h"
#include"choose.h"
#include"zip.h"
#include"unzip.h"

int main(){
 PPM_IMG *is;
	is=ppmNew(63,5,255,3);
int r=0;int g=0;int b=255;
int pix=pixel(r,g,b);
for(int i=0;i<5;i++){
	for(int j=0;j<63;j++){
		ppmWrite(is,j,i,pix);
	}
r=r+50;b=b+50;
pix=pixel(r,g,b);
}
ppmSave(is,"projet_image/imagergb");
ppmClose(is);
return 0;
}

//NAMA		: FEBBY RONALDO
//NRP		: 2210161032
//KELAS		: 1 D4 Teknik Komputer B
//FILE		: PROJECT_UAS.C
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


void ind(void);

int A, b, saldo, tt, stat, i, no, tu;	char B, C[30], c[14], D, pin[7], buff[50], user[11], np[7];

struct nasabah{char no_rekening[11]; char nama_lengkap[30]; char pin[6]; int saldo_terakhir;};
struct date{int tgl; int bln; int thn;};
struct time{int dtk; int mnt; int jam;};
struct loctime{struct time; struct date;};

FILE *fbuka, *fr[5];	time_t tx;

struct nasabah a[9];	struct loctime *y;	struct tm *waktu;

main()
{
	fbuka=fopen("Nasabah.txt","r+");	i=0;
	while(fgets(buff, sizeof(buff), fbuka)!=NULL)	{
	if(buff[0]!='\n')	
	sscanf(buff, "%[^,],%[^,],%[^,],%d", a[i].no_rekening, a[i].nama_lengkap, a[i].pin, &a[i].saldo_terakhir); else i--; i++;
	} fclose(fbuka);
	
	awal:
		A=0;	stat=0;		system("cls");
		printf("\t\t    SELAMAT DATANG DI BANK CYBER	   \n");
		printf("\t\t (Silahkan masukkan username anda)   \n");
		printf("\t\t =================================   \n");
		printf("\t\t     WELLCOME TO THE CYBER BANK	   \n");
		printf("\t\t    (input your username please)     \n");
		printf("\n\t\t\t     "); scanf("%s", user);		i=0;
	
		while(i<5){
		if(strcmp(user, a[i].no_rekening)==0)	{no=i;	stat=1;	break;}		i++;
		}
		
		if(stat==0)	{
		system("cls");			
		printf("\t\t          CYBER BANK                  \n");
    	printf("\t\t ==============================       \n");
		printf("\t\t  Username tersebut tidak ada		  \n");	 Beep(1000,1000); Sleep(2000);  	goto awal;
		}
		
	bahasa:
		system("cls");
		puts("\t\t          CYBER BANK                  ");
    	puts("\t\t ==============================       ");
    	puts("\t\t    SILAHKAN PILIH BAHASA             ");
		puts("\t\t (Please select the language)       \n");
		puts("\t\t                          ENGLISH ---> 1\n");
		puts("\t\t                        INDONESIA ---> 2\n");
		puts("\t\t Tekan cancel(0) untuk batal          ");
		puts("\t\t  (Press cancel(0) to void)           ");
		B=getch();		if(B=='0') goto awal;	else if(B=='1')	eng();	else if(B=='2')	indonesia();	else	goto bahasa;
}

indonesia()
{
	salah:
		system("cls");	
		if(A==3){
			printf("\n\t\tAnda salah dalam memasukkan PIN hingga 3 kali\n\n\t\t\tKartu ATM anda telah diblokir"); Sleep(2000);  main();
		}
		puts("\t\t          CYBER BANK                  ");
    	puts("\t\t ==============================       ");
		puts("\t\t    masukkan nomor PIN anda			");
		printf("\n\t\t\t");	scanf("%s", pin);
		
		if(strcmp(pin, a[no].pin)!=0) {
			printf("\n\n\t\t       PIN salah\n"); Sleep(2000);	A++; goto salah;
		}	utama();
}

utama()
{
	utama1:	
		system("cls");
		puts("");
    	puts("\t\t          CYBER BANK                  ");
    	puts("\t\t==============================        ");
    	puts("\t\t          MENU UTAMA                  ");
    	puts("\t\t  (pecahan uang Rp 50.000)            ");
    	puts("\t\t    tekan(0)untuk batal               ");
    	puts("\n");
    	puts("1 <--- 100.000   \t\t\t 	500.000 ---> 2\n");
    	puts("3 <--- 300.000   \t\t\t      1.000.000 ---> 4\n");
    	puts("5 <--- Bayar/Beli\t\t\t      Menu lain ---> 6\n");
    	puts("7 <--- jumlah lain					  \n"); B=getch();
		switch(B)
			{case '0':main();	
			 case '1':tt=100000; break;	
	 		 case '2':tt=500000; break;
			 case '3':tt=300000; break; 
			 case '4':tt=1000000; break;	
			 case '5':bayar();
	 	   	 case '6':transaksi();	
			 case '7':penarikan();	
			 default: goto utama1;
			 }
			 
	 if(tarik_tunai(&tt)) { 	
	 printf("\n\t\tSaldo tidak mencukupi");	sleep(2); goto utama1; }
	 else {
	 	system("cls");	a[no].saldo_terakhir-=tt;	nasabah();	tx = time(NULL);	y=localtime(&tx);
		fr[0]=fopen("data_transaksi_2210161031.txt","a+");	
		fr[1]=fopen("data_transaksi_2210161045.txt","a+");	
		fr[2]=fopen("data_transaksi_2210161039.txt","a+");	
		fr[3]=fopen("data_transaksi_2210161055.txt","a+");
		fr[4]=fopen("data_transaksi_2210161032.txt","a+");	
		
		fprintf(fr[no], "%d/%d/%d,%2d:%2d:%2d,\"Tarik tunai Sebesar Rp %d\"\n", y->tgl, (y->bln)+1, (y->thn)+1900, y->jam, y->mnt, y->dtk, tt);	
		for(i=0; i<5; i++) fclose(fr[i]);	sleep(1);
		printf("\n\n\n\n\n\t\t  Penarikan Uang RP.%d\n\n\t\t    Sisa Saldo : %d\n", tt, a[no].saldo_terakhir);	sleep(2);	main();
	 }
}

bayar()
{
	bayar1:	system("cls");
		puts("\t\t          CYBER BANK                  ");
    	puts("\t\t==============================        ");
    	puts("\t\t          BAYAR/BELI                  ");
    	puts("\t\t  tekan(0)untuk ke menu utama         \n\n");
    	puts("1 <--- Voucher HP\t\t\t\tlistrik/gas---> 2\n\n");
    	puts("3 <--- internet");

	B=getch();	if(B=='0') utama();		else if(B=='1')	voucher();	else if(B=='2') listrik();	else if(B=='3')	tv();	else goto bayar1;
}

voucher()
{
	voucher1: system("cls");
		puts("\t\t          CYBER BANK                  ");
    	puts("\t\t==============================        ");
    	puts("\t\t	 BAYAR/BELI -- Voucher HP           ");
    	puts("\t\t  tekan(0)untuk ke menu utama         \n\n");
    	puts("1 <--- XL\t\t\t\t indonesiaOSAT ---> 2\n\n");
    	puts("3 <--- AXIS\t\t\t\t TELKOMSEL ---> 4");
		B=getch();		if(B=='0') utama();
		switch(B)	{case '1':strcpy(C,"XL"); break;	
					 case '2':strcpy(C,"indonesiaOSAT"); break;
					 case '3':strcpy(C,"AXIS"); break;		
					 case '4':strcpy(C,"TELKOMSEL");}	
		
		system("cls");
		puts("\t\t          CYBER BANK                  ");
    	puts("\t\t==============================        ");
    	puts("\t\t   		 VOUCHER 					");
 	    puts("\t\t  tekan(0)untuk ke menu utama         \n\n");
  		puts("1 <--- 25.000\t\t\t\t 50.000 ---> 2\n\n");
    	puts("3 <--- 75.000\t\t\t\t100.000 ---> 4");
    	
	chk:
		B=getch();	if(B=='0') utama();
		switch(B)	{case '1':b=25000; break;		
					 case '2':b=50000; break;
					 case '3':b=75000; break;		
					 case '4':b=100000; break;	default: goto chk;
					 }
					 
		if((a[no].saldo_terakhir-b)<0)	{
			printf("\n\t\t\tSaldo tidak mencukupi");	sleep(2);	goto voucher1;
		}
		
	nope:	
		system("cls");		
   		puts("\t\t          CYBER BANK                  ");
    	puts("\t\t==============================        \n");
   	 	puts("\t\t      Masukkan nomor Anda             ");
		printf("\n\t\t\t   ");		scanf("%s", &c);
		
	chk1: 
		puts("\n\t\t                        Benar ---> 1");
        puts("\n\t\t                        Salah ---> 2");
		B=getch();		if(B=='0') utama();		else if(B=='2') goto nope;	else if(B!='1')	goto chk1; system("cls");
	
	chk2:	
		puts("\t\t          CYBER BANK                  ");
    	puts("\t\t==============================        \n"); 
    	puts("\t\t     KONFIRMASI PEMBELIAN             ");
    	printf("\t\tVOUCHER       : %s\n",C);
    	printf("\t\tNILAI VOUCHER : %d\n",b);
    	printf("\t\tNOMOR PONSEL  : %s\n",c);
    	puts("                              Benar ---> 1");
    	puts("                              Salah ---> 2");
		
		B=getch();	if(B=='2') goto voucher1;	else if(B!='1')	goto chk2;	
		
		system("cls");	a[no].saldo_terakhir-=b;	nasabah();	tx = time(NULL);	y=localtime(&tx);
		fr[0]=fopen("data_transaksi_2210161031.txt","a+");	
		fr[1]=fopen("data_transaksi_2210161045.txt","a+");	
		fr[2]=fopen("data_transaksi_2210161039.txt","a+");	
		fr[3]=fopen("data_transaksi_2210161055.txt","a+");
		fr[4]=fopen("data_transaksi_2210161032.txt","a+");	
	
		fprintf(fr[no], "%d/%d/%d,%2d:%2d:%2d,\"Pembelian Voucher %s Sebesar %d ke nomor %s\"\n", y->tgl, (y->bln)+1, (y->thn)+1900, y->jam, y->mnt, y->dtk, C, b, c);	
		for(i=0; i<5; i++) fclose(fr[i]);	sleep(1);
		puts("\t\t          CYBER BANK                  ");
 		puts("\t\t==============================        \n\n");
    	puts("\t\t     TRANSAKSI BERHASIL               \n");
    	printf("\t\t Sisa Saldo Anda : Rp %d			\n",a[no].saldo_terakhir);
		puts("\t\tApakah anda ingin transaksi lainya?   \n\n");
    	puts("\t\t                         Menu utama ---> 1\n");
    	puts("\t\t                            Selesai ---> 2\n");
	
	chk3:	B=getch();	if(B=='2') main();	else if(B!='1')	goto chk3;	utama();
}

listrik()
{
	listrik: 
		system("cls");	
		puts("\t\t          CYBER BANK                  ");
    	puts("\t\t==============================        ");
    	puts("\t\t   BAYAR/BELI -- Voucher HP           ");
    	puts("\t\t  tekan(0)untuk ke menu utama         \n\n");
    	puts("1 <--- Listrik/PLN\t\t\t PLN non TANLIS ---> 2");
		B=getch();		if(B=='0') utama();		else if(B=='1')	strcpy(C,"Listrik/PLN");	else if(B=='2') strcpy(C,"PLN non TAGLIS");	else goto listrik;
	
	nope:
		system("cls");
		puts("\t\t          CYBER BANK                  ");
    	puts("\t\t==============================        ");
    	printf("\t\t		%s		\n\n\t\t\t",C) ; 
		printf("\t\t   Masukkan nomor anda				"); scanf("%s", &c);
    	puts("\t\t                          Benar ---> 1");
    	puts("\t\t                          Salah ---> 2");
    	puts("\t\t  tekan(0)untuk ke menu utama         ");
	
	chk:	B=getch();		if(B=='0') utama();		else if(B=='2') goto nope;	else if(B!='1')	goto chk; system("cls");
	
	jml:	
		system("cls");	
		puts("\t\t          CYBER BANK                  ");
    	puts("\t\t==============================        ");
    	printf("\t\t		%s		\n\n\t\t\t",C) ; 
		printf("\t\t Masukkan jumlah pembayaran	"); scanf("%d", &b);
    	puts("\t\t                          Benar ---> 1");
    	puts("\t\t                          Salah ---> 2");
    	puts("\t\t  tekan(0)untuk ke menu utama         ");

	chk1:
		B=getch();		if(B=='0') utama();	else if(B=='2') goto jml;	else if(B!='1')	goto chk1; 
		system("cls");
		if(b>a[no].saldo_terakhir)	{
			printf("\n\t\t\tSaldo tidak mencukupi");	sleep(2); goto jml;}
			
		puts("\t\t          CYBER BANK                  ");
    	puts("\t\t==============================        ");	
		sprintf("\n\t\t\tKonfirmasi Pembayaran\n\n\nID Pelanggan : %s\nNama\t     : %s\nJumlah\t     : %d\n\n\t\t\t\t\t\tBenar--->1\n\n\t\t\t\t\t\tSalah--->2"
		, c, a[no].nama_lengkap, b);
	
	chk2:
		B=getch();		if(B=='2') goto listrik;	else if(B!='1') goto chk2;	
		system("cls");	a[no].saldo_terakhir-=b;	nasabah();	tx = time(NULL);	y=localtime(&tx);
		fr[0]=fopen("data_transaksi_2210161031.txt","a+");	
		fr[1]=fopen("data_transaksi_2210161045.txt","a+");	
		fr[2]=fopen("data_transaksi_2210161039.txt","a+");	
		fr[3]=fopen("data_transaksi_2210161055.txt","a+");
		fr[4]=fopen("data_transaksi_2210161032.txt","a+");	
		fprintf(fr[no], "%d/%d/%d,%2d:%2d:%2d,\"Pembayaran tagihan listrik Sebesar %d dengan nomor rekening %s\"\n"
		, y->tgl, (y->bln)+1, (y->thn)+1900, y->jam, y->mnt, y->dtk, b, c);	
		for(i=0; i<5; i++) fclose(fr[i]);	sleep(1);
		puts("\t\t          CYBER BANK                  ");
 		puts("\t\t==============================        \n\n");
    	puts("\t\t     TRANSAKSI BERHASIL               \n");
    	printf("\t\t Sisa Saldo Anda : Rp %d			\n",a[no].saldo_terakhir);
		puts("\t\tApakah anda ingin transaksi lainya?   \n\n");
    	puts("\t\t                         Menu utama ---> 1\n");
    	puts("\t\t                            Selesai ---> 2\n");
	
	chk3:
		B=getch();		if(B=='2') main();	else if(B!='1')	goto chk3;	utama();
}

tv()
{
	tv:	
	system("cls");
	    puts("\t\t          CYBER BANK                  ");
    	puts("\t\t==============================        \n");
   	 	puts("\t\t      TV KABEL / INTERNET             ");
		puts("\t\t    Masukkan kode perusaan            ");
		printf("\n\t\t\t	  "); scanf("%s", &c);
		puts("\t\t                          Benar ---> 1");
    	puts("\t\t                          Salah ---> 2");
    	puts("\t\t                    Daftar kode ---> 3");
    	
	chk:
		B=getch();		if(B=='2') goto tv; else if(B=='3')	kode();	else if(B!='1') goto chk;
		if(strcmp(c, "50100")!=0&&strcmp(c, "50101")!=0&&strcmp(c, "50102")!=0)	{
			printf("\n\t\tKode tersebut tidak ada dalam daftar");	sleep(2);	goto tv;}
	
	nope:
		system("cls");	
		puts("\t\t          CYBER BANK                  ");
    	puts("\t\t==============================        \n");
   	 	puts("\t\t      TV KABEL / INTERNET             ");
		puts("\t\t   Masukkan nomor pelanggan");
		printf("\n\t\t\t	  "); scanf("%s", &C);
		puts("\t\t                          Benar ---> 1");
    	puts("\t\t                          Salah ---> 2");
    	puts("\t\t  tekan(0)untuk ke menu utama         ");
    	
	chk1:
		B=getch();		if(B=='0') utama();	else if(B=='2') goto nope;	else if(B!='1')	goto chk1;
	
	byr:
	
		system("cls");	
		system("cls");			
		puts("\t\t          CYBER BANK                  ");
    	puts("\t\t==============================        \n");
   	 	puts("\t\t      TV KABEL / INTERNET             ");
		puts("\t\t   Masukkan Jumlah Pembayaran			");
		printf("\n\t\t\t	  "); scanf("%d", &b);
		puts("\t\t                          Benar ---> 1");
    	puts("\t\t                          Salah ---> 2");
    	puts("\t\t  tekan(0)untuk ke menu utama         ");
	chk2:
		B=getch();		if(B=='0') utama();	else if(B=='2') goto tv;	else if(B!='1') goto chk2;	
		system("cls");
		if(b>a[no].saldo_terakhir)	{
		printf("\n\t\t\tSaldo tidak mencukupi");	sleep(2); goto byr;
		}
		puts("\t\t          CYBER BANK                  ");
    	puts("\t\t==============================        \n"); 
    	puts("\t\t     KONFIRMASI PEMBAYARAN           ");
    	printf("\t\tKODE            : %s\n",c);
    	printf("\t\tNOMOR PELANGGAN : %s\n",C);
    	printf("\t\tNAMA LENGKAP    : %s\n",a[no].nama_lengkap);
    	printf("\t\tJUMLAH		    : %d\n",b);
    	puts("                              Benar ---> 1");
    	puts("\t\t                          Salah ---> 2");
	
	chk3:
		B=getch();		
		if(B=='2') goto tv;	else if(B!='1') goto chk3;	system("cls");	a[no].saldo_terakhir-=b;	
		nasabah();	tx = time(NULL); y=localtime(&tx);
		fr[0]=fopen("data_transaksi_2210161031.txt","a+");	
		fr[1]=fopen("data_transaksi_2210161045.txt","a+");	
		fr[2]=fopen("data_transaksi_2210161039.txt","a+");	
		fr[3]=fopen("data_transaksi_2210161055.txt","a+");
		fr[4]=fopen("data_transaksi_2210161032.txt","a+");	
		fprintf(fr[no], "%d/%d/%d,%2d:%2d:%2d,\"Pembayaran tagihan tv kabel Sebesar %d ke nomor pelanggan %s\"\n"
		, y->tgl, (y->bln)+1, (y->thn)+1900, y->jam, y->mnt, y->dtk, b, C);	
		for(i=0; i<5; i++) fclose(fr[i]);	sleep(1);
		
		puts("\t\t          CYBER BANK                  ");
 		puts("\t\t==============================        \n\n");
    	puts("\t\t     TRANSAKSI BERHASIL               \n");
    	printf("\t\t Sisa Saldo Anda : Rp %d			\n",a[no].saldo_terakhir);
		puts("\t\tApakah anda ingin transaksi lainya?   \n\n");
    	puts("\t\t                         Menu utama ---> 1\n");
    	puts("\t\t                            Selesai ---> 2\n");
	chk4:
		B=getch();		if(B=='2') main();	else if(B!='1')	goto chk4;	utama();
}

kode()
{
		system("cls");	
		printf("\n\t\t\tDaftar Kode\n\n\n50100 - indonesiaOVISION/TOP/TREN/OKE\n\n50101 - FRISTMEDIA\n\n50102 - indonesiaOSATNET\n\n\t\t\t\t\t\tKembali--->1");
	chk1:	
		B=getch();	if(B=='1') tv();	else goto chk1;
}

transaksi()
{
		system("cls");	
		    puts("\t\t          CYBER BANK                  ");
    		puts("\t\t==============================        ");
  		    puts("\t\t          MENU LAIN                   ");
    		puts("\t\t  tekan(0)untuk ke menu utama         \n");
    		puts("1 <--- TRANSFER\t\t\t     UBAH PIN ---> 2");
   			puts("3 <--- CEK SALDO							");
    		puts("");
	chk:	
		B=getch();		if(B=='0') utama();	
						else if(B=='1')	transfer();	
						else if(B=='2')	ubah_pin();	
						else if(B=='3')	cek_saldo();	
						else goto chk;
}

transfer()
{
	tr:	
		stat=0;	
		system("cls");
		puts("\t\t          CYBER BANK                  ");
   		puts("\t\t==============================        ");
  	    puts("\t\t           TRANSFER                   ");
   		puts("\t\t  tekan(0)untuk ke menu utama         \n");
		puts("1 <--- BANK CYBER\t\t      BANK LAIN ---> 2");
	chk:
		B=getch();		if(B=='0') utama();	else if(B=='1') strcpy(C,"Mandiri");	else if(B=='2') strcpy(C,"lain");	else goto chk;
	rkg:
		system("cls");
	    puts("\t\t          CYBER BANK                  ");
    	puts("\t\t==============================        ");
  		puts("\t\tMasukkan Nomor Rekening Tujuan        ");
	    printf("\t\t\t    ");scanf("%s",&c);
    	puts("\t\t                          Benar ---> 1");
    	puts("\t\t                          Salah ---> 2\n");
    	puts("\t\t  tekan(0)untuk ke menu utama         ");
	chk1:
		B=getch();		if(B=='0') utama();	else if(B=='2') goto rkg;	else if(B!='1')	goto chk1;
		
		for(i=0; i<5; i++)	
		if(strcmp(c, a[i].no_rekening)==0)	{tu=i;	stat=1;	break;}
		if(stat==0)	
			{system("cls");	
			puts("\t\t          CYBER BANK                  ");
    		puts("\t\t==============================        ");
  			puts("\t\t REKENING TERSEBUT TIDAK ADA  	    ");	sleep(2);	goto rkg;}
		
		else if (strcmp(a[no].no_rekening, a[tu].no_rekening)==0)
			{system("cls");	
			puts("\t\t          CYBER BANK                  ");
    		puts("\t\t==============================        ");
  			puts("\t\t TIDAK BISA TRANFER KE REKENING	    ");
			puts("\t\t 			 SENDIRI					");	sleep(2);	goto rkg;}

	jml:
		system("cls");	
	    puts("\t\t          CYBER BANK                  ");
    	puts("\t\t==============================        ");
  		puts("\t\t    Masukkan Jumlah Nominal           ");
	    printf("\t\t\t    ");scanf("%d",&b);
    	puts("\t\t                          Benar ---> 1");
    	puts("\t\t                          Salah ---> 2\n");
    	puts("\t\t  tekan(0)untuk ke menu utama         ");
		
	chk2:
		B=getch();		if(B=='0') utama();	else if(B=='2') goto jml;	else if(B!='1') goto chk2;	
		system("cls");
		if(b>a[no].saldo_terakhir)	{
			printf("\n\t\t\tSaldo tidak mencukupi");	sleep(2); goto jml;
			}
		
		puts("\t\t          CYBER BANK                  ");
    	puts("\t\t==============================        \n"); 
    	puts("\t\t     KONFIRMASI PEMBAYARAN           ");
    	printf("\t\tREKENING TUJUAN : %s\n",c);
    	printf("\t\tNAMA LENGKAP    : %s\n",a[tu].nama_lengkap);
    	printf("\t\tJUMLAH          : %d\n",b);
    	printf("\t\tREKENING ASAL   : %s\n",a[no].no_rekening);
    	printf("\t\NAMA LENGKAP		: %s\n\n",a[no].nama_lengkap);
    	puts("\t\t                          Benar ---> 1");
    	puts("\t\t                          Salah ---> 2");
		
	chk3:
		B=getch();		if(B=='2') goto tr;	else if(B!='1') goto chk3;	
		system("cls");	a[no].saldo_terakhir-=b;	a[tu].saldo_terakhir+=b;	nasabah();	tx = time(NULL);	y=localtime(&tx);
		fr[0]=fopen("data_transaksi_2210161031.txt","a+");	
		fr[1]=fopen("data_transaksi_2210161045.txt","a+");	
		fr[2]=fopen("data_transaksi_2210161039.txt","a+");	
		fr[3]=fopen("data_transaksi_2210161055.txt","a+");
		fr[4]=fopen("data_transaksi_2210161032.txt","a+");	
		
		fprintf(fr[no], "%d/%d/%d,%2d:%2d:%2d,\"Transfer ke rekening %s Sebesar %d\"\n"
		, y->tgl, (y->bln)+1, (y->thn)+1900, y->jam, y->mnt, y->dtk, a[tu].no_rekening, b);
		fprintf(fr[tu], "%d/%d/%d,%2d:%2d:%2d,\"Mendapat transfer dari rekening %s Sebesar %d\"\n"
		, y->tgl, (y->bln)+1, (y->thn)+1900, y->jam, y->mnt, y->dtk, a[no].no_rekening, b);	
		for(i=0; i<5; i++) fclose(fr[i]);	sleep(1);
	
		puts("\t\t          CYBER BANK                  ");
 		puts("\t\t==============================        \n\n");
    	puts("\t\t     TRANSAKSI BERHASIL               \n");
    	printf("\t\t Sisa Saldo Anda : Rp %d			\n",a[no].saldo_terakhir);
		puts("\t\tApakah anda ingin transaksi lainya?   \n\n");
    	puts("\t\t                         Menu utama ---> 1\n");
    	puts("\t\t                            Selesai ---> 2\n");
	
	chk4:
		B=getch();		if(B=='2') main();	else if(B!='1')	goto chk4;	utama();
}

ubah_pin()
{
	chp:
		system("cls");	
		puts("\t\t          CYBER BANK                  ");
 		puts("\t\t==============================        \n\n");
    	puts("\t\t           UBAH PIN                   \n");
    	puts("\t\t   MASUKKAN PIN LAMA ANDA				");
		printf("\n\t\t\t	  ");	scanf("%s", &pin);	
		
		if(strcmp(pin, a[no].pin)==0){
	
	new:
		system("cls");	
		puts("\t\t          CYBER BANK                  ");
 		puts("\t\t==============================        \n\n");
    	puts("\t\t           UBAH PIN                   \n");
    	puts("\t\t   MASUKKAN PIN BARU ANDA				");
		printf("\n\t\t\t	  ");	scanf("%s", &c);
		
		system("cls");	
		puts("\t\t          CYBER BANK                  ");
 		puts("\t\t==============================        \n\n");
    	puts("\t\t           UBAH PIN                   \n");
    	puts("\t\t    MASUKKAN PIN ANDA LAGI			");
		printf("\n\t\t\t	  ");	scanf("%s", &np);
		
		if(strcmp(c,np)==0){
			strcpy(a[no].pin,np);	nasabah();	tx = time(NULL);	y=localtime(&tx);
				fr[0]=fopen("data_transaksi_2210161031.txt","a+");	
				fr[1]=fopen("data_transaksi_2210161045.txt","a+");	
				fr[2]=fopen("data_transaksi_2210161039.txt","a+");	
				fr[3]=fopen("data_transaksi_2210161055.txt","a+");
				fr[4]=fopen("data_transaksi_2210161032.txt","a+");
				
				printf(fr[no], "%d/%d/%d,%2d:%2d:%2d,\"Ubah pin dari %s menjadi %s\"\n", y->tgl, (y->bln)+1, (y->thn)+1900, y->jam, y->mnt, y->dtk, pin, a[no].pin);	
				for(i=0; i<5; i++) fclose(fr[i]);	sleep(1);
		
		system("cls");	
		puts("\t\t          CYBER BANK                  ");
 		puts("\t\t==============================        \n\n");
    	puts("\t\t   PIN ANDA TELAH DIUBAH              \n");	sleep(2); main();
		}
		
		puts("\t\t          CYBER BANK                  ");
 		puts("\t\t==============================        \n\n");
    	puts("\t\t        PIN TIDAK SAMA                \n");	sleep(1);	goto new;
		}
		puts("\t\t          CYBER BANK                  ");
 		puts("\t\t==============================        \n\n");
    	puts("\t\t        PIN ANDA SALAH                \n");	sleep(2);	goto chp;
}

cek_saldo()
{
		puts("\t\t          CYBER BANK                  ");
   		puts("\t\t==============================        \n");
    	printf("\t\t NO. REKENING	: %s				\n",a[no].no_rekening);
    	printf("\t\t NAMA LENGKAP	: %s				\n\n",a[no].nama_lengkap);
    	puts("\t\t     SALDO REKENING ANDA              ");
    	printf("\t\t       %d\n\n",a[no].saldo_terakhir);
    	puts("\t\t TRANSAKSI ANDA TELAH SELESAI         ");
    	puts("\t\t APAKAH ANDA INGIN MELAKUKAN          ");
    	puts("\t\t     TRANSAKSI LAINNYA?               \n");
    	puts("\t\t                            YA ---> 1 \n");
    	puts("\t\t                         TIDAK ---> 2 ");
	
	chk:
		B=getch();		if(B=='2') main();	else if(B!='1')	goto chk;	utama();
}

penarikan()
{
	lain:
		system("cls");
		puts("\t\t          CYBER BANK                  ");
   	 	puts("\t\t==============================        ");
    	puts("\t\t    PENARIKAN JUMLAH LAIN             ");
    	puts("\t\t  tekan(0)untuk ke menu utama          \n\n");
    	puts("\t\t                 Masukkan jumlah penarikan");
    	puts("\t\t                  dengan kelipatan nominal");
    	puts("\t\t                                 Rp 50.000");	
		printf("\n\t\t\t\t "); scanf("%d", &b);
		puts("\t\t                              Benar ---> 1");
    	puts("\t\t                    	        Salah ---> 2");
    	
	chk:
		B=getch();		if(B=='0') utama();	else if(B=='2')	goto lain;	else if(B!='1')	goto chk;	
	
	if((b%50000)!=0)	{
		printf("\n\t\t  Jumlah penarikan harus kelipatan Rp 50.000");	sleep(2);	goto lain;}
	if(b>a[no].saldo_terakhir)	{
		printf("\n\t\t\tSaldo tidak mencukupi");	sleep(2); goto lain;}	a[no].saldo_terakhir-=b;	nasabah();	tx = time(NULL);	y=localtime(&tx);
		
	fr[0]=fopen("data_transaksi_2210161031.txt","a+");	
	fr[1]=fopen("data_transaksi_2210161045.txt","a+");	
	fr[2]=fopen("data_transaksi_2210161039.txt","a+");	
	fr[3]=fopen("data_transaksi_2210161055.txt","a+");
	fr[4]=fopen("data_transaksi_2210161032.txt","a+");	
	
	fprintf(fr[no], "%d/%d/%d,%2d:%2d:%2d,\"Tarik tunai Sebesar Rp %d\"\n", y->tgl, (y->bln)+1, (y->thn)+1900, y->jam, y->mnt, y->dtk, b);	
	for(i=0; i<5; i++) fclose(fr[i]);	sleep(1);
	printf("\n\n\n\n\n\t\t  Penarikan Uang RP.%d\n\n\t\t    Sisa Saldo : %d\n", b, a[no].saldo_terakhir);	sleep(2);	main();
}

//BAHASA INGGRIS NYA MASIH BERANTAKAN
eng()
{
	SALAH:	system("cls");	if(A==3){printf("\t\tYou've entered wrong PIN 3 times\n\n\t\t  Your ATM card had been blocked");	sleep(2);  main();}
		printf("\t\tPlease insert your PIN number\n\n\t\t\t   ");	scanf("%s", &pin);
		if(strcmp(pin,a[no].pin)!=0) {printf("\n\t\t\t       Wrong PIN\n"); A++;	sleep(2); goto SALAH;}	first();
}
first()
{
	utama1:	system("cls");
	printf("\n\t\t\tMain menu\n\t\t (Multiple of RP.50.000)\n\t\t Press cancel(0) to void\n\n1<---100.000\t\t\t\t500.000--->2\n\n3<---300.000\t\t\t\t1.000.000--->4\n\n");
			printf("5<---Pay/Buy\t\t\t   Other transaction--->6\n\n7<---Other Withdraw");		B=getch();
	switch(B)
	{case '0':main();	case '1':tt=100000; break;	case '3':tt=300000; break;
	 case '2':tt=500000; break; case '4':tt=1000000; break;	case '5': pay();
	 case '6':transaction();	case '7':withdraw();	default: goto utama1;}
	 if(tarik_tunai(&tt))
	 { 	printf("\n\t\t\tInsufficient funds");	sleep(2);	goto utama1;	 }
	 else
	 {
	 	a[no].saldo_terakhir-=tt;	nasabah();	tx = time(NULL);	y=localtime(&tx);
	 	fr[0]=fopen("data_transaksi_2210161031.txt","a+");	fr[1]=fopen("data_transaksi_2210161045.txt","a+");	fr[2]=fopen("data_transaksi_2210161039.txt","a+");	
		 fr[3]=fopen("data_transaksi_2210161055.txt","a+");
		fr[4]=fopen("data_transaksi_2210161032.txt","a+");	fprintf(fr[no], "%d/%d/%d,%2d:%2d:%2d,\"Tarik tunai Sebesar Rp %d\"\n"
		, y->tgl, (y->bln)+1, (y->thn)+1900, y->jam, y->mnt, y->dtk, tt);	
		for(i=0; i<5; i++) fclose(fr[i]);	sleep(1);
		system("cls");	printf("\n\n\n\n\n\t\t   Withdraw RP.%d\n\n\t\tRemaining funds : %d", tt, a[no].saldo_terakhir);	sleep(2);		main();}
}
pay()
{
	bayar1:	system("cls");
	printf("\n\t\t\t\tPay/Buy\n\t\t     Press cancel(0) to main menu\n\n\n1<---Phone's Voucher\t\t\t\tElectricity/Gas--->2\n\n3<---Cable TV / \n     Internet");
	B=getch();		if(B=='0') first();		else if(B=='1')	Voucher();	else if(B=='2') Electric();	else if(B=='3')	Tv();	else goto bayar1;
}
Voucher()
{
	voucher1:system("cls");
		printf("\n\t\t\t\tPhone's Voucher\n\t\t     Press cancel(0) to main menu\n\n\n1<---XL\t\t\t\t\tindosat--->2\n\n3<---3 \t\t\t\t\tSimpati--->4\n");
		B=getch();		if(B=='0') first();
		switch(B)	{case '1':strcpy(C,"XL"); break;	case '2':strcpy(C,"indonesiaosat"); break;
					 case '3':strcpy(C,"3"); break;		case '4':strcpy(C,"Simpati");}	system("cls");
	printf("\n\t\t\t  Choose the value\n\t\t     Press cancel(0) to main menu\n\n\n1<---25.000\t\t\t\t 50.000--->2\n\n3<---75.000\t\t\t\t100.000--->4\n");
	ulang:	B=getch();		if(B=='0') first();
		switch(B)	{case '1':b=25000; break;		case '2':b=50000; break;
					 case '3':b=75000; break;		case '4':b=100000; break;	default:goto ulang;}
	if((a[no].saldo_terakhir-b)<0)	{printf("\n\t\t\tInsufficient funds");	sleep(2);	goto voucher1;}
	nope:		system("cls");		printf("\n\t\t\tType your phone number\n\n\n\t\t\t   ");		scanf("%s", &c);
	ulang1: printf("\n\n\t\t\tIs this correct\n\t\t\t\t\t\tYes--->1\n\n\t\t\t\t\t\t No--->2\n\n\t\t     Press cancel(0) to main menu");
		B=getch();		if(B=='0') first();		else if(B=='2') goto nope;	else if(B!='1')	goto ulang1; system("cls");
	ulang2:	
	printf("\t\t\tPayment's confirmation\n\nOperator\t: %s\nValue\t\t: %d\nPhone number\t: %s\n\n\n\t\t\tIs this correct\n\n\t\t\t\t\t\tYes--->1\n\n\t\t\t\t\t\t No--->2", C, b, c);
		B=getch();		if(B=='2') goto voucher1;	else if(B!='1')	goto ulang2;	system("cls");	a[no].saldo_terakhir-=b;	nasabah();	tx = time(NULL);	y=localtime(&tx);
	fr[0]=fopen("data_transaksi_2210161031.txt","a+");	fr[1]=fopen("data_transaksi_2210161045.txt","a+");	fr[2]=fopen("data_transaksi_2210161039.txt","a+");
		fr[3]=fopen("data_transaksi_2210161055.txt","a+");
	fr[4]=fopen("data_transaksi_2210161032.txt","a+");	fprintf(fr[no], "%d/%d/%d,%2d:%2d:%2d,\"Pembelian Voucher %s Sebesar %d ke nomor %s\"\n"
	, y->tgl, (y->bln)+1, (y->thn)+1900, y->jam, y->mnt, y->dtk, C, b, c);	
	for(i=0; i<5; i++) fclose(fr[i]);	sleep(1);
	printf("\n\t\t\tTransaction success\n\n\t\tRemaining Balance : %d\n\n\n\t\t\t\t\t   Main menu--->1\n\n\t\t\t\t\t      Finish--->2", a[no].saldo_terakhir);
	ulang3:	B=getch();		if(B=='2') main();	else if(B!='1')	goto ulang3;	first();
}
Electric()
{
	listrik: system("cls");	printf("\n\t\t\t\tElectricity/Gas\n\t\t     Press cancel(0) to main menu\n\n\n1<---Electricity/PLN\t\t\t\t Non bill PLN--->2\n\t\t\t\t");
		B=getch();		if(B=='0') first();		else if(B=='1')	strcpy(C,"Electricity/PLN");	else if(B=='2') strcpy(C," Non-bill PLN");	else goto listrik;
	nope:system("cls");	printf("\n\t\t\t    %s\n\n\t\t     Type your PLN's customer id\n\n\n\t\t\t   ", C);		scanf("%s", &c);
		printf("\n\n\t\t\tIs this correct\n\n\t\t\t\t\t\tYes--->1\n\n\t\t\t\t\t\t No--->2\n\n\t\t     Press cancel(0) to main menu");
	ulang:B=getch();		if(B=='0') first();		else if(B=='2') goto nope;	else if(B!='1')	goto ulang; system("cls");
	jml:system("cls");	printf("\n\t\t\t\t%s\n\n\n\t\t     Type the value\n\n\n\t\t\t   ", C);		scanf("%d", &b);
		printf("\n\n\t\t\tIs this correct\n\n\t\t\t\t\t\tYes--->1\n\n\t\t\t\t\t\t No--->2\n\n\t\t     Press cancel(0) to main menu");
	ulang1:B=getch();		if(B=='0') first();	else if(B=='2') goto jml;	else if(B!='1')	goto ulang1; system("cls");
		if(b>a[no].saldo_terakhir)	{printf("\n\t\t\tInsufficient funds");	sleep(2); goto jml;}
		printf("\n\t\t\tPayment's confirmation\n\nCustomer's ID : %s\nName\t      : %s\nValue\t     : %d\n\n\n\t\t\tIs this correct\n\n\t\t\t\t\t\tYes--->1\n\n\t\t\t\t\t\t No--->2\n"
		, c, a[no].nama_lengkap, b);
	ulang2:B=getch();		if(B=='2') goto listrik;	else if(B!='1') goto ulang2;	system("cls");	a[no].saldo_terakhir-=b;	nasabah();	tx = time(NULL);	y=localtime(&tx);
	fr[0]=fopen("data_transaksi_2210161031.txt","a+");	fr[1]=fopen("data_transaksi_2210161045.txt","a+");	fr[2]=fopen("data_transaksi_2210161039.txt","a+");	
	fr[3]=fopen("data_transaksi_2210161055.txt","a+");
	fr[4]=fopen("data_transaksi_2210161032.txt","a+");	fprintf(fr[no], "%d/%d/%d,%2d:%2d:%2d,\"Pembayaran tagihan listrik Sebesar %d dengan nomor rekening %s\"\n"
	, y->tgl, (y->bln)+1, (y->thn)+1900, y->jam, y->mnt, y->dtk, b, c);
	for(i=0; i<5; i++) fclose(fr[i]);	sleep(1);
	printf("\n\t\t\tTransaction success\n\n\t\tRemaining Balance : %d\n\n\n\t\t\t\t\t   Main menu--->1\n\n\t\t\t\t\t      Finish--->2", a[no].saldo_terakhir);
	ulang3:	B=getch();		if(B=='2') main();	else if(B!='1')	goto ulang3;	first();
}
Tv()
{
	tv:	system("cls");	printf("\n\t\t\tCable TV / Internet\n\n\t\t     Type company's / \n\t\t     Institution code\n\n\t\t\t   ");	scanf("%s", &c);
		printf("\n\n\t\t\tIs this correct\n\n\t\t\t\t\t\tYes--->1\n\n\t\t\t\t\t\t No--->2\n\n\t\t\t\t\t  Code list--->3");
	ulang:B=getch();		if(B=='2') goto tv; else if(B=='3')	Kode();	else if(B!='1') goto ulang;
		if(strcmp(c, "50100")!=0&&strcmp(c, "50101")!=0&&strcmp(c, "50102")!=0)	{printf("\n\t\tThat institution code isn't listed");	sleep(2);	goto tv;}
	nope:system("cls");	printf("\n\t\tType your customer ID\n\n\t\t\t");	scanf("%s", &C);
		printf("\n\n\t\t\tIs this correct\n\t\t\t\t\t\tYes--->1\n\n\t\t\t\t\t\t No--->2\n\n\t\t     Press cancel(0) to main menu");
	ulang1:B=getch();		if(B=='0') first();	else if(B=='2') goto nope;	else if(B!='1')	goto ulang1;
	byr:system("cls");		printf("\n\t\t\tType the payment's value\n\n\t\t\t   ");	scanf("%d", &b);
		printf("\n\n\t\t\tIs this correct\n\t\t\t\t\t\tYes--->1\n\n\t\t\t\t\t\t No--->2\n\n\t\t     Press cancel(0) to main menu");
	ulang2:B=getch();		if(B=='0') first();	else if(B=='2') goto tv;	else if(B!='1') goto ulang2;	system("cls");
		if(b>a[no].saldo_terakhir)	{printf("\n\t\t\tInsufficient funds");	sleep(2); goto byr;}
	printf("\n\t\t\tPayment's confirmation\n\nCode\t\t: %s\nCustomer ID: %s\nName\t\t: %s\nValue\t\t : %d\n\n\t\t\t\t\t\tIs this correct\n\n\t\t\t\t\t\tYes--->1\n\n\t\t\t\t\t\t No--->2"
		, c, a[no].nama_lengkap, C, b);
	ulang3:B=getch();		if(B=='2') goto tv;	else if(B!='1') goto ulang3;	system("cls");	a[no].saldo_terakhir-=b;	nasabah();	tx = time(NULL);	y=localtime(&tx);
		fr[0]=fopen("data_transaksi_2210161031.txt","a+");	fr[1]=fopen("data_transaksi_2210161045.txt","a+");	fr[2]=fopen("data_transaksi_2210161039.txt","a+");	
		fr[3]=fopen("data_transaksi_2210161055.txt","a+");
		fr[4]=fopen("data_transaksi_2210161032.txt","a+");	fprintf(fr[no], "%d/%d/%d,%2d:%2d:%2d,\"Pembayaran tagihan tv kabel Sebesar %d ke nomor pelanggan %s\"\n"
		, y->tgl, (y->bln)+1, (y->thn)+1900, y->jam, y->mnt, y->dtk, b, C);	
		for(i=0; i<5; i++) fclose(fr[i]);	sleep(1);
		printf("\n\t\t\tTransaction success\n\n\t\tRemaining Balance : %d\n\n\n\t\t\t\t\t   Main menu--->1\n\n\t\t\t\t\t      Finish--->2", a[no].saldo_terakhir);
	ulang4:	B=getch();		if(B=='2') main();	else if(B!='1')	goto ulang4;	first();
}
Kode()
{
	system("cls");	printf("\n\t\t\tCode list\n\n\n50100 - indonesiaOVISION/TOP/TREN/OKE\n\n50101 - FRISTMEDIA\n\n50102 - INDOSATNET\n\n\t\t\t\t\t\tBack--->1");
	ulang1:	B=getch();	if(B=='1') tv();	else goto ulang1;
}
transaction()
{
	system("cls");	printf("\n\t\t\tOther main menu\n\t\t     Press cancel(0) to main menu\n\n\n1<---Transfer\t\t\t\t\tchange PIN--->2\n");
	ulang:	B=getch();		if(B=='0') utama();	else if(B=='1')	Transfer();	else if(B=='2')	Change_pin();	else if(B=='3')	Check();	else goto ulang;
}
Transfer()
{
	tr:	stat=0;	system("cls");printf("\n\t\t\t\tTransfer\n\t\t     Press cancel(0) to main menu\n\n\n1<---To Mandiri's\t\t\t     To other --->2\n     account\t\t\t\t   Bank's account\n");
	ulang:B=getch();		if(B=='0') utama();	else if(B=='1') strcpy(C,"Mandiri");	else if(B=='2') strcpy(C,"other bank");	else goto ulang;
	rkg:system("cls");	printf("\n\t\t\tTransfer to %s\n\n\t\t  Type the transfers destination number\n\n\t\t\t", C);		scanf("%s", &c);
		printf("\n\n\t\t\tIs this correct\n\t\t\t\t\t\tYes--->1\n\n\t\t\t\t\t\t No--->2\n\n\t\t     Press cancel(0) to main menu");
	ulang1:B=getch();		if(B=='0') utama();	else if(B=='2') goto rkg;	else if(B!='1')	goto ulang1;
	for(i=0; i<5; i++)	if(strcmp(c, a[i].no_rekening)==0)	{tu=i;	stat=1;	break;}
		if(stat==0)	{system("cls");	printf("\n\n\t\tThat bank account isn't listed");	sleep(2);	goto rkg;}
		else if (strcmp(a[no].no_rekening, a[tu].no_rekening)==0)	{system("cls");	printf("\n\n\n\t\t    Cannot transfer to your own account");	sleep(2);	goto rkg;}
	jml:system("cls");	printf("\n\t\t\t  Type the value\n\n\n\t\t\t     ");	scanf("%d", &b);
		printf("\n\n\t\t\tIs this correct\n\t\t\t\t\t\tYes--->1\n\n\t\t\t\t\t\t No--->2\n\n\t\t     Press cancel(0) to main menu");
	ulang2:B=getch();		if(B=='0') utama();	else if(B=='2') goto jml;	else if(B!='1') goto ulang2;	system("cls");
		if(b>a[no].saldo_terakhir)	{printf("\n\t\t\tInsufficient funds");	sleep(2); goto jml;}
		printf("Transfer's confirmation\n\n\nDestination : %s\nName\t: %s\nValue\t: %d\n\nFrom\t: %s\nName\t: %s\n\n\nIs this correct\n\n\t\t\tYes--->1\n\n\t\t\t\ No--->2\n"
		, c, a[tu].nama_lengkap, b, a[no].no_rekening, a[no].nama_lengkap);
	ulang3:B=getch();		if(B=='2') goto tr;	else if(B!='1') goto ulang3;	
	system("cls");	a[no].saldo_terakhir-=b;	a[tu].saldo_terakhir+=b;	nasabah();	tx = time(NULL);	y=localtime(&tx);
		fr[0]=fopen("data_transaksi_2210161031.txt","a+");	fr[1]=fopen("data_transaksi_2210161045.txt","a+");	fr[2]=fopen("data_transaksi_2210161039.txt","a+");	
		fr[3]=fopen("data_transaksi_2210161055.txt","a+");
	fr[4]=fopen("data_transaksi_2210161032.txt","a+");	fprintf(fr[no], "%d/%d/%d,%2d:%2d:%2d,\"Transfer ke rekening %s Sebesar %d\"\n"
	, y->tgl, (y->bln)+1, (y->thn)+1900, y->jam, y->mnt, y->dtk, a[tu].no_rekening, b);
	fprintf(fr[no], "%d/%d/%d,%2d:%2d:%2d,\"Mendapat transfer dari rekening %s Sebesar %d\"\n"
	, y->tgl, (y->bln)+1, (y->thn)+1900, y->jam, y->mnt, y->dtk, a[no].no_rekening, b);	for(i=0; i<5; i++) fclose(fr[i]);	sleep(1);
		for(i=0; i<5; i++) fclose(fr[tu]);	sleep(1);	
		printf("\n\t\t\tTransaction success\n\n\t\tRemaining Balance : %d\n\n\n\t\t\t\t\t   Main menu--->1\n\n\t\t\t\t\t      Finish--->2", a[no].saldo_terakhir);
	ulang4:B=getch();		if(B=='2') main();	else if(B!='1')	goto ulang4;	utama();
}
Change_pin()
{
	chp:system("cls");	printf("\n\t\t\t\tChange PIN\n\n\t\t\t    Type your old PIN\n\n\t\t\t\t");	scanf("%s", &pin);	if(strcmp(pin, a[no].pin)==0){
	new:system("cls");	printf("\n\t\t\t\tChange PIN\n\n\t\t\t    Type your new PIN\n\n\t\t\t\t  ");	scanf("%s", &c);
		system("cls");	printf("\t\t\t\tChange PIN\n\n\t\t      Type your new PIN once more\n\n\t\t\t\t  ");	scanf("%s", &np);
		if(strcmp(c,np)==0){strcpy(a[no].pin,np);	nasabah();	tx = time(NULL);	y=localtime(&tx);
		fr[0]=fopen("data_transaksi_2210161031.txt","a+");	fr[1]=fopen("data_transaksi_2210161045.txt","a+");	fr[2]=fopen("data_transaksi_2210161039.txt","a+");
			fr[3]=fopen("data_transaksi_2210161055.txt","a+");
		fr[4]=fopen("data_transaksi_2210161032.txt","a+");	fprintf(fr[no], "%d/%d/%d,%2d:%2d:%2d,\"Ubah pin dari %s menjadi %s\"\n"
		, y->tgl, (y->bln)+1, (y->thn)+1900, y->jam, y->mnt, y->dtk, pin, a[no].pin);	
		
		for(i=0; i<5; i++) fclose(fr[i]);	sleep(1);
		system("cls");	printf("\n\n\t\t\t\t\tPIN changed\n\n");	sleep(2); main();}
		system("cls");	printf("\n\t\t\t\tChange PIN\n\n\t\t\t    PIN didn't match\n"); sleep(1);	goto new;}
		system("cls");	printf("\n\n\n\t\t\t\tWrong PIN");	sleep(2);	goto chp;
}
Check()
{
	system("cls");	printf("\n\nAccount number  : %s\nName            : %s\nRemaining funds : %d\n\n\t\t\t\t\t   Main menu--->1\n\n\t\t\t\t\t      Finish--->2"
	, a[no].no_rekening, a[no].nama_lengkap, a[no].saldo_terakhir);
ulang:B=getch();		if(B=='2') main();	else if(B!='1')	goto ulang;	utama();
}
withdraw()
{
	lain:system("cls");	printf("\n\t\t\t    Other withdraw\n\t\t     (Multiple of Rp 50.000)\n\n\t\t\tType withdraw's value\n\n\t\t\t\t");
		scanf("%d", &b);	printf("\n\n\t\t\tIs this correct\n\t\t\t\t\t\tYes--->1\n\n\t\t\t\t\t\t No--->2\n\n\t\t     Press cancel(0) to main menu");
	ulang:B=getch();		if(B=='0') utama();	else if(B=='2')	goto lain;	else if(B!='1')	goto ulang;	system("cls");
	if((b%50000)!=0)	{printf("\n\n\t\t  Value must be multiple of Rp 50.000");	sleep(2);	goto lain;}
	if(b>a[no].saldo_terakhir)	{printf("\n\t\t\tInsufficient funds");	
	sleep(2); goto lain;}	a[no].saldo_terakhir-=b;	nasabah();	tx = time(NULL);	y=localtime(&tx);
	fr[0]=fopen("data_transaksi_2210161031.txt","a+");	fr[1]=fopen("data_transaksi_2210161045.txt","a+");	fr[2]=fopen("data_transaksi_2210161039.txt","a+");	
	fr[3]=fopen("data_transaksi_2210161055.txt","a+");
	fr[4]=fopen("data_transaksi_2210161032.txt","a+");	fprintf(fr[no], "%d/%d/%d,%2d:%2d:%2d,\"Tarik tunai Sebesar Rp %d\"\n"
	, y->tgl, (y->bln)+1, (y->thn)+1900, y->jam, y->mnt, y->dtk, b);	for(i=0; i<5; i++) fclose(fr[i]);	Sleep(1000);
	printf("\n\n\n\n\n\t\t   Withdraw RP.%d\n\n\t\tRemaining funds : %d", b, a[no].saldo_terakhir);	sleep(2);	main();
}
nasabah()
{
	fbuka=fopen("Nasabah.txt","w+");	for(i=0; i<5; i++)	{fprintf(fbuka, "%s,%s,%s,%d\n", a[i].no_rekening, a[i].nama_lengkap, a[i].pin, a[i].saldo_terakhir);	}	fclose(fbuka);
}

int tarik_tunai(int *x)
{
	if(a[no].saldo_terakhir<*x)	return(1);
	else return(0);
}


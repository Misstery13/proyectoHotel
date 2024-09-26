#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<string.h> 
#include<time.h>
#include<ctime>
#include<windows.h>
using namespace std;
void gotoxy(int x, int y){ 
    HANDLE hcon;  
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;  
	dwPos.X = x;  //columna
	dwPos.Y= y;  //fila
	SetConsoleCursorPosition(hcon,dwPos);  
 }
 
struct Habitacion{
	int tipodeHabitacion;
	int vistaalmar;
	string codigo;
	int cantHab;
	string descripcion;
	float precio_base;
	float tasa;
	
	float iva;
	int estado;
	
	Habitacion *sgte;
	Habitacion *ant;
};

struct Persona{
	string cedula;
	string nombre;
	string apellido;
	string email; 
	string direccion;
	string telefono;
	int dia1,dia2,mes1,mes2,anio1,anio2,hora,min;

	int band;
	string numero_de_la_habitacion;
	
	Persona *sgte;
	Persona *ant;
};

struct 	Bar{
	int cant;
	string codigo;
	string descripcion;
	float precio;
	float iva;
	Bar *sgte;
	Bar *ant;
};

struct DetalleHab{
	
	string descripcion;
	
	string codigoProduct;
	float precio;
	int cantidad;
	float subtotal;
	float iva;
	
	DetalleHab *sgte;
	DetalleHab *ant;
};

struct CabFactura{
	string codfact;
	int dia;
	int mes;
	int anio;
	
	string cedula;
	string codHab;
	
	float subtotal_fact;
	float valorIva_fact;
	float total_fact;
	
	DetalleHab *pcabDetalleHab;
	DetalleHab *pfinDetalleHab;
	
	int x,y;
	CabFactura *sgte;
	CabFactura *ant;	
};


int menu();
int menuhab();
int menuReserva();
int menu_hab_bar();
int menuBar();
void logo1();
void operaciones(int op,int dia, int mes,int x,int y,int anio, int hora, int min,Persona *&pcabPer,Persona *&pfinPer,CabFactura *&pcabFactu,CabFactura *&pfinFactu,Bar *&pcabBar,Bar	*&pfinBar,Bar *&pcabReg,Bar *&pfinReg,Habitacion *&pcabHab, Habitacion *&pfinHab);

void Registro_Habitaciones(Habitacion *&pcabHab, Habitacion *&pfinHab );

Habitacion *fun_buscarHabitacion(string codigo,Habitacion *pcabHab);
Habitacion *fun_buscarHabitacion_por_tipo(string codigo,Habitacion *pcabHab,int respuesta);

void EliminarHabitacion(Habitacion *&pcabHab,string codigo);
void fun_eliminarHabitacion(Habitacion *&pcabHab,Habitacion *&pfinHab);
void ModificarHabitaciones(Habitacion*pcabHab,Habitacion*pfinHab);

void MostrarHab(Habitacion *pcabHab);
void MostrarHabdepende(Habitacion *pcabHab,int op,int &band);
void MostrarHab_por_codigo(Habitacion *pcabHab,string codigo,int y,int x);

void fun_registrarPersona(string cedula,int dia, int mes, int anio, int hora, int min,Persona *&pcabPer,Persona *&pfinPer);
Persona *fun_buscarPersona(string cedula,Persona *pcabPer);
void mostrarPersona(Persona *pcabPer);
void insertarPersona(Persona *&pcabPer,Persona *&pfinPer);

void Reservacion(int dia, int mes, int anio, int hora, int min,Persona *&pcabPer,Persona *&pfinPer,Habitacion *&pcabHab,Habitacion *&pfinHab);
void Confirmar_reservacion(Persona *&pcabPer,Persona *&pfinPer,Habitacion *&pcabHab,Habitacion *&pfinHab,CabFactura *&pcabFactu,CabFactura *&pfinFactu);
void sub_ingresoHab(string codigo,Habitacion *&pcabHab,Habitacion *&pfinHab,int respuesta);

void ingreso_bar(Bar *&pcabBar ,Bar *&pfinBar,Bar *&pcabReg,Bar *&pfinReg);
void sub_ingresoBar(string codigo,Bar *&pcabBar,Bar *&pfinBar,Bar *&pcabReg,Bar *&pfinReg);
Bar *fun_buscarProducto(string codigo,Bar *pcabBar);
void MostrarProducto(Bar *pcabBar);
void MostrarProducto_por_codigo(string codigo,Bar *pcabBar,int y, int x);
void ModificarProducto(Bar *&pcabBar, Bar *&pfinBar);
void fun_eliminarProducto(Bar *&pcabBar, Bar *pfinBar);
void EliminarProducto(Bar *&pcabBar, string codigo);

void Compra_productos_bar(Persona *&pcabPer,Persona *&pfinPer,Bar *&pcabBar,Bar *&pfinBar,Bar *&pcabReg,Bar *&pfinReg,CabFactura *&pcabFactu,CabFactura *&pfinFactu,int y, int x);

void Pagar_reservacion(Persona *&pcabPer,Persona *&pfinPer,CabFactura *&pcabFactu,CabFactura *&pfinFactu,Habitacion *&pcabHab);

CabFactura *buscardetafact(string cedula,CabFactura *pcabFactu);
void listarDetalles(CabFactura *aux,float &total);
void Mostrar_factura(CabFactura *aux,Persona *pcabPer,Habitacion *&pcabHab);

CabFactura *buscardetafact_codigo(string cedula,CabFactura *pcabFactu);
void Mostrar_factura_codigo(CabFactura *aux,Persona *pcabPer,Habitacion *&pcabHab);

void marco();
void reloj();
void logo();
void chao();
void limpiado_de_pantalla();
void limpiado_de_lineas(int f, int g);
void bor();

int main(){
	
	
 		/**/   			std::time_t t = std::time(0);   // get time now	 //
/**/    		std::tm* now = std::localtime(&t);							//
/**/    		int anio=(now->tm_year + 1900); 							//
/**/    		int mes=(now->tm_mon + 1);									//
/**/    		int dia=now->tm_mday;										//	
/**/			int hora   = now->tm_hour;									//	
/**/  			int min   = now->tm_min;									//

	marco(); reloj(); //system("color 07");
	//punteros para el producto
	Bar *pcabBar=NULL;
	Bar *pfinBar=NULL;
	Bar *pcabReg=NULL;
	Bar *pfinReg=NULL;
	//punteros para la factura
	CabFactura *pcabFactu=NULL;
	CabFactura *pfinFactu=NULL;
	//punteros para Persona	
	Persona *pcabPer=NULL;
	Persona *pfinPer=NULL;
	
	Habitacion *pcabHab=NULL;
	Habitacion *pfinHab=NULL;
	
	int x,y;

	int op,respuesta,f,g;
    retorno:
    limpiado_de_lineas( f, g);
	do{
		gotoxy(4,30);cout<<"Elija su opcion:                          ";
		
		limpiado_de_lineas( f, g);
		op=menu();
		operaciones(op,dia,mes,x,y,anio,hora,min,pcabPer,pfinPer,pcabFactu,pfinFactu,pcabBar,pfinBar,pcabReg,pfinReg,pcabHab,pfinHab);
		if(op!=5 && op!=4){
			goto retorno;
			gotoxy(4,30);cout<<"Desea realizar otra operacion si(1):";
			gotoxy(41,30);cin>>respuesta;
		}
		else if(op==4){
			gotoxy(4,38);cout<<"---PULSE UNA TECLA PARA CONTINUAR---: ";
			getch();
			gotoxy(4,30);cout<<"Desea realizar otra operacion si(1):";
			gotoxy(41,30);cin>>respuesta;
			system("cls");
			goto retorno;
		}
		else if(op==5){
			gotoxy(4,38);cout<<"---PULSE UNA TECLA PARA CONTINUAR---: ";
			getch();
		}
		limpiado_de_lineas(f,g);
	}while(respuesta==1);
	limpiado_de_lineas(f,g);
	system("cls");
	chao();
	return 0;
}

int menu(){
	int respuesta;
	gotoxy(30,10);printf("            MENU PRINCIPAL         ");
	do{
		gotoxy(4,15);cout<<"1: ADMINISTRADOR             ";
		gotoxy(4,17);cout<<"2: RECEPCIONISTA             ";
		gotoxy(4,19);cout<<"3: COMPRAS PRODUCTO EN BAR   ";
		gotoxy(4,21);cout<<"4: VER FACTURA               ";
		gotoxy(4,23);cout<<"5: SALIR                     ";
		gotoxy(21,30);cin>>respuesta;
	}while(respuesta<1 or respuesta>5);
	return respuesta;
}

int menu_hab_bar(){
	int respuesta;
	gotoxy(30,10);printf("        Usuario:  ADMINISTRADOR        ");
	do{
		gotoxy(4,15);cout<<"1: HABITACIONES              ";
		gotoxy(4,17);cout<<"2: BAR                       ";
		gotoxy(4,19);cout<<"3: REGRESAR                  ";
		gotoxy(4,21);cout<<"                             ";
		gotoxy(4,23);cout<<"                             ";
		gotoxy(21,30);cin>>respuesta;
	}while(respuesta<1 or respuesta>3);
	return respuesta;
}


int menuHabitacion(){
	int respuesta;
	do{
		gotoxy(6,13);cout<<"         MENU HABITACIONES            "<<endl;
		gotoxy(4,15);cout<<"1: INGRESO DE HABITACIONES   ";
		gotoxy(4,17);cout<<"2: MODIFICAR HABITACIONES    ";
		gotoxy(4,19);cout<<"3: ELIMINAR HABITACIONES     ";
		gotoxy(4,21);cout<<"4: LISTAR HABITACIONES       ";
		gotoxy(4,23);cout<<"5: REGRESAR                  ";
		gotoxy(21,30);cin>>respuesta;
	}while(respuesta<1 or respuesta>5);
	return respuesta;
}

int menuBar(){
	int respuesta;
	do{
		gotoxy(6,13);cout<<"         MENU BAR                     ";
		gotoxy(4,15);cout<<"1: INGRESO DE PRODUCTOS      ";
		gotoxy(4,17);cout<<"2: MODIFICAR PRODUCTOS       ";
		gotoxy(4,19);cout<<"3: ELIMINAR PRODUCTOS        ";
		gotoxy(4,21);cout<<"4: LISTAR PRODUCTOS          ";
		gotoxy(4,23);cout<<"5: REGRESAR                  ";
		gotoxy(21,30);cin>>respuesta;
	}while(respuesta<1 or respuesta>5);
	return respuesta;
}


int menuhab(){
	int respuesta;
	do{
		gotoxy(6,13);cout<<"MENU DE INGRESO DE HABITACIONES";
		gotoxy(4,15);cout<<"1: HABITACIONES SENCILLAS    ";
		gotoxy(4,17);cout<<"2: HABITACIONES MATRIMONIALES";
		gotoxy(4,19);cout<<"3: HABITACIONES MULTIPLES    ";
		gotoxy(21,30);cin>>respuesta;		
	}while(respuesta<1 or respuesta>3);
	return respuesta;	
}

int menuReservacion(){
	int respuesta;
	limpiado_de_pantalla();
	gotoxy(30,10);printf("        Usuario:  RECEPCIONISTA         ");	
	do{
		gotoxy(6,13);cout<<"    MENU DE RESERVACIONES       ";
		gotoxy(4,15);cout<<"1: INGRESO DE DATOS          ";
		gotoxy(4,17);cout<<"2: CONFIRMAR RESERVACION     ";
		gotoxy(4,19);cout<<"3: PAGAR RESERVACION         ";		
		gotoxy(4,21);cout<<"4: REGRESAR                  ";
		gotoxy(4,30);cout<<"Opcion:                       ";
		gotoxy(21,30);cin>>respuesta;
	}while(respuesta<1 or respuesta>4);
	return respuesta;	
}

void operaciones(int op,int dia,int mes,int x,int y,int anio,int hora,int min,Persona *&pcabPer,Persona *&pfinPer,CabFactura *&pcabFactu,CabFactura *&pfinFactu,Bar *&pcabBar,Bar	*&pfinBar,Bar *&pcabReg,Bar *&pfinReg,Habitacion *&pcabHab, Habitacion *&pfinHab){
	int respuesta,seguir;
	CabFactura *aux=NULL;
	string cedula,codigo;
	switch(op){
		case 1:
			retorno:
			respuesta=menu_hab_bar();
			switch(respuesta){
				case 1:
					returno:
					marco(); reloj(); 
					gotoxy(30,10);printf("        Usuario:  ADMINISTRADOR        ");
					respuesta=menuHabitacion();
					switch(respuesta){
						case 1: //Ingreso de habitaciones
							Registro_Habitaciones(pcabHab, pfinHab );
							goto returno;
						break;
						case 2://Modificar habitaciones
							ModificarHabitaciones(pcabHab,pfinHab);
							goto returno;
						break;
						case 3: //Eliminar habitaciones
							fun_eliminarHabitacion(pcabHab,pfinHab);
							goto returno;
						break;
						case 4: //listar
							if(pcabHab!=NULL){
								system("cls");
								MostrarHab(pcabHab);
								system("cls");
							}else{
								limpiado_de_pantalla();
								gotoxy(4,35);cout<<"NO EXISTE NINGUNA HABITACION REGISTRADA";
								getch();
								gotoxy(4,35);cout<<"                                                     ";
							}
							goto returno;
						break;
					}
					goto retorno;
				break;
				case 2:
					retu:
					marco(); reloj(); 
					gotoxy(30,10);printf("        Usuario:  ADMINISTRADOR         ");
					respuesta=menuBar();
					switch(respuesta){
						case 1: //Ingreso de Productos
							do{
								ingreso_bar(pcabBar,pfinBar,pcabReg,pfinReg);
								gotoxy(4,30);cout<<"Desea volver a ingresar algun producto? Si(1), No(0): ";
								cin>>seguir;
								gotoxy(4,30);cout<<"                                                        ";
							}while(seguir==1);
							goto retu;
						break;
						case 2://Modificar Productos
							do{
								ModificarProducto(pcabBar,pfinBar);
								gotoxy(4,30);cout<<"Desea volver a modificar algun producto? Si(1), No(0): ";
								cin>>seguir;
								gotoxy(4,30);cout<<"                                                        ";
							}while(seguir==1);
							goto retu;	
						break;
						case 3: //Eliminar Productos
							do{	
								fun_eliminarProducto(pcabBar,pfinBar);
								gotoxy(4,30);cout<<"Desea volver a eliminar algun producto? Si(1), No(0): ";
								cin>>seguir;
								gotoxy(4,30);cout<<"                                                        ";
							}while(seguir==1);
							goto retu;	 
						break;
						case 4: //listar
						if(pcabBar!=NULL){
							system("cls");
							MostrarProducto(pcabBar);
						}
						else
							{
							limpiado_de_pantalla();
								gotoxy(4,30);cout<<"NO EXISTE NINGUNA HABITACION REGISTRADa";
								getch();
								gotoxy(4,30);cout<<"                                                       ";
							}
						goto retu;
						break;
					}
					goto retorno;
				break;
			}
		break;
		case 2: //Recepcionista	
			gf:
			respuesta=menuReservacion();
			switch(respuesta){
				case 1: //Ingreso de personas
					Reservacion(dia,mes,anio,hora,min,pcabPer,pfinPer,pcabHab,pfinHab);
					goto gf;
				break;
				case 2: //confirmar reservacion
					Confirmar_reservacion(pcabPer,pfinPer,pcabHab,pfinHab,pcabFactu,pfinFactu);//AQUI ESTUVO MOOR 
					goto gf;
				break;
				case 3: //pagar reservacion
					Pagar_reservacion(pcabPer,pfinPer,pcabFactu,pfinFactu,pcabHab);
					goto gf;
				break;
			}
		break;
		
		case 3://compras en el bar
			gotoxy(30,10);printf("          Usuario: BAR         ");
			Compra_productos_bar(pcabPer,pfinPer,pcabBar,pfinBar,pcabReg,pfinReg,pcabFactu,pfinFactu,y,x);
		break;
		case 4: 
			system("cls");
			logo();
			gotoxy(30,10);cout<<"CODIGO DE LA FACTURA: ";
			cin>>cedula;
			
			aux=buscardetafact_codigo(cedula,pcabFactu);
			
			if(aux!=NULL){
				Mostrar_factura_codigo(aux,pcabPer,pcabHab);
			}else{
				gotoxy(4,34);cout<<"NO EXISTE FACTURA CON ESE CODIGO";
				getch();
				gotoxy(4,34);cout<<"                                        ";
			}
		break;	
	}
}

void Registro_Habitaciones(Habitacion *&pcabHab, Habitacion *&pfinHab ){
	int cantHab,op,respuesta,f,g;
	string codigo;
	string descripcion;
	float precio_base;
	float tasa;
	float iva;
	int y=4,x=14;
	Habitacion *nuevaHabitacion=NULL;
	do{	
		limpiado_de_pantalla();
		respuesta=menuhab();
		limpiado_de_pantalla();
		gotoxy(6,13);cout<<"INGRESE DE DATOS DE HABITACION ";
		gotoxy(4,15);cout<<"Numero:                      ";gotoxy(12,15);cin>>codigo;//RESPUESTA 
		nuevaHabitacion=fun_buscarHabitacion_por_tipo(codigo,pcabHab,respuesta);
		if(nuevaHabitacion!=NULL){
			logo1();
			MostrarHab_por_codigo(pcabHab,codigo,y,x); 
			gotoxy(4,34);cout<<"HABITACION CON ESE CODIGO YA ESTA REGISTRADA";
		}else{
			nuevaHabitacion=fun_buscarHabitacion(codigo,pcabHab);
			if(nuevaHabitacion!=NULL){
				MostrarHab_por_codigo(pcabHab,codigo,y,x);
				gotoxy(4,34);cout<<"HABITACION CON ESE CODIGO YA ESTA REGISTRADA";
			}else{
				sub_ingresoHab(codigo,pcabHab,pfinHab,respuesta);
			}
		}
		gotoxy(4,25);cout<<"Registrar otra habitacion Si(1) o No(2): ";
		gotoxy(21,30);cout<<"                  ";gotoxy(21,30);cin>>op;
	}while(op==1);
	limpiado_de_pantalla();
}

void sub_ingresoHab(string codigo,Habitacion *&pcabHab,Habitacion *&pfinHab,int respuesta){
	float iva;
	float tasa;
	int cantHab;
	Habitacion *nuevaHabitacion;
	nuevaHabitacion = new(Habitacion);
	nuevaHabitacion->codigo=codigo;
	gotoxy(4,17);cout<<"Descripcion:                 ";fflush(stdin);gotoxy(17,17);cin>>nuevaHabitacion->descripcion;
	gotoxy(4,19);cout<<"Precio:                      ";gotoxy(12,19);cin>>nuevaHabitacion->precio_base;
	gotoxy(4,21);cout<<"Iva(ejemplo 12% =12):        ";gotoxy(26,21);cin>>nuevaHabitacion->iva;
	limpiado_de_pantalla();
	gotoxy(4,13);cout<<"   ******* TEMPORADA ******";
	gotoxy(4,15);cout<<"ALTA=15%   MEDIA=10%   BAJA=0%";
	gotoxy(4,17);cout<<"Tasa: ";gotoxy(10,17);cin>>nuevaHabitacion->tasa;
	if(respuesta==3){
	gotoxy(4,19);cout<<"Cantidad de camas: ";gotoxy(23,19);cin>>nuevaHabitacion->cantHab;
	}else{
		nuevaHabitacion->cantHab=1;
		gotoxy(4,19);cout<<"Vista al mar Si(1) o No(2):  ";gotoxy(32,19);cin>>nuevaHabitacion->vistaalmar;
	}
	nuevaHabitacion->tipodeHabitacion=respuesta;
	nuevaHabitacion->estado=1;
	nuevaHabitacion->iva=(nuevaHabitacion->iva/100);
	nuevaHabitacion->tasa=(nuevaHabitacion->tasa/100);
	nuevaHabitacion->sgte=NULL;
	nuevaHabitacion->ant=NULL;
	
	if(pcabHab==NULL){
		pcabHab=nuevaHabitacion;
		pfinHab=nuevaHabitacion;
	}else{
		pfinHab->sgte=nuevaHabitacion;
		nuevaHabitacion->ant=pfinHab;
		pfinHab=nuevaHabitacion;
	}
}

void ModificarHabitaciones(Habitacion *pcabHab,Habitacion *pfinHab){
	Habitacion *HabAct=NULL;
	float tasa;
	float iva;
	string codigo,numero;
	bor();
	limpiado_de_pantalla();
	gotoxy(6,13);cout<<"MODIFICAR DATOS DE HABITACION ";
	gotoxy(4,15);cout<<"Numero:                      ";gotoxy(12,15);cin>>codigo;
	HabAct=fun_buscarHabitacion(codigo,pcabHab);
	int y=38,x=14;
	MostrarHab_por_codigo(pcabHab,codigo,y,x);
	gotoxy(4,34);system("pause");
	gotoxy(4,34);cout<<"                                         ";
	
	if(HabAct !=NULL){	
		int op;
		do{
			limpiado_de_pantalla();
			gotoxy(4,15);cout<<"MENU MODIFICAR HABITACION";
			gotoxy(4,17);cout<<"1. Numero                    ";
			gotoxy(4,18);cout<<"2. Descripcion               ";
			gotoxy(4,19);cout<<"3. Precio                    ";
			gotoxy(4,20);cout<<"4. Tasa                      ";
			gotoxy(4,21);cout<<"5. Iva                       ";
			gotoxy(4,22);cout<<"6. Tipo de habitacion        ";
			gotoxy(4,30);cout<<"Opcion:                             ";
			gotoxy(12,30);cin>>op;
			fflush(stdin);
		}while(op<1 or op>6);
		limpiado_de_pantalla();
		switch(op){
			case 1:
				gotoxy(4,15);cout<<"Numero: ";cin>>numero;
				fflush(stdin);
				HabAct=fun_buscarHabitacion(numero,pcabHab);
				if(HabAct==NULL){
					HabAct->codigo=numero;
					gotoxy(4,34);cout<<"CAMBIO REALIZADO CORRECTAMENTE";
					getch();
				}else{
					gotoxy(4,34);cout<<"EL NUMERO DE HABITACION YA EXISTE";
					getch();
				}
			break;
			case 2:
				gotoxy(4,15);cout<<"DESCRIPCION NUEVA: ";cin>>HabAct->descripcion;
				gotoxy(4,34);cout<<"CAMBIO REALIZADO CORRECTAMENTE";
			break;
			case 3:
				gotoxy(4,15);cout<<"PRECIO NUEVO: ";cin>>HabAct->precio_base;
				gotoxy(4,34);cout<<"CAMBIO REALIZADO CORRECTAMENTE";
			break;
			case 4:
				gotoxy(4,15);cout<<"TASA NUEVA: ";cin>>tasa;
				HabAct->tasa=(tasa/100);
				gotoxy(4,34);cout<<"CAMBIO REALIZADO CORRECTAMENTE";
			break;
			case 5:
				gotoxy(4,15);cout<<"IVA NUEVO: ";cin>>iva;
				HabAct->iva=(iva/100);
				gotoxy(4,34);cout<<"CAMBIO REALIZADO CORRECTAMENTE";
			break;
			case 6:
				gotoxy(4,15);cout<<"1: HABITACIONES SENCILLAS    ";
				gotoxy(4,17);cout<<"2: HABITACIONES MATRIMONIALES";
				gotoxy(4,19);cout<<"3: HABITACIONES MULTIPLES    ";
				gotoxy(4,21);cout<<"Tipo de habitacion: ";cin>>HabAct->tipodeHabitacion;
				if(HabAct->tipodeHabitacion==3){
					gotoxy(4,23);cout<<"Cantidad de camas: ";cin>>HabAct->cantHab;
				}else{
					HabAct->cantHab=1;
				}
				gotoxy(4,34);cout<<"CAMBIO REALIZADO CORRECTAMENTE";
			break;
		}
	}else{
		gotoxy(4,34);cout<<"EL NUMERO DE HABITACION NO EXISTE";
	}
	gotoxy(4,34);cout<<"                                     ";
	getch();
	limpiado_de_pantalla();
}

void fun_eliminarHabitacion(Habitacion *&pcabHab,Habitacion *&pfinHab){
	Habitacion *direccion=NULL;
	Habitacion *dirEliminar=NULL;
	string codigo;
	bor();
	limpiado_de_pantalla();
	gotoxy(4,15);cout<<"Ingrese el numero de la habitacion a eliminar: ";cin>>codigo;
	direccion=fun_buscarHabitacion(codigo,pcabHab);
	int y=12,x=14;
	MostrarHab_por_codigo(pcabHab,codigo,y,x);
	if(direccion!=NULL){
		EliminarHabitacion(pcabHab,codigo);
		gotoxy(4,34);cout<<"HABITACION ELIMINADA CORRECTAMENTE";
	}else{
		gotoxy(4,34);cout<<"LA HABITACION INGRESADA NO EXISTE";
	}
	getch();
	gotoxy(4,35);cout<<"                                       ";
	limpiado_de_pantalla();
}

void ModificarProducto(Bar *&pcabBar, Bar *&pfinBar){
	Bar *BarAct=pcabBar;
	float iva;
	string codigo,numero;
	Bar *Barcamb=NULL;
	limpiado_de_pantalla();
	gotoxy(6,13);cout<<"MODIFICAR DATOS DEL PRODUCTO";
	gotoxy(4,15);cout<<"Numero:                      ";gotoxy(12,15);cin>>codigo;
	BarAct=fun_buscarProducto(codigo,pcabBar);
	
	if(BarAct!=NULL){
		int op;
		do{
			limpiado_de_pantalla();
			gotoxy(6,15);cout<<"     ***___MENU MODIFICAR___***"<<endl;
			gotoxy(4,17);cout<<"1. Numero                          ";
			gotoxy(4,19);cout<<"2. Descripcion                     ";
			gotoxy(4,21);cout<<"3. Precio                          ";
			gotoxy(4,23);cout<<"4. Iva                             ";
			gotoxy(4,30);cout<<"Opcion:             ";gotoxy(12,30);cin>>op;
		}while(op<1 or op>4);
		limpiado_de_pantalla();
		switch(op){
			case 1:
				gotoxy(4,17);cout<<"NUMERO:                               ";gotoxy(13,17);cin>>numero;
				Barcamb=fun_buscarProducto(numero,pcabBar);
				if(Barcamb==NULL){
					BarAct->codigo=numero;
					gotoxy(4,34);cout<<"CAMBIO REALIZADO CORRECTAMENTE             ";
					getch;
				}
				getch;
			break;
			case 2:
				gotoxy(4,17);cout<<"Descripcion nueva:                               ";gotoxy(23,17);cin>>BarAct->descripcion;
				gotoxy(4,34);cout<<"CAMBIO REALIZADO CORRECTAMENTE                    ";
			break;
			case 3:
				gotoxy(4,17);cout<<"Precio nuevo:                               ";gotoxy(19,17);cin>>BarAct->precio;
				gotoxy(4,34);cout<<"CAMBIO REALIZADO CORRECTAMENTE                     ";
			break;
			case 4:
				gotoxy(4,17);cout<<"Iva nuevo:                               ";gotoxy(15,17);cin>>iva;
				BarAct->iva=(iva/100);
				gotoxy(4,34);cout<<"CAMBIO REALIZADO CORRECTAMENTE                   ";
			break;
		}
	}else{
		gotoxy(4,34);cout<<"EL CODIGO DE PRODUCTO NO EXISTE                "; 
	}
	getch();
	limpiado_de_pantalla();
}

void fun_eliminarProducto(Bar *&pcabBar, Bar *pfinBar){
	Bar *direccion=NULL;
	Bar *dirEliminar=NULL;
	string codigo;
	bor();
	limpiado_de_pantalla();
	gotoxy(6,13);cout<<"ELIMINAR PRODUCTO";
	gotoxy(4,15);cout<<"Ingrese el codigo del producto a eliminar:      ";gotoxy(48,15);cin>>codigo;
	direccion=fun_buscarProducto(codigo,pcabBar);
	if(direccion!=NULL){
		EliminarProducto(pcabBar,codigo);
		gotoxy(4,34);cout<<"EL PRODUCTO FUE ELIMINADO CORRECTAMENTE                    ";
	}else{
		gotoxy(4,34);cout<<"EL PRODUCTO INGRESADO NO EXISTE                    ";
	}
	getch();
	limpiado_de_pantalla();
}

void EliminarProducto(Bar *&pcabBar, string codigo)
{
	if(pcabBar != NULL){
		Bar *dirEliminar=new (Bar);
		dirEliminar=pcabBar;
		Bar *ant = NULL;
		//RECORRE LA LISTA
		while(dirEliminar!=NULL){
			if(dirEliminar->codigo == codigo){//ELEMENTO NO HA SIDO ENCONTRADO
				if(dirEliminar == NULL){
					gotoxy(4,34);cout<<"CODIGO DEL PRODUCTO NO EXISTE EN EL SISTEMA: ";
				}else if(ant==NULL){//PRIMER ELEMENTO A ELIMINAR
					pcabBar = pcabBar->sgte;
					delete dirEliminar;
				}else{//ELEMENTO ESTA EN LA LISTA, PERO NO ES EL PRIMERO
					ant->sgte=dirEliminar->sgte;
					delete dirEliminar;
				}
			}
			ant=dirEliminar;
			dirEliminar = dirEliminar->sgte;
		}
	}
	getch();
	limpiado_de_pantalla();
}

void EliminarHabitacion(Habitacion *&pcabHab,string codigo){
	if(pcabHab != NULL){
		Habitacion *dirEliminar=new (Habitacion);
		dirEliminar=pcabHab;
		Habitacion *ant = NULL;
		//RECORRE LA LISTA
		while(dirEliminar!=NULL){ 
			if(dirEliminar->codigo == codigo){//ELEMENTO NO HA SIDO ENCONTRADO
				if(dirEliminar == NULL){
				gotoxy(4,34);cout<<"CODIGO DE LA HABITACION  NO EXISTE EN EL SISTEMA ";
				}else if(ant==NULL){//PRIMER ELEMENTO A ELIMINAR
					pcabHab = pcabHab->sgte;
					delete dirEliminar;
				}else{//ELEMENTO ESTA EN LA LISTA, PERO NO ES EL PRIMERO
					ant->sgte=dirEliminar->sgte;
					delete dirEliminar;
				}
			}
			ant=dirEliminar;
			dirEliminar = dirEliminar->sgte;
		}
	}
}

Persona *fun_buscarPersona(string cedula,Persona *pcabPer){
	Persona *direccion=NULL;
	Persona *personaActual=pcabPer;
	while(personaActual!=NULL){
		if(personaActual->cedula==cedula){
			return personaActual;
		}	
		personaActual=personaActual->sgte;
	}
	return direccion;
}

void mostrarPersona(Persona *nuevaPersona){
	limpiado_de_pantalla();
	gotoxy(6,13);cout<<"CEDULA "<<nuevaPersona->cedula;
	gotoxy(6,14);cout<<"NOMBRE: "<<nuevaPersona->nombre;
	gotoxy(6,15);cout<<"DIRECCION: "<<nuevaPersona->direccion;
	gotoxy(6,16);cout<<"EMAIL: "<<nuevaPersona->email;
	gotoxy(6,17);cout<<"TELEFONO: "<<nuevaPersona->telefono<<endl;
}


void Reservacion(int dia, int mes, int anio, int hora, int min,Persona *&pcabPer,Persona *&pfinPer,Habitacion *&pcabHab,Habitacion *&pfinHab){
	
	int resp,op;
	
	int dia1,dia2;
	int mes1,mes2;
	int anio1,anio2;
	
	string codigo;
	string cedula;
	
	Persona *nuevaPersona=NULL;
	Habitacion *nuevaHabitacion=NULL;
	Habitacion *anterior;
	limpiado_de_pantalla();
	if(pcabHab!=NULL){
		gotoxy(6,13);cout<<"Ingreso de datos para la reservacion";
		do{
			int op;
			gotoxy(6,15);cout<<"**Ingreso de datos del Huesped**";
			gotoxy(4,17);cout<<"Cedula: ";
			cin>>cedula;
			
			nuevaPersona=fun_buscarPersona(cedula,pcabPer);
			if(nuevaPersona!=NULL){
				//Recuperar datos de la persona
				limpiado_de_pantalla();
				mostrarPersona(nuevaPersona);
			}else{
				//Crear una nueva persona el cliente no existe
				fun_registrarPersona(cedula,dia,mes,anio,hora,min,pcabPer,pfinPer);
			}
			
			op=menuhab();
			int band=0;
			
			MostrarHabdepende(pcabHab,op,band);
			if(band==1){
				
				cout<<"\nIngreso el numero de la Habitacion: ";
				cin>>codigo;
				nuevaHabitacion=fun_buscarHabitacion_por_tipo(codigo,pcabHab,op);
				if(nuevaHabitacion!=NULL){
					nuevaPersona=fun_buscarPersona(cedula,pcabPer);
					nuevaPersona->numero_de_la_habitacion=codigo;
					nuevaHabitacion->estado=2;
					cout<<"\nReservacion exitosamente";
				}else{
					cout<<"\nEse numero de habitacion no existe";
				}
				getch();
			}else{
				cout<<"\nNo existe ninguna habitacion de ese tipo";
			}
			getch();
			system("cls");
			marco(); reloj();
			gotoxy(38,10);printf("Usuario:  RECEPCIONISTA");	
			gotoxy(4,30);cout<<"Realizar otra reservacion Si(1): ";
			gotoxy(38,30);cin>>resp;
			gotoxy(4,30);cout<<"                                   ";
		}while(resp==1);
	}else{
		gotoxy(4,34);cout<<"Registre almenos una habitacion         ";
		getch();
		gotoxy(4,25);cout<<"                                       ";
	}
}

void fun_registrarPersona(string cedula,int dia, int mes, int anio, int hora, int min,Persona *&pcabPer,Persona *&pfinPer){
	Persona *nuevaPersona;
	
	nuevaPersona=new(Persona);
	nuevaPersona->cedula=cedula;
	limpiado_de_pantalla();
	gotoxy(4,15);cout<<"Nombre: ";cin>>nuevaPersona->nombre;
	gotoxy(4,17);cout<<"Direccion: ";cin>>nuevaPersona->direccion;
	gotoxy(4,19);cout<<"Telefono: ";cin>>nuevaPersona->telefono;
	gotoxy(4,21);cout<<"Email: ";cin>>nuevaPersona->email;
	do{
		gotoxy(4,20);cout<<"                                                               ";
		gotoxy(4,22);cout<<"                                                               ";
		limpiado_de_pantalla();
		gotoxy(4,15);cout<<dia<<"/"<<mes<<"/"<<anio<<endl;
		gotoxy(4,17);cout<<"Digite la fecha de entrada al hotel (dd/mm/aa): ";
		gotoxy(4,19);cout<<"Dia: ";cin>>nuevaPersona->dia1;
		gotoxy(14,19);cout<<"Mes: ";cin>>nuevaPersona->mes1;
		gotoxy(24,19);cout<<"Año: ";cin>>nuevaPersona->anio1;
		if(nuevaPersona->dia1<dia && nuevaPersona->mes1<mes && nuevaPersona->anio1<anio){
			gotoxy(4,35);cout<<"Fecha incorrecta ingrese denuevo";
			getch();
		}
	}while(nuevaPersona->dia1<dia && nuevaPersona->mes1<mes && nuevaPersona->anio1<anio);
	
	do{
		gotoxy(4,24);cout<<"                                                               ";
		gotoxy(4,26);cout<<"                                                               ";
		gotoxy(4,21);cout<<dia<<"/"<<mes<<"/"<<anio<<endl;
		gotoxy(4,23);cout<<"Digite la fecha de salida del hotel (dd/mm/aa): "<<endl;
		gotoxy(4,25);cout<<"Dia: ";cin>>nuevaPersona->dia2;
		gotoxy(14,25);cout<<"Mes: ";cin>>nuevaPersona->mes2;
		gotoxy(24,25);cout<<"Año: ";cin>>nuevaPersona->anio2;	
		if(nuevaPersona->dia2<dia && nuevaPersona->mes2<mes && nuevaPersona->anio2<anio){
			gotoxy(4,35);cout<<"Fecha incorrecta ingrese denuevo";
			getch();
		}
	}while(nuevaPersona->dia2<dia && nuevaPersona->mes2<mes && nuevaPersona->anio2<anio);
	
	limpiado_de_pantalla();
	
	if(nuevaPersona->dia1==nuevaPersona->dia2 &&nuevaPersona->mes1==nuevaPersona->mes2 && nuevaPersona->anio1==nuevaPersona->anio2){
		gotoxy(6,15);cout<<"FECHAS SEMEJANTES";
		gotoxy(4,17);cout<<hora<<":"<<min;
		gotoxy(4,19);cout<<"Ingrese la hora de Salida ";
		gotoxy(4,21);cout<<"Hora: ";cin>>nuevaPersona->hora;
		gotoxy(14,21);cout<<"Minutos: ";cin>>nuevaPersona->min;
		//gotoxy(4,13);cout<<"  ";
		//gotoxy(4,14);cout<<"     ";
	}
	
	nuevaPersona->band=0;
	nuevaPersona->sgte=NULL;
	nuevaPersona->ant=NULL;
	if(pcabPer==NULL){
		pcabPer=nuevaPersona;
		pfinPer=nuevaPersona;
	}else{
		pfinPer->sgte=nuevaPersona;
		nuevaPersona->ant=pfinPer;
		pfinPer=nuevaPersona;
	}
	
}

void MostrarHab_por_codigo(Habitacion *pcabHab,string codigo,int y,int x){
	Habitacion *nuevaHabitacion=pcabHab;
	while(nuevaHabitacion!=NULL){
		if(nuevaHabitacion->codigo==codigo){
			
			gotoxy(6,19);cout<<"NUMERO: "<<nuevaHabitacion->codigo<<endl;
			
			gotoxy(6,20);cout<<"Tipo de habitacion: ";
			if(nuevaHabitacion->tipodeHabitacion==1){
				gotoxy(6,21);cout<<"Habitacion sencilla";
			}
			if(nuevaHabitacion->tipodeHabitacion==2){
				gotoxy(6,21);cout<<"Habitacion matrimonial";
			}
			if(nuevaHabitacion->tipodeHabitacion==3){
				gotoxy(6,21);cout<<"Habitacion mixta";
			}
			gotoxy(6,22);cout<<"Descripcion de habitacion: "<<nuevaHabitacion->descripcion;
			gotoxy(6,23);cout<<"Precio: "<<nuevaHabitacion->precio_base;
			gotoxy(6,24);cout<<"Iva: "<<nuevaHabitacion->iva;
			gotoxy(6,25);cout<<"Tasa (TEMPORADA): "<<nuevaHabitacion->tasa;
			gotoxy(6,26);cout<<"Cantidad de cama: "<<nuevaHabitacion->cantHab;
		}
		nuevaHabitacion=nuevaHabitacion->sgte;
		y=y+1;
	}
}
void MostrarHab(Habitacion *pcabHab){
	Habitacion *nuevaHabitacion=pcabHab;
	while(nuevaHabitacion!=NULL){
		cout<<"\n\n*********************************"<<endl;
		cout<<"NUMERO: "<<nuevaHabitacion->codigo<<endl;
		cout<<"---------------------------------"<<endl;
		cout<<"TIPO DE HABITACION: ";
		if(nuevaHabitacion->tipodeHabitacion==1)
			cout<<"HABITACION SENCILLA\n";
		if(nuevaHabitacion->tipodeHabitacion==2)
			cout<<"HABITACION MATRIMONIAL\n";
		if(nuevaHabitacion->tipodeHabitacion==3)
			cout<<"HABITACION MIXTA\n";
		cout<<"VISTA AL MAR: ";	
		if(nuevaHabitacion->vistaalmar==1){
			cout<<"SI\n";
		}else{
			cout<<"NO\n";
		}
		cout<<"DESCRPCION: "<<nuevaHabitacion->descripcion<<endl;
		cout<<"PRECIO: "<<nuevaHabitacion->precio_base<<endl;
		cout<<"IVA: "<<nuevaHabitacion->iva<<endl;
		cout<<"TASA (TEMPORADA): "<<nuevaHabitacion->tasa<<endl;
		cout<<"CANTIDAD DE CAMAS: "<<nuevaHabitacion->cantHab<<endl<<endl;
		nuevaHabitacion=nuevaHabitacion->sgte;
		cout<<"\nPULSE UN TECLA PARA CONTINUAR";
	}
	getch();
	gotoxy(0,1);printf("                                        ");
	gotoxy(0,2);printf("                                        ");
	gotoxy(0,3);printf("                                        ");
	gotoxy(0,4);printf("                                        ");
	gotoxy(0,5);printf("                                        ");
	gotoxy(0,6);printf("                                        ");
	gotoxy(0,7);printf("                                        ");
	gotoxy(0,8);printf("                                        ");
	gotoxy(0,9);printf("                                        ");
	gotoxy(0,10);printf("                                        ");
}

void MostrarHabdepende(Habitacion *pcabHab,int op,int &band){
	system("cls");
	Habitacion *nuevaHabitacion=pcabHab;
	while(nuevaHabitacion!=NULL){
		if(nuevaHabitacion->tipodeHabitacion==op && nuevaHabitacion->estado==1){
			cout<<"\n\n*******************************"<<endl;
			cout<<"Numero: "<<nuevaHabitacion->codigo<<endl;
			cout<<"---------------------------------"<<endl;
			cout<<"Tipo de habitacion: ";
			if(nuevaHabitacion->tipodeHabitacion==1)
				cout<<"Habitacion sencilla\n";
			if(nuevaHabitacion->tipodeHabitacion==2)
				cout<<"Habitacion matrimonial\n";
			if(nuevaHabitacion->tipodeHabitacion==3)
				cout<<"Habitacion mixta\n";
			cout<<"Vista al mar: ";	
			if(nuevaHabitacion->vistaalmar==1){
				cout<<"SI\n";
			}else{
				cout<<"NO\n";
			}
			cout<<"Descripcion: "<<nuevaHabitacion->descripcion<<endl;
			cout<<"Precio: "<<nuevaHabitacion->precio_base<<endl;
			cout<<"Iva: "<<nuevaHabitacion->iva<<endl;
			cout<<"Tasa (Temporada): "<<nuevaHabitacion->tasa<<endl;
			cout<<"Cantidad de camas: "<<nuevaHabitacion->cantHab<<endl<<endl;
			band=1;
		}
		nuevaHabitacion=nuevaHabitacion->sgte;
		//cout<<"\n";
	}
}

Habitacion *fun_buscarHabitacion_por_tipo(string codigo,Habitacion *pcabHab,int respuesta){
	Habitacion *direccion=NULL;
	Habitacion *habitacionActual=pcabHab;
	while(habitacionActual!=NULL){
		if(habitacionActual->codigo==codigo && habitacionActual->tipodeHabitacion==respuesta){
			return habitacionActual;
		}	
		habitacionActual=habitacionActual->sgte;
	}
	return direccion;
}


Habitacion *fun_buscarHabitacion(string codigo,Habitacion *pcabHab){
	Habitacion *direccion=NULL;
	Habitacion *habitacionActual=pcabHab;
	while(habitacionActual!=NULL){
		if(habitacionActual->codigo==codigo){
			return habitacionActual;
		}	
		habitacionActual=habitacionActual->sgte;
	}
	return direccion;
}

void ingreso_bar(Bar *&pcabBar ,Bar *&pfinBar,Bar *&pcabReg,Bar *&pfinReg){
	int op,cant;
	char v='s';
	string codigo;
	string descripcion;
	float precio;
	float iva;
	int y=4,x=14;
	Bar *nuevoProducto=NULL;
	limpiado_de_pantalla();
	//gotoxy(4,14);cout<<"                             ";
	//gotoxy(4,15);cout<<"                             ";
	gotoxy(6,13);cout<<"INGRESE DE DATOS DEL PRODUCTO";
	gotoxy(4,15);cout<<"Codigo:                    ";gotoxy(12,15);cin>>codigo;
	nuevoProducto=fun_buscarProducto(codigo,pcabBar);
	if(nuevoProducto!=NULL){
		gotoxy(4,34);cout<<"CODIGO DE PRODUCTO YA EXISTE";
		string cod;
		cod=nuevoProducto->codigo;
		//MostrarProducto_por_codigo(cod,pcabBar, y, x);
		int res;
		gotoxy(4,25);cout<<"Aumentar cantidad existente si(1): ";
		cin>>res;
		if(res==1){
			cout<<"Cantidad a aumentar: ";
			cin>>res;
			nuevoProducto->cant=nuevoProducto->cant+res;
		}
	}else{
		sub_ingresoBar(codigo,pcabBar,pfinBar,pcabReg,pfinReg);
	}
	limpiado_de_pantalla();
}


void sub_ingresoBar(string codigo,Bar *&pcabBar,Bar *&pfinBar,Bar *&pcabReg,Bar *&pfinReg){
	float iva;
	Bar *nuevoProducto;
	Bar *nuevoRegistro;
	nuevoProducto = new(Bar);
	nuevoRegistro = new(Bar);
	nuevoProducto->codigo=codigo;
	gotoxy(4,17);cout<<"Descripcion: ";cin>>nuevoProducto->descripcion;
	gotoxy(4,19);cout<<"Precio: ";cin>>nuevoProducto->precio;
	gotoxy(4,21);cout<<"Valor del iva(ejemplo 12% =12): ";cin>>iva;
	gotoxy(4,23);cout<<"Cantidad: ";gotoxy(23,23);cin>>nuevoProducto->cant;
	nuevoProducto->iva=(iva/100);
	
	nuevoProducto->sgte=NULL;;
	nuevoProducto->ant=NULL;
	
	if(pcabBar==NULL){
		pcabBar=nuevoProducto;
		pfinBar=nuevoProducto;
	}else{
		pfinBar->sgte=nuevoProducto;
		nuevoProducto->ant=pfinBar;
		pfinBar=nuevoProducto;
	}
		limpiado_de_pantalla();
}

Bar *fun_buscarProducto(string codigo,Bar *pcabBar){
	Bar *direccion=NULL;
	Bar *productoActual=pcabBar;
	while(productoActual!=NULL){
		if(productoActual->codigo==codigo){
			return productoActual;
		}	
		productoActual=productoActual->sgte;
	}
	return direccion;
}

void MostrarProducto_por_codigo(string codigo,Bar *pcabBar,int y, int x){
	Bar *nuevoProducto=new (Bar);
	nuevoProducto=pcabBar;
	while(nuevoProducto!=NULL){
		if(nuevoProducto->codigo==codigo){
			gotoxy(6,17);cout<<"*********************************";
			gotoxy(6,18);cout<<"DATOS DEL PRODUCTO"<<endl;
			gotoxy(6,19);cout<<"---------------------------------"<<endl;
			gotoxy(6,20);cout<<"Codigo: "<<nuevoProducto->codigo<<endl;
			gotoxy(6,21);cout<<"---------------------------------"<<endl;
			gotoxy(6,22);cout<<"Descripcion: "<<nuevoProducto->descripcion<<endl;
			gotoxy(6,23);cout<<"Precio: "<<nuevoProducto->precio<<endl;
		    gotoxy(6,24);cout<<"Iva: "<<nuevoProducto->iva<<endl;
			gotoxy(6,25);cout<<"Cantidad: "<<nuevoProducto->cant<<endl<<endl;
		}
		nuevoProducto=nuevoProducto->sgte;
	y=y+1;
	}
	gotoxy(6,25);getch();
	limpiado_de_pantalla();
}

void MostrarProducto(Bar *pcabBar){
	Bar *nuevoProducto=new (Bar);
	nuevoProducto=pcabBar;
	while(nuevoProducto!=NULL){
		cout<<"\n\n**********************************"<<endl;
		cout<<"DATOS DEL PRODUCTO"<<endl;
		cout<<"----------------------------------"<<endl;
		cout<<"CODIGO DE PRODUCTO: "<<nuevoProducto->codigo<<endl;
		cout<<"----------------------------------"<<endl;
		cout<<"DESCRIPCION DEL producto: "<<nuevoProducto->descripcion<<endl;
		cout<<"PRECIO: "<<nuevoProducto->precio<<endl;
		cout<<"IVA: "<<nuevoProducto->iva<<endl;
		cout<<"CANTIDAD DE Productos: "<<nuevoProducto->cant<<endl<<endl;	
		nuevoProducto=nuevoProducto->sgte;
	}
	getch();
	gotoxy(0,1);printf("                                        ");
	gotoxy(0,2);printf("                                        ");
	gotoxy(0,3);printf("                                        ");
	gotoxy(0,4);printf("                                        ");
	gotoxy(0,5);printf("                                        ");
	gotoxy(0,6);printf("                                        ");
	gotoxy(0,7);printf("                                        ");
	gotoxy(0,8);printf("                                        ");
	gotoxy(0,9);printf("                                        ");
	gotoxy(0,10);printf("                                       ");
	system("cls");
	
}
 
void Compra_productos_bar(Persona *&pcabPer,Persona *&pfinPer,Bar *&pcabBar,Bar *&pfinBar,Bar *&pcabReg,Bar *&pfinReg,CabFactura *&pcabFactu,CabFactura *&pfinFactu,int y, int x){
	
	int resp,cantidad,i=0;
	float e;
	string codigo;
	string cedula;
	
	Persona *nuevaPersona=NULL;
	Bar *nuevoBar=NULL;
	
	CabFactura *dir=NULL;
	
	
	if(pcabBar!=NULL){
		do{
			limpiado_de_pantalla();
			gotoxy(6,13);cout<<"INGRESE DE DATOS DEL HUESPED"<<endl;
			gotoxy(4,15);cout<<"Cedula:                            ";gotoxy(13,15);cin>>cedula;
			nuevaPersona=fun_buscarPersona(cedula,pcabPer);
			if(nuevaPersona!=NULL){
				//Recuperar datos de la persona
				mostrarPersona(nuevaPersona);
				getch();
				if(nuevaPersona->band==1){
					limpiado_de_pantalla();
					gotoxy(6,13);cout<<"***INGRESE DE DATOS DEL PRODUCTO***";
					gotoxy(4,15);cout<<"Codigo:                  ";gotoxy(13,15);cin>>codigo;
					nuevoBar=fun_buscarProducto(codigo,pcabBar);
					if(nuevoBar!=NULL){
						MostrarProducto_por_codigo(codigo,pcabBar,x,y);
						gotoxy(4,15);cout<<"Cantidad:                     ";gotoxy(15,15);cin>>cantidad;
						limpiado_de_pantalla();
						if(cantidad>nuevoBar->cant){
							gotoxy(4,13);cout<<"*********************************";
							gotoxy(4,15);cout<<"NO HAY ESA CANTIDAD DEL PRODUCTO";
							gotoxy(4,17);cout<<"CANTIDAD DISPONIBLE: "<<nuevoBar->cant;
							gotoxy(4,19);cout<<"----------------------------------";
							getch();
						}else{
							nuevoBar->cant=(nuevoBar->cant)-cantidad;
							gotoxy(4,34);cout<<"SU COMPRA HA SIDO EXITOSA";
							
							
							//CabFactura *nuevaFactura=CabFactura;
							
							//nuevaFactura->pcabDetalleHab=NULL;
							//nuevaFactura->pfinDetalleHab=NULL;
							
							dir=buscardetafact(cedula,pcabFactu);
							
							
							DetalleHab *nuevoDetalleHab=new (DetalleHab);
							
							nuevoDetalleHab->cantidad=cantidad;
							
							//nuevoDetalleHab
							nuevoDetalleHab->codigoProduct=codigo;
							nuevoDetalleHab->descripcion=nuevoBar->descripcion;
							
							nuevoDetalleHab->precio=nuevoBar->precio;
							nuevoDetalleHab->iva=(nuevoBar->iva)/100;
							nuevoDetalleHab->subtotal=nuevoDetalleHab->subtotal+(cantidad*((nuevoBar->iva)/100))+cantidad;
			
			
							if((dir->pcabDetalleHab)==NULL){
								nuevoDetalleHab->ant=NULL;
								nuevoDetalleHab->sgte=NULL;
    							dir->pcabDetalleHab=nuevoDetalleHab;
							}else{
								nuevoDetalleHab->ant=dir->pfinDetalleHab;
   					 			nuevoDetalleHab->sgte=NULL;
   					 			dir->pfinDetalleHab->sgte=nuevoDetalleHab;
							}
		
							dir->pfinDetalleHab=nuevoDetalleHab;
													
						}	
					}else{
						gotoxy(4,34);cout<<"EL PRODUCTO NO ESTA REGISTRADO";
					}
				}else{
					gotoxy(4,34);cout<<"CLIENTE NO ESTA HOSPEDADO";
				}
			}else{
				gotoxy(4,34);cout<<"CLIENTE NO REGISTRADO";
			}	
			gotoxy(4,30);cout<<"REALIZAR OTRA COMPRA Si(1):                ";
			gotoxy(33,30);cin>>resp;
		}while(resp==1);
	}else{
		gotoxy(4,34);cout<<"REGISTRE UN PRODUCTO AL MENOS";
	}
}

CabFactura *buscardetafact(string cedula,CabFactura *pcabFactu){
	CabFactura *direccion=NULL;
	CabFactura *facturaActual=new (CabFactura);
	facturaActual=pcabFactu;
	while(facturaActual!=NULL){
		if(facturaActual->cedula==cedula){
			direccion=facturaActual;
		}	
		facturaActual=facturaActual->sgte;
	}
	return direccion;
}

CabFactura *buscardetafact_codigo(string cedula,CabFactura *pcabFactu){
	CabFactura *direccion=NULL;
	CabFactura *facturaActual=new (CabFactura);
	facturaActual=pcabFactu;
	while(facturaActual!=NULL){
		if(facturaActual->codfact==cedula){
			direccion=facturaActual;
		}	
		facturaActual=facturaActual->sgte;
	}
	return direccion;
}

void Confirmar_reservacion(Persona *&pcabPer,Persona *&pfinPer,Habitacion *&pcabHab,Habitacion *&pfinHab,CabFactura *&pcabFactu,CabFactura *&pfinFactu){
	
	int resp,op;
	string codigo;
	string cedula;
	
	Persona *nuevaPersona=NULL;
	Habitacion *dirHabitacion=NULL;
	Habitacion *anterior;
	int y=4,x=14;
	limpiado_de_pantalla();
	if(pcabHab!=NULL){
		if(pcabPer!=NULL){
			do{
				limpiado_de_pantalla();
				gotoxy(6,13);cout<<"***CONFIRMAR RESERVACIONES***";
				gotoxy(6,15);cout<<"INGRESO DE DATOS PARA CONFIRMAR RESERVACION";
				int op;
				string numerohabitacion;
				gotoxy(6,17);cout<<"Datos del huesped";
				gotoxy(6,19);cout<<"Cedula: ";cin>>cedula;
				nuevaPersona=fun_buscarPersona(cedula,pcabPer);
				if(nuevaPersona!=NULL){
					//Recuperar datos de la persona
					mostrarPersona(nuevaPersona);
					numerohabitacion=nuevaPersona->numero_de_la_habitacion;
					MostrarHab_por_codigo(pcabHab,numerohabitacion,y,x);
					if(nuevaPersona->band!=1){
						gotoxy(4,30);cout<<"Desea CONFIRMAR reservacion Si(1) No(0): ";
						cin>>resp;
						
						if(resp==1){
							dirHabitacion=fun_buscarHabitacion(numerohabitacion,pcabHab);
							nuevaPersona->band=1;
							dirHabitacion->estado=3;
							
							std::time_t t = std::time(0);   // get time now	
   							std::tm* now = std::localtime(&t);
   							int anio=(now->tm_year + 1900);
   							int mes=(now->tm_mon + 1);
   							int dia=now->tm_mday;
			    		
			    			CabFactura *nuevaCabFactura=new (CabFactura);
						
							nuevaCabFactura->cedula=cedula;
							nuevaCabFactura->codfact=cedula;
							nuevaCabFactura->codHab=numerohabitacion;
							nuevaCabFactura->dia=dia;
							nuevaCabFactura->mes=mes;
							nuevaCabFactura->anio=anio;
							nuevaCabFactura->subtotal_fact=0;
							nuevaCabFactura->total_fact=0;
							nuevaCabFactura->valorIva_fact=0;
						
						
							nuevaCabFactura->pcabDetalleHab=NULL;
							nuevaCabFactura->pfinDetalleHab=NULL;
							
							if(pcabFactu==NULL){
								nuevaCabFactura->ant=NULL;
								nuevaCabFactura->sgte=NULL;
								pcabFactu=nuevaCabFactura;
							}else{
								nuevaCabFactura->ant=pfinFactu;
								nuevaCabFactura->sgte=NULL;
								pfinFactu->sgte=nuevaCabFactura;
							}
							pfinFactu=nuevaCabFactura;
						}
					}else{
						cout<<"USTED YA CONFIRMO LA CITA";
					}
				}else{
					cout<<"\nNo cuenta con una reservacion";
				}
				gotoxy(4,30);cout<<"Verificar otra reservacion de otro usuario? Si(1) o No(Cualquier numero): ";
				cin>>resp;
				gotoxy(4,30);cout<<"                                                                                ";
				
			}while(resp==1);
		}else{
			gotoxy(4,35);cout<<"Registre al menos una RESERVACION";
			getch();
			gotoxy(4,35);cout<<"                                       ";
		} 
	}else{
		gotoxy(4,35);cout<<"Registre al menos una habitacion";
		getch();
		gotoxy(4,35);cout<<"                                       ";
	}
}

void Pagar_reservacion(Persona *&pcabPer,Persona *&pfinPer,CabFactura *&pcabFactu,CabFactura *&pfinFactu,Habitacion *&pcabHab){
	
	int resp,op;
	string codigo,codfact;
	string cedula;
	
	float subtotal_fact,valorIva_fact,total_fact;
	Persona *nuevaPersona=NULL;
	limpiado_de_pantalla();
	if(pcabPer!=NULL){
		system("cls");
		marco();
		logo();
		gotoxy(4,30);cout<<"                                       ";
		gotoxy(6,13);cout<<"        PAGAR RESERVACIONES       ";
		gotoxy(4,15);cout<<"INGRESO DE DATOS PARA PAGAR RESERVACION";
		do{
			int op;
			string numerohabitacion;
			system("cls");
			marco();
			logo();
			gotoxy(4,30);cout<<"                                       ";
			gotoxy(4,17);cout<<"DATOS DEL HUESPED";
			gotoxy(4,19);cout<<"CEDULA: ";cin>>cedula;
			nuevaPersona=fun_buscarPersona(cedula,pcabPer);
			if(nuevaPersona!=NULL){
				if(nuevaPersona->band==1){
					numerohabitacion=nuevaPersona->numero_de_la_habitacion;
					gotoxy(4,30);cout<<"DESEA REALIZAR LA FACTURACION SI(1)  NO(0): ";cin>>resp;
					system("cls");
					marco();
					logo();
					if(resp==1){
						
						gotoxy(30,10);cout<<"DATOS PARA LA FACTURA";
						gotoxy(4,15);cout<<"CODIGO: ";cin>>codfact;
						gotoxy(4,17);cout<<"FECHA DE FACTURACION: ";
						
						std::time_t t = std::time(0);   // get time now	
   						std::tm* now = std::localtime(&t);
   						int anio=(now->tm_year + 1900);
   						int mes=(now->tm_mon + 1);
   						int dia=now->tm_mday;
			    		std::cout<<dia<<'-'<<mes<<'-'<<anio<<"\n";
						CabFactura *aux=NULL;
						
						aux=buscardetafact(cedula,pcabFactu);
						
						aux->codfact=codfact;						
					}
				}else{
					gotoxy(4,29);cout<<"USTED NO HA CONFIRMADO LA CITA";
				}
			}else{
				gotoxy(4,29);cout<<"No cuenta con una reservacion";
			}
				gotoxy(4,30);cout<<"Verificar otra reservacion de otro usuario? Si(1) oNo(Cualquier numero): ";cin>>resp;
				getch();
				gotoxy(4,30);cout<<"                                                                           ";
		}while(resp==1);
	}else{
		gotoxy(4,29);cout<<"*** Registre almenos una habitacion ***";
		getch();
		gotoxy(4,29);cout<<"                                       ";
	}   
}
void Mostrar_factura_codigo(CabFactura *aux,Persona *pcabPer,Habitacion *&pcabHab){
	string cedula;
	cedula=aux->cedula;
	string codigo;
	codigo=aux->codHab;
	float valor,total;
	int resp;
	//marco();
	logo();
	gotoxy(4,13);cout<<"FACTURA: ";
	gotoxy(4,14);cout<<"CODIGO: "<<aux->codfact;
	Persona *actualPersona=NULL;
	actualPersona=fun_buscarPersona(cedula,pcabPer);
	mostrarPersona(actualPersona);
	
	Habitacion *actualHabitacion=NULL;
	actualHabitacion=fun_buscarHabitacion(codigo,pcabHab);

	gotoxy(40,13);cout<<"DETALLE DE HABITACION";
	gotoxy(40,14);cout<<"NUMERO DE HABITACION: "<<actualHabitacion->codigo;
	valor=((actualHabitacion->iva)*(actualHabitacion->precio_base))+(actualHabitacion->precio_base)+((actualHabitacion->precio_base)*(actualHabitacion->tasa));
	gotoxy(40,15);cout<<"TIPO DE HABITACION: ";
	if(actualHabitacion->tipodeHabitacion==1){
	     gotoxy(60,15);cout<<" Simple";
	}
	if(actualHabitacion->tipodeHabitacion==2){
		gotoxy(60,15);cout<<" Matrimonial";
	}
	if(actualHabitacion->tipodeHabitacion==3){
		gotoxy(60,15);cout<<" Multiple";
	}
	gotoxy(40,16);cout<<"PRECIO BASE: "<<actualHabitacion->precio_base;
	gotoxy(40,17);cout<<"IVA: "<<actualHabitacion->iva;
	gotoxy(40,18);cout<<"TASA: "<<actualHabitacion->tasa;
	gotoxy(40,19);cout<<"VALOR A PAGAR: "<<valor;
	
	gotoxy(4,20);cout<<"DETALLE DE COMPRAS EN EL BAR";
	//================================================================	
	listarDetalles(aux,total);
	cout<<endl;
	gotoxy(4,30);cout<<"VALOR TOTAL A PAGAR: "<<(valor+total);
	cout<<endl;
	//================================================================	
	cout<<endl;
}


void Mostrar_factura(CabFactura *aux,Persona *pcabPer,Habitacion *&pcabHab){
	string cedula;
	cedula=aux->cedula;
	string codigo;
	codigo=aux->codHab;
	float valor,total;
	int resp;
	
	Persona *actualPersona=NULL;
	actualPersona=fun_buscarPersona(cedula,pcabPer);
	mostrarPersona(actualPersona);
	
	Habitacion *actualHabitacion=NULL;
	actualHabitacion=fun_buscarHabitacion(codigo,pcabHab);
	system("cls");
	logo();
	marco();
	
    gotoxy(40,13);cout<<"DETALLE DE HABITACION";
	gotoxy(40,14);cout<<"NUMERO DE HABITACION: "<<actualHabitacion->codigo;
	valor=((actualHabitacion->iva)*(actualHabitacion->precio_base))+(actualHabitacion->precio_base)+((actualHabitacion->precio_base)*(actualHabitacion->tasa));
	gotoxy(40,15);cout<<"TIPO DE HABITACION: ";
	if(actualHabitacion->tipodeHabitacion==1){
	     gotoxy(60,15);cout<<" Simple";
	}
	if(actualHabitacion->tipodeHabitacion==2){
		gotoxy(60,15);cout<<" Matrimonial";
	}
	if(actualHabitacion->tipodeHabitacion==3){
		gotoxy(60,15);cout<<" Multiple";
	}
	gotoxy(40,16);cout<<"PRECIO BASE: "<<actualHabitacion->precio_base;
	gotoxy(40,17);cout<<"IVA: "<<actualHabitacion->iva;
	gotoxy(40,18);cout<<"TASA: "<<actualHabitacion->tasa;
	gotoxy(40,19);cout<<"******VALOR A PAGAR: "<<valor;
	gotoxy(4,20);cout<<"**********************DETALLE DE COMPRAS EN EL VAR*************************";
	//================================================================	
	listarDetalles(aux,total);
	cout<<endl;
	gotoxy(4,30);cout<<"VALOR TOTAL A PAGAR: "<<(valor+total);
	
	//================================================================
	gotoxy(4,33);cout<<"Realizar PAGO Si(1) No(0): ";
	cin>>resp;
	if(resp==1){// SE LIBERA LA HABITACIO A ESTAR DISPONIBLE CON ESTADO 1
		actualHabitacion->estado=1;
	}
}


void listarDetalles(CabFactura *aux,float &total){
	DetalleHab *nuevoDetalleHab;
	nuevoDetalleHab=aux->pcabDetalleHab;
	int cont=1,j=22;
	float subtotal=0;
	
	gotoxy(4,21);cout<<"Cant";
	gotoxy(11,21);cout<<"Codigo";
	gotoxy(22,21);cout<<"Descripcion";
	gotoxy(43,21);cout<<"Precio U.";
	gotoxy(56,21);cout<<"IVA";
	gotoxy(64,21);cout<<"Subtotal \n";
	
	while(nuevoDetalleHab!=NULL){
		
		gotoxy(4,j);cout<<nuevoDetalleHab->cantidad;
		gotoxy(11,j);cout<<nuevoDetalleHab->codigoProduct;
		gotoxy(22,j);cout<<nuevoDetalleHab->descripcion;
		gotoxy(43,j);cout<<nuevoDetalleHab->precio;
		gotoxy(56,j);cout<<nuevoDetalleHab->iva;
		gotoxy(64,j);cout<<nuevoDetalleHab->subtotal<<endl;
		subtotal=(nuevoDetalleHab->subtotal)+subtotal;
		total=((nuevoDetalleHab->subtotal)+((nuevoDetalleHab->subtotal)*(nuevoDetalleHab->iva)))+total;
		
		nuevoDetalleHab=nuevoDetalleHab->sgte;
		cont++;
		j++;
	}
	gotoxy(40,26);cout<<"Subtotal: "<<subtotal<<endl;
	gotoxy(40,27);cout<<"Total: "<<total;
}

void limpiado_de_pantalla(){
	int i,j;
	for(i=12; i<27; i++)
	{
		for(j=3; j<80; j++)
		{
			gotoxy(j,i);printf(" ");
		}
	}
}

void limpiado_de_lineas(int f, int g)
{
	for(f=5; f<80; f++)
	{
		gotoxy(f,g);printf(" ");
	}
}
void chao(){
	int i,j;
	for(j=1;j<=32;j++)
	{
		for(i=1;i<=80;i++)
		{
			gotoxy(i,j);printf(" ");
		}
	}
	//system("color 70");
	gotoxy(5,3);printf("                                         ******* ****** ****** ****** * ****** ******              ");
	gotoxy(5,4);printf("                                         *       *    * *    * *      * *    * *");
	gotoxy(5,5);printf("                                         ******* *****  ****** *      * ****** ****** ");
	gotoxy(5,6);printf("                                         *     * *   *  *    * *      * *    *      * ");
	gotoxy(5,7);printf("                 ________                ******* *    * *    * ****** * *    * ******         ");
	gotoxy(5,8);printf("                /_HOTEL_/|                                                  ______");
	gotoxy(5,9);printf("         ______| _   _ | | ________	   ******  ******  ******     /______/|");
	gotoxy(5,10);printf("       /______||_| |_|| |/_______/|           *    *  *    *  *    *    |       ||");
	gotoxy(5,11);printf("      | _   _ | _   _ | | _   _ | |           *****   *    *  *****     | ^   ^ ||");
	gotoxy(5,12);printf("      ||_| |_|||_| |_|| ||_| |_|| |           *       *    *  *    *    | :___: ||");
	gotoxy(5,13);printf("      | _   _ | _   _ | | _   _ | |           *       ******  *     *   |_______|/ ");
	gotoxy(5,14);printf("      ||_| |_|||_| |_|| ||_| |_|| |               ");
	gotoxy(5,15);printf("      |_______|       | |_______|/                ");
	gotoxy(5,16);printf("              |_______|/                      ***** *      ***** ***** * ***** *    * ***** *****    ");
	gotoxy(5,17);printf("                                              *     *      *     *     * *   * * *  * *   * *");
	gotoxy(5,18);printf("     %c%c%c    %c%c %c%c%c%c  %c%c %c%c%c%c                  ****  *      ****  ***** * ****  *  * * *   * *****",126,126,126,126,126,126,126,126,126,126,126,126,126,126,126);
	gotoxy(5,19);printf("  %c%c%c    %c%c %c%c%c%c  %c%c %c%c%c%c                     *     *      *     *   * * *  *  *   ** *   *     *   ",126,126,126,126,126,126,126,126,126,126,126,126,126,126,126);
	gotoxy(5,20);printf("%c%c%c    %c%c %c%c%c%c  %c%c %c%c%c%c                       ***** ****** ***** ***** * *   * *    * ***** ***** ",126,126,126,126,126,126,126,126,126,126,126,126,126,126,126);
	Beep(1000, 900);
}

 void reloj()
{
	time_t now = time(0); // fecha/hora actual basado en el sistema actual
	tm * time = localtime(&now); // Objeto de una estructura tm
	//Formato=dia/mes/año     el mes comienza en 0 por eso se suma +1  y y el año se le suma 1900 sino saldria 118
	gotoxy(4,6);printf("%d/ %d/ %d", time->tm_mday, (1+time->tm_mon), (1900+time->tm_year));
	gotoxy(4,7);printf("%d: %d: %d ", time->tm_hour, time->tm_min, time->tm_sec);
}

void marco(){
	logo();
	int i,j;
	for(i=1;i<=35;i++)
	{
		if(i>=1 && i<=8)//PERMITE DIBUJAR LA SEGUNDA LINEA VERTICAL DERECHA
		{
			gotoxy(17,i);printf("%c",219);
		}
		if(i<=8)//PERMITE DIBUJAR LA TERCERA LINEA VERTICAL DERECHA
		{
			gotoxy(82,i);printf("%c",219);
		}
		gotoxy(1,i);printf("%c",219); //PERMITE DIBUJAR UNA LINEA VERTICAL IZQUIERDA j columna q aora es 1
		gotoxy(100,i);printf("%c",219);//PERMITE DIBUJAR UNA LINEA VERTICAL DERECHA  j columna q aora es 80
	}
	//logo TI
	gotoxy(86,2);printf("%c%c%c%c%c%c  %c%c",205,205,205,205,205,205,205,205);
	for(i=2;i<=7;i++){
		gotoxy(88,i);printf("%c%c",205,205);
		gotoxy(94,i);printf("%c%c",205,205);
		if(i<=4){
			gotoxy(28,(i+6));printf("%c",219);	
			gotoxy(70,(i+6));printf("%c",219);	
		}
	}
	for(j=2;j<=99;j++)
		{
			if(j>=2 && j<=16)//PERMITE DIBUJAR LA HORIZONTAL DEL CUADRO DEL RELOJ
			{
				gotoxy(j,4);printf("%c",220);		
			}
		  	gotoxy(j,1);printf("%c",223);//PERMITE DIBUJAR UNA LINEA HORIZONTAL SUPERIOR
			gotoxy(j,8);printf("%c",220);//PERMITE DIBUJAR UNA LINEA HORIZONTAL INTERNA		
			gotoxy(j,11);printf("%c",220);//PERMITE DIBUJAR UNA LINEA HORIZONTAL INTERNA
			gotoxy(j,28);printf("%c",220); // SEGUNDA LINEA INTERNNA
			gotoxy(j,32);printf("%c",220); //TERCERA LINEA INTERNA
			gotoxy(j,35);printf("%c",220);//PERMITE DIBUJAR UNA LINEA HORIZONTAL INFERIOR
		}
	gotoxy(4,30);cout<<"Elija su opcion:                         ";
}

void logo(){
	gotoxy(5,3);printf("HOLTEL:");
	gotoxy(22,2);printf("°°°°° °  °    °°°   °°°°  °°°° °°°°  °°  °   ° °°°° °°°°");
	gotoxy(22,3);printf("  °   °  °    °  °  °     °    °    °  ° °°  ° °    °  ° ");
	gotoxy(22,4);printf("  °   °  °    °   ° °°°°  °°°° °    °°°° ° ° ° °°°° °  ° ");
	gotoxy(22,5);printf("  °   °  °    °  °  °        ° °    °  ° °  °°    ° °  ° ");
	gotoxy(22,6);printf("  °   °°°°    °°°   °°°°  °°°° °°°° °  ° °   ° °°°° °°°°");
}

void logo1(){
	gotoxy(39,12);printf("      OOOO CCCC U  U PooP  A   DDD  OOOO  ");
    gotoxy(39,13);printf("      O  O C    U  U PooP A A  D  D O  O  ");
    gotoxy(39,14);printf("      OOOO CCCC UUUU P   A   A DDD  OOOO  ");
}
void bor(){
	gotoxy(4,12);cout<<"                             ";
	gotoxy(4,13);cout<<"                             ";
	gotoxy(4,14);cout<<"                             ";
	gotoxy(4,15);cout<<"                             ";
	gotoxy(4,16);cout<<"                             ";
	gotoxy(4,17);cout<<"                             ";
}

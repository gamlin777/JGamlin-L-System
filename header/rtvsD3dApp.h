////////////////////////////////////////////////////////////////////////////////




// ---------- rtvsD3dApp.h ----------

/*!

\file rtvsD3dWinLite.h
\brief interface for the rtvsD3dApp class
\author Gareth Edwards

*/


#ifndef _rtvsD3dApp_
#define _rtvsD3dApp_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// ---------- include ----------

#include <windows.h>
#include <stdio.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "../header/L_System.h"
#include "../header/vector.h"
#include <list>

////////////////////////////////////////////////////////////////////////////////




// ---------- FVF - Flexible Vertex Format ----------

struct Vertex
{
    float x , y, z;
 
    enum FVF
    {
        FVF_Flags = D3DFVF_XYZ
    };
};




// ---------- rtvsD3dApp class interface ----------


class rtvsD3dApp  
{

	// ---- properties ----
	L_System LSystem;

	DWORD	_id;


public:


	// ---- properties ----

	ID3DXFont*				pFont;
	D3DCOLOR				fontCol;
	LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;
	D3DMATERIAL9			lineMtrl;
	D3DLIGHT9				sunLight;
	D3DLIGHT9				backLight;
	DWORD					currentKeyClicked;
	DWORD					previousKeyClicked;
	float					fSpinX;
	float					fSpinY;
	char*					vectorName;
	bool					z_pressed;
	bool					x_pressed;
	float					length;
	bool					ctrl_pressed;
	bool					shift_pressed;
	float					angle;
	bool					space_pressed;
	float					rdn;
	float					reset_angle;
	bool					w_pressed;
	bool					a_pressed;
	bool					s_pressed;
	bool					d_pressed;
	float					ls_transX;
	float					ls_transY;
	float					ls_transZ;
	bool					q_pressed;
	bool					e_pressed;

	// ---- methods ----

	// constructor/destructor
	rtvsD3dApp (int);


	// framework
	bool cleanup	();
	bool cleanupDX	(LPDIRECT3DDEVICE9);
	bool display	(LPDIRECT3DDEVICE9);
	bool setup		();
	bool setupDX	(LPDIRECT3DDEVICE9);

	// update vertex buffer
	DWORD updateVertexBuffer (Vertex, Vertex);
	
	// gui
	bool updateKeyboard();

	// other
	void getSpin	(float*, float*);
	void setSpin	(float, float);

};




////////////////////////////////////////////////////////////////////////////////




#endif // _rtvsD3dApp_





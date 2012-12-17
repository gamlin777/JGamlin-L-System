////////////////////////////////////////////////////////////////////////////////




// ---------- rtvsD3dApp.cpp ----------

/*!

\file rtvsD3dApp.cpp
\brief Implementation of the rtvsD3dApp class
\author Gareth Edwards

*/




// ---------- include ----------

#include "../header/rtvsD3dApp.h"
#include <vector>
#include <stack>
using namespace std;


////////////////////////////////////////////////////////////////////////////////




// ---------- constructor ----------

/*!

\brief constructor
\author Gareth Edwards

\param int (id of this instance)


*/

rtvsD3dApp::rtvsD3dApp (int id)
{

	// initialise
    ZeroMemory( this, sizeof(rtvsD3dApp) );

	// store id
	_id = id;
	LSystem = L_System();
	// key clicked
	currentKeyClicked = 5;
	// initializing modifiable parameters
	length = 0.06f;
	rdn = 3.141592f / 180.0f;
	angle = rdn*LSystem.getTurnValue();
	ls_transX = 0.0f;
	ls_transY = 0.0f;
	ls_transZ = 20.0f;
	//text output to screen
	vectorName = "A Simple L-System by James Gamlin\n__________________________________\n                   Controls:\nCycle Iterations(Growth)= Number Keys \n      n.b for the Axiom/Origin press Zero\nChange L-System(Plant) = F1 to F6\nMove Around = W,A,S,D\nZoom In/Out = Q/E \nIncrease/Decrease Branch Angle = Shift/Ctrl\nIncrease/Decrease Branch Size = Z/X\nFree Translate(Irreversible) = Mouse\n       Reset = SPACEBAR\n__________________________________";
}

////////////////////////////////////////////////////////////////////////////////




// ---------- framework ----------




// ---------- framework : cleanup ----------

/*!

\brief framework : cleanup
\author Gareth Edwards

\return bool (TRUE if ok)

*/

bool rtvsD3dApp::cleanup ()
{

	// ok
	return true;

}




// ---------- framework : cleanup dx ----------

/*!

\brief framework : cleanup dx
\author Gareth Edwards

\param LPDIRECT3DDEVICE9	(device)

\return bool (TRUE if ok)

*/

bool rtvsD3dApp::cleanupDX (LPDIRECT3DDEVICE9 pd3dDevice)
{

     // ---- invalidate the font object ----

    if( pFont != NULL )
    {
        int nNewRefCount = pFont->Release();

        if( nNewRefCount > 0 )
        {
            static char strError[256];
            sprintf_s ( strError, 256,
				"The font object failed to cleanup properly.\n"
                "Release() returned a reference count of %d",
				nNewRefCount );
            MessageBox( NULL, strError, "ERROR", MB_OK | MB_ICONEXCLAMATION );
        }

        pFont = NULL;
    }


    // ---- invalidate the vertex buffer object ----

    if( pVertexBuffer != NULL )
    {
        int nNewRefCount = pVertexBuffer->Release();

        if( nNewRefCount > 0 )
        {
            static char strError[256];
            sprintf_s ( strError, 256,
				"The vertex buffer object failed to cleanup properly.\n"
                "Release() returned a reference count of %d",
				nNewRefCount );
            MessageBox( NULL, strError, "ERROR", MB_OK | MB_ICONEXCLAMATION );
        }
        pVertexBuffer = NULL;
    }


	// ok
	return true;

}




// ---------- framework : display ----------

/*!

\brief framework : display
\author Gareth Edwards

\param LPDIRECT3DDEVICE9	(device)

\return bool (TRUE if ok)

*/

bool rtvsD3dApp::display (LPDIRECT3DDEVICE9 pd3dDevice)
{

 	// clear backbuffers
    pd3dDevice->Clear( 0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_COLORVALUE(0.0f,0.0f,0.0f,1.0f),
		1.0f,
		0);

   // local matrices
    D3DXMATRIX matView;
    D3DXMATRIX matRotation;
    D3DXMATRIX matTranslation;
    D3DXMATRIX matWorld;


	// display flag
	bool lines = true;


	// view matrix
    D3DXMatrixIdentity( &matView );
    pd3dDevice->SetTransform( D3DTS_VIEW, &matView );


	// rotation matrix
	D3DXMatrixRotationYawPitchRoll	( &matRotation, D3DXToRadian(fSpinX), D3DXToRadian(fSpinY), 0 );


	// set render states
	pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	// locate
	D3DXMatrixTranslation( &matTranslation, ls_transX, ls_transY, ls_transZ ); // use to move the L-System and zoom
	matWorld = matRotation * matTranslation;
	pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );


	// IF lines THEN
	if (lines)
	{

		// set draw parameters
		pd3dDevice->SetTexture( 0, 0 );
		pd3dDevice->SetStreamSource( 0, pVertexBuffer, 0, sizeof(Vertex) );
		pd3dDevice->SetFVF( Vertex::FVF_Flags );
		pd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		pd3dDevice->SetMaterial( &lineMtrl );

		// update key clicked
		updateKeyboard();

		
		Vertex s, e;
		reset_angle = LSystem.TURN_VALUE*rdn; //for the reset button
		
		
		stack <Vector3D> mainpos;
		stack <float> anglepos;
		
		string axiom = LSystem.getAxiom();
		string str = axiom; // the main string for holding the re-written production rules
		char *c_axiom;
		c_axiom = &axiom[0];
		string node = LSystem.getNode();
		char *c_node;
		c_node = &node[0];
		
		// handling the rules
		struct Rule
		{
			char from[1];
			string to;
		};

		Rule r;
		Rule r2;
		r.from[0] = *c_axiom;
		r.to = LSystem.getRule();
		r2.from[0] = *c_node;
		r2.to = LSystem.getNodeRule();

		std::vector<Rule> rList;
		rList.push_back(r);
		rList.push_back(r2);

			
			float current_angle = 0.0f; // initialized as 0.0f for the initial straight line
			float sin_angle = sin(current_angle);
			float cos_angle = cos(current_angle);
			Vector3D direction = Vector3D(sin_angle*length, cos_angle*length,0);
			Vector3D currentpos = Vector3D(4,-7,0);
			int max_iterations = LSystem.getIterations(); // is set up as maximum for demo purposes, but can be changed to show different iterations
			int default_iterations = LSystem.getIterations(); // is specific to each L-system example

			//Handles the iteration selection
			if (currentKeyClicked == 1){
				if (1 <= default_iterations){
					max_iterations = 1;
				}
			}
			if (currentKeyClicked == 2){
				if (2 <= default_iterations){
					max_iterations = 2;
				}
			}
			if (currentKeyClicked == 3){
				if (3 <= default_iterations){
					max_iterations = 3;
				}
			}
			if (currentKeyClicked == 4){
				if (4 <= default_iterations){
					max_iterations = 4;
				}
			}
			if (currentKeyClicked == 5){
				if (5 <= default_iterations){
					max_iterations = 5;
				}
			}
			if (currentKeyClicked == 6){
				if (6 <= default_iterations){
					max_iterations = 6;
				}
			}
			if (currentKeyClicked == 7){
				if (7 <= default_iterations){
					max_iterations = 7;
				}
			}
			if (currentKeyClicked == 8){
				if (8 <= default_iterations){
					max_iterations = 8;
				}
			}
			if (currentKeyClicked == 9){
				if (9 <= default_iterations){
					max_iterations = 9;
				}
			}
			if (currentKeyClicked == 0){
					max_iterations = 0;
			}
		// Generates the productions rules each frame
		for (int k = 0; k < max_iterations; ++k){
			for (int i = str.length() - 1; i >= 0; --i){
				for (int j = 0; j < rList.size(); j++){
					if (str[i] == *rList[j].from){
						str.replace(i, 1, rList[j].to);
					}
				}
			}
		}
		//Generating the lines based on the production characters
		for (int i = 0; i < str.length(); i++){
			if (str[i] == 'F'){
						s.x = currentpos.x;
						s.y = currentpos.y;
						s.z = currentpos.z;

						e.x = s.x + direction.x;
						e.y = s.y + direction.y;
						e.z = s.z + direction.z;

						currentpos.x = e.x;
						currentpos.y = e.y;
						currentpos.z = e.z;
						updateVertexBuffer(s, e);
					} else if (str[i] == 'f'){
						s.x = currentpos.x;
						s.y = currentpos.y;
						s.z = currentpos.z;

						e.x = s.x + direction.x;
						e.y = s.y + direction.y;
						e.z = s.z + direction.z;

						currentpos.x = e.x;
						currentpos.y = e.y;
						currentpos.z = e.z;
					} else if (str[i] == 'X'){
						s.x = currentpos.x;
						s.y = currentpos.y;
						s.z = currentpos.z;

						e.x = s.x + direction.x;
						e.y = s.y + direction.y;
						e.z = s.z + direction.z;

						currentpos.x = e.x;
						currentpos.y = e.y;
						currentpos.z = e.z;
						updateVertexBuffer(s, e);
					} else if (str[i] == 'x'){
						s.x = currentpos.x;
						s.y = currentpos.y;
						s.z = currentpos.z;

						e.x = s.x + direction.x;
						e.y = s.y + direction.y;
						e.z = s.z + direction.z;

						currentpos.x = e.x;
						currentpos.y = e.y;
						currentpos.z = e.z;
					} else if (str[i] == '+'){
						current_angle += -angle;
						cos_angle = cos(current_angle);
						sin_angle = sin(current_angle);
						direction.x = sin_angle*length;
						direction.y = cos_angle*length;
					} else if (str[i] =='-'){
						current_angle += angle;
						cos_angle = cos(current_angle);
						sin_angle = sin(current_angle);
						direction.x = sin_angle*length;
						direction.y = cos_angle*length;
					} else if (str[i] == '['){
						mainpos.push(direction);
						mainpos.push(currentpos);
						anglepos.push(current_angle);
					} else if (str[i] == ']'){
						current_angle = anglepos.top();
						anglepos.pop();
						currentpos = mainpos.top();
						mainpos.pop();
						direction = mainpos.top();
						mainpos.pop();
					}

					pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, 1 );
				}
			// pd3dDevice->DrawPrimitive( D3DPT_LINELIST, 0, 1 );
			// updateVertexBuffer(s, e);
			RECT rect = { 20, 20, 1000, 1000 };
			pFont->DrawText(0,vectorName,-1,&rect,0,fontCol);
		
		//manipulation of the l_system
		if (z_pressed == true){
			length += 0.001f;
		}
		if (x_pressed == true){
			length -= 0.001f;
		}
		if (shift_pressed == true){
			angle += 0.1f;
		}
		if (ctrl_pressed == true){
			angle -= 0.1f;
		}
		if (space_pressed == true){
			angle = reset_angle;
			ls_transX = 0.0f;
			ls_transY = 0.0f;
			ls_transZ = 20.0f;
			length = 0.06f;
		}
		if (w_pressed == true){
			ls_transY -= 0.1f;
		}
		if (s_pressed == true){
			ls_transY += 0.1f;
		}
		if (a_pressed == true){
			ls_transX += 0.1f;
		}
		if (d_pressed == true){
			ls_transX -= 0.1f;
		}
		if (q_pressed == true){
			ls_transZ -= 0.1f;
		}
		if (e_pressed == true){
			ls_transZ += 0.1f;
		}

	} // if lines

	return true;

} // Display




// ---------- framework : setup ----------

/*!

\brief framework : setup
\author Gareth Edwards

\return bool (TRUE if ok)

*/

bool rtvsD3dApp::setup ()
{

    // setup a material for the lines
    ZeroMemory( &lineMtrl, sizeof(D3DMATERIAL9) );
	lineMtrl.Emissive.r = 1.0f;
	lineMtrl.Emissive.g = 1.0f;
	lineMtrl.Emissive.b = 1.0f;

    // setup directional sun light
	ZeroMemory( &sunLight, sizeof(D3DLIGHT9) );
	sunLight.Type = D3DLIGHT_DIRECTIONAL;
    sunLight.Direction = D3DXVECTOR3( -1.0f, -1.0f,  1.0f );
    sunLight.Diffuse.r = 1.0f;
    sunLight.Diffuse.g = 1.0f;
    sunLight.Diffuse.b = 1.0f;
    sunLight.Diffuse.a = 1.0f;
    sunLight.Specular.r = 1.0f;
    sunLight.Specular.g = 1.0f;
    sunLight.Specular.b = 1.0f;
    sunLight.Specular.a = 1.0f;

    // setup directional back light
	ZeroMemory( &backLight, sizeof(D3DLIGHT9) );
	backLight.Type = D3DLIGHT_DIRECTIONAL;
    backLight.Direction = D3DXVECTOR3( 1.0f,  0.0f,  0.0f );
    backLight.Diffuse.r = 1.0f;
    backLight.Diffuse.g = 0.2f;
    backLight.Diffuse.b = 0.5f;
    backLight.Diffuse.a = 1.0f;
    backLight.Specular.r = 0.3f;
    backLight.Specular.g = 0.3f;
    backLight.Specular.b = 0.3f;
    backLight.Specular.a = 1.0f;

	// ok
	return true;

}




// ---------- framework : setup dx ----------

/*!

\brief framework : setup dx
\author Gareth Edwards

\param LPDIRECT3DDEVICE9	(device)

\return bool (TRUE if ok)

*/

bool rtvsD3dApp::setupDX (LPDIRECT3DDEVICE9 pd3dDevice)
{

	// ---- turn lighting ON ----
	pd3dDevice->SetRenderState( D3DRS_LIGHTING , TRUE);


	// ---- ambient light ----
	pd3dDevice->SetRenderState( D3DRS_AMBIENT,D3DCOLOR_COLORVALUE( 0.3, 0.3, 0.3, 1.0));


	// ---- sun light ----
    pd3dDevice->SetLight( 0, &sunLight );
    pd3dDevice->LightEnable( 0, TRUE );


	// ---- back light ----
	pd3dDevice->SetLight( 1, &backLight );
    pd3dDevice->LightEnable( 1, TRUE );


	// ---- FONT ----

	fontCol = D3DCOLOR_COLORVALUE(1,1,1,1);
	D3DXCreateFont(
		pd3dDevice,
		20,								// height in pixels
		0,								// width in pixels (0 for default)
		400,							// thickness, 0-1000 OR FW_THIN (100), FW_NORMAL (400), FW_BOLD (700), FW_HEAVY (900)
		0,								// number of MipMaps to create. 0 creates a full chain - no scaling use 1
		false,							// 0/1 - true/false, do you want Italics
		DEFAULT_CHARSET,				// character Set - (Arabic, Greek, etc)
		OUT_DEFAULT_PRECIS,				// how precisely the output must match the font
		ANTIALIASED_QUALITY,			// ANTIALIASED_QUALITY, DEFAULT_QUALITY, DRAFT_QUALITY, and PROOF_QUALITY
		DEFAULT_PITCH | FF_DONTCARE,	// font pitch 
		"Verdana",					// name of the required font or "" for system best match
		&pFont);


	// ---- LINE ----


	// ---- initialise vertex data ----
 	Vertex vertices[] =
	{
		//    x      y      z
		{  0.0f,  0.0f,  0.0f  },
		{  0.0f,  0.0f,  0.0f  },
	};

	// ---- create vertex buffer ----
	int numVertices = sizeof(vertices) / ( sizeof(float) * 3 );
	int numLines = numVertices / 2;
	pd3dDevice->CreateVertexBuffer( numVertices*sizeof(Vertex),
                                      D3DUSAGE_WRITEONLY,
                                      Vertex::FVF_Flags,
                                      //D3DPOOL_MANAGED, // does not have to be properly Released before calling IDirect3DDevice9::Reset
                                      D3DPOOL_DEFAULT,   // must be Released properly before calling IDirect3DDevice9::Reset
                                      &pVertexBuffer, NULL );

	// ---- block copy into vector vertex buffer ----
	void* pVertices = NULL;
	pVertexBuffer->Lock( 0, sizeof(vertices), (void**)&pVertices, 0 );
	memcpy( pVertices, vertices, sizeof(vertices) );
	pVertexBuffer->Unlock();


	// ok
	return true;

}




////////////////////////////////////////////////////////////////////////////////




// ---------- update vertex buffer ----------

/*!

\brief line - update vertex buffer
\author Gareth Edwards

\param 

\return bool (TRUE)

*/

DWORD rtvsD3dApp::updateVertexBuffer(Vertex s, Vertex e)
{

	// ---- update vector vertex buffer ----
	Vertex *pVertices = NULL;
	pVertexBuffer->Lock( 0, sizeof(Vertex) * 6, (void**)&pVertices, 0 );
	pVertices->x = (float)s.x;
	pVertices->y = (float)s.y;
	pVertices->z = (float)s.z;
	pVertices++;
	pVertices->x = (float)e.x;
	pVertices->y = (float)e.y;
	pVertices->z = (float)e.z;
	pVertexBuffer->Unlock();

	// ok
	return 1;
}



// ---------- update keyboard ----------

/*!

\brief update keyboard
\author Gareth Edwards

\param rtvsD3dSdk::stage* (pointer to RTVS Stage)

\return bool (TRUE if key updated)

*/

bool rtvsD3dApp::updateKeyboard ()
{

	// get key clicked
	if(GetAsyncKeyState('1') & 0x8000f)
		currentKeyClicked = 1;
	else if(GetAsyncKeyState('2') & 0x8000f)
		currentKeyClicked = 2;
	else if(GetAsyncKeyState('3') & 0x8000f)
		currentKeyClicked = 3;
	else if(GetAsyncKeyState('4') & 0x8000f)
		currentKeyClicked = 4;
	else if(GetAsyncKeyState('5') & 0x8000f)
		currentKeyClicked = 5;
	else if(GetAsyncKeyState('6') & 0x8000f)
		currentKeyClicked = 6;
	else if(GetAsyncKeyState('7') & 0x8000f)
		currentKeyClicked = 7;
	else if(GetAsyncKeyState('8') & 0x8000f)
		currentKeyClicked = 8;
	else if(GetAsyncKeyState('9') & 0x8000f)
		currentKeyClicked = 9;
	else if(GetAsyncKeyState('0') & 0x8000f)
		currentKeyClicked = 0;		
	if (GetAsyncKeyState(0x70) & 0x8000f){ // F1
		LSystem.load(1);
	}else if (GetAsyncKeyState(0x71) & 0x8000f){ // F2
		LSystem.load(2);
	}else if (GetAsyncKeyState(0x72) & 0x8000f){ // F3
		LSystem.load(3);
	}else if (GetAsyncKeyState(0x73) & 0x8000f){ // F4
		LSystem.load(4);
	}else if (GetAsyncKeyState(0x74) & 0x8000f){ // F5
		LSystem.load(5);
	}else if (GetAsyncKeyState(0x75) & 0x8000f){ // F6
		LSystem.load(6);
	}
	if (GetAsyncKeyState(0x5A) & 0x8000f){ // z
		z_pressed = true;
	}else{
		z_pressed = false;
	}
	if (GetAsyncKeyState(0x58) & 0x8000f){ // x
		x_pressed = true;
    }else{
		x_pressed = false;
	}
	if (GetAsyncKeyState(0x10) & 0x8000f){ // shift
		shift_pressed = true;
	}else{
		shift_pressed = false;
	}
	if (GetAsyncKeyState(0x11) & 0x8000f){ // ctrl
		ctrl_pressed = true;
	}else{
		ctrl_pressed = false;
	}
	if (GetAsyncKeyState(0x20) & 0x8000f){ // SPACEBAR
		space_pressed = true;
	}else{
		space_pressed = false;
	}
	if (GetAsyncKeyState(0x57) & 0x8000f){ // w
		w_pressed = true;
	}else{
		w_pressed = false;
	}
	if (GetAsyncKeyState(0x41) & 0x8000f){ // a
		a_pressed = true;
	}else{
		a_pressed = false;
	}	
	if (GetAsyncKeyState(0x53) & 0x8000f){ // s
		s_pressed = true;
	}else{
		s_pressed = false;
	}	
	if (GetAsyncKeyState(0x44) & 0x8000f){ // d
		d_pressed = true;
	}else{
		d_pressed = false;
	}	
	if (GetAsyncKeyState(0x51) & 0x8000f){ // q
		q_pressed = true;
	}else{
		q_pressed = false;
	}	
	if (GetAsyncKeyState(0x45) & 0x8000f){ // e
		e_pressed = true;
	}else{
		e_pressed = false;
	}	
	return true;
}


	
	
////////////////////////////////////////////////////////////////////////////////




// ---------- getSpin ----------

/*!

\brief get x and y spin 
\author Gareth Edwards
\param float* ([out] spin around x axis)
\param float* ([out] spin around y axis)

*/

void rtvsD3dApp::getSpin (float* spinX, float* spinY)
{
	*spinX = fSpinX;
	*spinY = fSpinY;
}




// ---------- setSpin ----------

/*!

\brief set x and y spin 
\author Gareth Edwards
\param float (spin around x axis)
\param float (spin around y axis)

*/

void rtvsD3dApp::setSpin (float spinX, float spinY)
{
	fSpinX = spinX;
	fSpinY = spinY;
}




////////////////////////////////////////////////////////////////////////////////

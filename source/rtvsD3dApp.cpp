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
    ZeroMemory( this, sizeof(rtvsD3dApp) ); // Comment out later

	// store id
	_id = id;
	LSystem = L_System();
	// key clicked
	currentKeyClicked = 0;

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
		D3DCOLOR_COLORVALUE(1.0f,1.0f,1.0f,1.0f),
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
	D3DXMatrixTranslation( &matTranslation, 0, 0, 20 ); // use to move the L-System and zoom
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

		// select angle of increment from a look up table
		// where the array index == current key clicked


		// draw a line rotating around the z axis
		LSystem = L_System();
		Vertex s, e;
		float rdn = 3.141592f / 180.0f;
		
		stack <Vector3D> mainpos;
		stack <float> anglepos;
		
		string axiom = LSystem.getAxiom();
		string str = axiom;
		char *c_axiom;
		c_axiom = &axiom[0];
		string node = LSystem.getNode();
		char *c_node;
		c_node = &node[0];
		
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

			
			// update start and end vertex

			float length = LSystem.getLength();
			float angle = rdn*LSystem.getTurnValue();
			float current_angle = 0.0f; // for the initial straight line
			

			float sin_angle = sin(current_angle);
			float cos_angle = cos(current_angle);
			Vector3D direction = Vector3D(sin_angle*length, cos_angle*length,0);
			Vector3D currentpos = Vector3D(0,0,0);
			int max_iterations = 0;
			int default_iterations = LSystem.getIterations();
			int current_iteration = 0;

			
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
			
		for (current_iteration = 0; current_iteration < max_iterations; ++current_iteration){
			for (int i = str.length() - 1; i >= 0; --i){
				for (int j = 0; j < rList.size(); j++){
					if (str[i] == *rList[j].from){
						str.replace(i, 1, rList[j].to);
					}
				}
			}
		}
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
	lineMtrl.Emissive.r = 0.0f;
	lineMtrl.Emissive.g = 0.0f;
	lineMtrl.Emissive.b = 0.0f;

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
		30,								// height in pixels
		0,								// width in pixels (0 for default)
		400,							// thickness, 0-1000 OR FW_THIN (100), FW_NORMAL (400), FW_BOLD (700), FW_HEAVY (900)
		0,								// number of MipMaps to create. 0 creates a full chain - no scaling use 1
		false,							// 0/1 - true/false, do you want Italics
		DEFAULT_CHARSET,				// character Set - (Arabic, Greek, etc)
		OUT_DEFAULT_PRECIS,				// how precisely the output must match the font
		ANTIALIASED_QUALITY,			// ANTIALIASED_QUALITY, DEFAULT_QUALITY, DRAFT_QUALITY, and PROOF_QUALITY
		DEFAULT_PITCH | FF_DONTCARE,	// font pitch 
		"Arial",						// name of the required font or "" for system best match
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
	else if (GetAsyncKeyState(0x41) & 0x8000f)
		currentKeyClicked = 0x41;
	else if (GetAsyncKeyState('e') & 0x8000f)
		currentKeyClicked = 'e';			
	// ok
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

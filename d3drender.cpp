/*

	PROJECT:		mod_sa
	LICENSE:		See LICENSE in the top level directory
	COPYRIGHT:		Copyright we_sux, BlastHack

	mod_sa is available from https://github.com/BlastHackNet/mod_s0beit_sa/

	mod_sa is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	mod_sa is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with mod_sa.  If not, see <http://www.gnu.org/licenses/>.

*/
////////////////////////////////////////////////////////////////////////
// This font class was created by Azorbix (Matthew L) for Game-Deception
// http://www.game-deception.com   http://forum.game-deception.com
// irc://irc.rizon.net/game-deception
//
// A lot all of the CD3DFont::Initialize() code was created by Microsoft
// (taken from the D3D9 SDK)
//
// Please note that this is NOT 100% complete yet, colour tags and
// shadows are not implemented yet
//
// USAGE:
//   CD3DFont:
//     1) Instanciate the class with the parameterized constructor
//        eg CD3DFont *g_pD3Dfont = new CD3DFont("Arial", 16, FCT_BOLD);
//
//     2) Call Initialize() after other rendering is ready
//        eg g_pD3DFont->Initialize(pD3Ddevice);
//
//     3) To begin rendering use Print function
//        eg g_pD3DFont->Print(10.0f, 50.0f, 0xFF00FF00, "Hello World", FT_BORDER);
//
//     4) call Invalidate() upon Reset of the D3D surface and re-initialize
//
//   CD3DRender:
//     1) Instanciate the class with the parameterized constructor
//        eg CD3DRender *g_pRender = new CD3DRender(128);
//
//     2) Call Initialize() after other rendering is ready
//        eg g_pRender->Initialize(pD3Ddevice);
//
//     3) To begin rendering, start rendering much like OpenGL
//        eg if( SUCCEEDED(g_pRender->Begin(D3DPT_TRIANGLELIST)) )
//           {
//               D3DAddQuad(g_pRender, 10.0f, 10.0f, 50.0f, 50.0f, 0xFFFF0000); //helper function
//               g_pRender->D3DColour(0xFF0000FF); //blue
//               g_pRender->D3DVertex2f(60.0f, 60.0f);
//               g_pRender->D3DVertex2f(60.0f, 110.0f);
//               g_pRender->D3DVertex2f(110.0f, 110.0f);
//               g_pRender->End();
//           }
//
//     4) call Invalidate() upon Reset of the D3D surface and re-initialize
//
// FASTER RENDERING (Advanced but NOT REQUIRED):
//   To enable faster rendering, it's ideal to call static function CD3DBaseRendering::BeginRender(); before
//   other font / primitive rendering code, and call CD3DBaseRendering::EndRender(); afterwards
//   *** IT IS CRUCIAL THAT YOU CALL EndRender FOR EVERY BeginRender() CALL ***
//   *** IMAGE RENDERING MAY BECOME CORRUPT IF YOU DO NOT ***
//   eg
//     if( SUCCEEDED(CD3DBaseRender::BeginRender()) )
//     {
//         //primitive and font rendering goes here
//         CD3DBaseRender::EndRender();
//     }
//
#include "main.h"
#include "d3drender.h"

IDirect3DDevice9 *CD3DBaseRender::		m_pD3Ddev = NULL;
IDirect3DStateBlock9 *CD3DBaseRender::	m_pD3DstateDraw = NULL;
IDirect3DStateBlock9 *CD3DBaseRender::	m_pD3DstateNorm = NULL;
int CD3DBaseRender::					m_renderCount = 0;
int CD3DBaseRender::					m_numShared = 0;
bool CD3DBaseRender::					m_statesOK = false;

inline d3dvertex_s Init2DVertex ( float x, float y, DWORD color, float tu, float tv )
{
	d3dvertex_s v = { x, y, 1.0f, 1.0f, color, tu, tv };
	return v;
}
void CD3DRender::D3D_OL_Double_Trapezium(float x, float y, float w, float h, D3DCOLOR color, D3DCOLOR color2)
{
	D3DBox(x, y, w, h / 2, color);
	D3DBox(x, y + h / 2, w - h / 2, h / 2, color2);
}
void CD3DRender::D3D_OL_Trapezium(float x, float y, float w, float h, D3DCOLOR color)
{
	if (SUCCEEDED(Begin(D3DPT_TRIANGLESTRIP)))
	{
		D3DColor(color);
		//first triangle
		D3DVertex2f(x, y);//top left
		D3DVertex2f(x + w, y);//top right
		D3DVertex2f(x, y + h);//bottom left
		//second triangle
		D3DVertex2f(x + w - h, y + h);//bottom right
		End();
	}
}
CD3DBaseRender::CD3DBaseRender ()
{
	m_numShared++;
}

CD3DBaseRender::~CD3DBaseRender ()
{
	if ( --m_numShared == 0 )
		DeleteStates();
}

HRESULT CD3DBaseRender::Initialize ( IDirect3DDevice9 *pD3Ddev )
{
	if ( m_pD3Ddev == NULL && (m_pD3Ddev = pD3Ddev) == NULL )
		return E_FAIL;

	if ( !m_statesOK && FAILED(CreateStates()) )
		return E_FAIL;

	return S_OK;
}

HRESULT CD3DBaseRender::Invalidate ()
{
	DeleteStates();
	return S_OK;
}

HRESULT CD3DBaseRender::BeginRender ()
{
	if ( !m_statesOK )
		return E_FAIL;

	if ( ++m_renderCount == 1 )
	{
		m_pD3DstateNorm->Capture();
		m_pD3DstateDraw->Apply();
	}

	return S_OK;
}

HRESULT CD3DBaseRender::EndRender ()
{
	if ( !m_statesOK )
		return E_FAIL;

	m_renderCount--;

	if ( m_renderCount == 0 )
		m_pD3DstateNorm->Apply();
	else if ( m_renderCount < 0 )
		m_renderCount = 0;

	return S_OK;
}
struct vertex
{
	FLOAT x, y, z, rhw;
	DWORD color;
};

void CD3DRender::DrawCircleFilled(float x, float y, float rad, int resolution, DWORD color)
{

	std::vector<vertex> circle(resolution + 2);
	float pi;

	pi = D3DX_PI;

	circle[0].x = x;
	circle[0].y = y;
	circle[0].z = 0;
	circle[0].rhw = 1;
	circle[0].color = color;

	for (int i = 1; i < resolution + 2; i++)
	{
		circle[i].x = (float)(x - (rad * 2) * cos(pi * ((i - 1) / (resolution / 2.0f))));
		circle[i].y = (float)(y - (rad * 2) * sin(pi * ((i - 1) / (resolution / 2.0f))));
		circle[i].z = 0;
		circle[i].rhw = 1;
		circle[i].color = color;
	}

	VOID* pVertices;
	m_pD3Dbuf->Lock(0, (resolution + 2) * sizeof(vertex), (void**)& pVertices, 0);
	memcpy(pVertices, &circle[0], (resolution + 2) * sizeof(vertex));
	m_pD3Dbuf->Unlock();

	m_pD3Ddev->SetTexture(0, NULL);
	m_pD3Ddev->SetPixelShader(NULL);
	m_pD3Ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3Ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3Ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pD3Ddev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);

	m_pD3Ddev->SetStreamSource(0, m_pD3Dbuf, 0, sizeof(vertex));
	m_pD3Ddev->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	m_pD3Ddev->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, resolution);
}
HRESULT CD3DBaseRender::CreateStates ()
{
	for ( int iStateBlock = 0; iStateBlock < 2; iStateBlock++ )
	{
		m_pD3Ddev->BeginStateBlock();
		m_pD3Ddev->SetPixelShader( NULL );
		m_pD3Ddev->SetVertexShader( NULL );

		m_pD3Ddev->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		m_pD3Ddev->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		m_pD3Ddev->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		m_pD3Ddev->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );
		m_pD3Ddev->SetRenderState( D3DRS_ALPHAREF, 0x08 );
		m_pD3Ddev->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );
		m_pD3Ddev->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
		m_pD3Ddev->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
		m_pD3Ddev->SetRenderState( D3DRS_STENCILENABLE, FALSE );
		m_pD3Ddev->SetRenderState( D3DRS_CLIPPING, TRUE );
		m_pD3Ddev->SetRenderState( D3DRS_CLIPPLANEENABLE, FALSE );
		m_pD3Ddev->SetRenderState( D3DRS_VERTEXBLEND, D3DVBF_DISABLE );
		m_pD3Ddev->SetRenderState( D3DRS_INDEXEDVERTEXBLENDENABLE, FALSE );
		m_pD3Ddev->SetRenderState( D3DRS_FOGENABLE, FALSE );
		m_pD3Ddev->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, FALSE );
		m_pD3Ddev->SetRenderState( D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN |
								   D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA );

		m_pD3Ddev->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
		m_pD3Ddev->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		m_pD3Ddev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		m_pD3Ddev->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
		m_pD3Ddev->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		m_pD3Ddev->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
		m_pD3Ddev->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, 0 );
		m_pD3Ddev->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE );
		m_pD3Ddev->SetTextureStageState( 1, D3DTSS_COLOROP, D3DTOP_DISABLE );
		m_pD3Ddev->SetTextureStageState( 1, D3DTSS_ALPHAOP, D3DTOP_DISABLE );

		m_pD3Ddev->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_POINT );
		m_pD3Ddev->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_POINT );
		m_pD3Ddev->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE );

		if ( iStateBlock )
			m_pD3Ddev->EndStateBlock( &m_pD3DstateDraw );
		else
			m_pD3Ddev->EndStateBlock( &m_pD3DstateNorm );
	}

	m_statesOK = true;

	return S_OK;
}

HRESULT CD3DBaseRender::DeleteStates ()
{
	SAFE_RELEASE( m_pD3DstateDraw );
	SAFE_RELEASE( m_pD3DstateNorm );
	m_statesOK = false;

	return S_OK;
}

CD3DFont::CD3DFont ( const char *szFontName, int fontHeight, DWORD dwCreateFlags )
{
	strlcpy( m_szFontName, (szFontName ? szFontName : "Arial"), sizeof(m_szFontName) );

	m_fontHeight = fontHeight;
	m_dwCreateFlags = dwCreateFlags;

	m_isReady = false;
	m_statesOK = false;

	m_pD3Dtex = NULL;
	m_pD3Dbuf = NULL;
	m_pRender = NULL;

	m_maxTriangles = 224 * 4;

	m_texWidth = m_texHeight = 0;
	m_chrSpacing = 0;

	memset( m_fTexCoords, 0, sizeof(float) * 224 * 4 );

	m_fChrHeight = 0.0;
}

CD3DFont::~CD3DFont ()
{
	Invalidate();
}

/* god, what a mess */
HRESULT CD3DFont::Initialize ( IDirect3DDevice9 *pD3Ddev )
{
	if ( FAILED(CD3DBaseRender::Initialize(pD3Ddev)) )
		return E_FAIL;

	if ( m_pRender == NULL && (m_pRender = new CD3DRender(16)) == NULL )
		return E_FAIL;

	if ( FAILED(m_pRender->Initialize(pD3Ddev)) )
		return E_FAIL;

	m_texWidth = m_texHeight = 1024;

	if ( FAILED(m_pD3Ddev->CreateTexture(m_texWidth, m_texHeight, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, &m_pD3Dtex,
				 NULL)) )
		return E_FAIL;

	if ( FAILED(m_pD3Ddev->CreateVertexBuffer(m_maxTriangles * 3 * sizeof(d3dvertex_s),
				 D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &m_pD3Dbuf, NULL)) )
	{
		SAFE_RELEASE( m_pD3Dtex );
		return E_FAIL;
	}

	DWORD		*pBitmapBits;
	BITMAPINFO	bmi;

	memset( &bmi.bmiHeader, 0, sizeof(BITMAPINFOHEADER) );
	bmi.bmiHeader.biSize = sizeof( BITMAPINFOHEADER );
	bmi.bmiHeader.biWidth = m_texWidth;
	bmi.bmiHeader.biHeight = -m_texHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biBitCount = 32;

	HDC		hDC = CreateCompatibleDC( NULL );
	HBITMAP hbmBitmap = CreateDIBSection( hDC, &bmi, DIB_RGB_COLORS, (void **) &pBitmapBits, NULL, 0 );
	SetMapMode( hDC, MM_TEXT );

	int		iHeight = -m_fontHeight * (int)GetDeviceCaps( hDC, LOGPIXELSY ) / 72;

	HFONT	hFont = CreateFont( iHeight, 0, 0, 0, (m_dwCreateFlags & FCR_BOLD) ? FW_BOLD : FW_NORMAL,
								m_dwCreateFlags & FCR_ITALICS, false, false, DEFAULT_CHARSET, OUT_TT_PRECIS,
								CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH, m_szFontName );

	if ( hFont == NULL )
	{
		Log( "CreateFont() %s FAIL!", m_szFontName );
		DeleteObject( hbmBitmap );
		DeleteDC( hDC );
		DeleteObject( hFont );
		SAFE_RELEASE( m_pD3Dtex );
		return E_FAIL;
	}

	SelectObject( hDC, hbmBitmap );
	SelectObject( hDC, hFont );

	RECT	all = { 0, 0, m_texWidth - 1, m_texWidth - 1 };
	HBRUSH	green = CreateSolidBrush( RGB(0, 255, 0) );
	FillRect( hDC, &all, green );
	DeleteObject( green );

	SetBkMode( hDC, TRANSPARENT );
	SetTextAlign( hDC, TA_TOP );

	SIZE	size;
	char	ch = ' ';

	GetTextExtentPoint32( hDC, &ch, 1, &size );

	m_chrSpacing = ( size.cx + 3 ) / 4;
	m_fChrHeight = (float)( size.cy );

	if ( m_dwCreateFlags & FCR_BORDER )
	{
		size.cx += 2;
		size.cy += 2;
	}

	int y = 0, x = ( size.cx + 3 ) / 4;

	for ( int c = 32; c < 256; c++ )
	{
		ch = (char)c;

		GetTextExtentPoint32( hDC, &ch, 1, &size );
		if ( m_dwCreateFlags & FCR_BORDER )
		{
			size.cx += 3;
			size.cy += 3;
		}

		if ( x + size.cx + m_chrSpacing > m_texWidth )
		{
			x = m_chrSpacing;
			if ( y + size.cy * 2 + 2 < m_texHeight )
				y += size.cy + 1;
			else
				Log( "BUG: Font does not fit in texture." );
		}

		RECT	rect = { x, y, x + size.cx, y + size.cy };

		if ( m_dwCreateFlags & FCR_BORDER )
		{
			// XXX retarded :p use font outline instead
			SetTextColor( hDC, RGB(0, 0, 0) );
			x++;
			y++;
			ExtTextOut( hDC, x - 1, y - 1, ETO_CLIPPED, &rect, &ch, 1, NULL );
			ExtTextOut( hDC, x, y - 1, ETO_CLIPPED, &rect, &ch, 1, NULL );
			ExtTextOut( hDC, x + 1, y - 1, ETO_CLIPPED, &rect, &ch, 1, NULL );
			ExtTextOut( hDC, x + 1, y, ETO_CLIPPED, &rect, &ch, 1, NULL );
			ExtTextOut( hDC, x + 1, y + 1, ETO_CLIPPED, &rect, &ch, 1, NULL );
			ExtTextOut( hDC, x, y + 1, ETO_CLIPPED, &rect, &ch, 1, NULL );
			ExtTextOut( hDC, x - 1, y + 1, ETO_CLIPPED, &rect, &ch, 1, NULL );
			ExtTextOut( hDC, x - 1, y, ETO_CLIPPED, &rect, &ch, 1, NULL );
			SetTextColor( hDC, RGB(255, 0, 0) );
			ExtTextOut( hDC, x, y, ETO_CLIPPED, &rect, &ch, 1, NULL );
			x--;
			y--;
		}
		else
		{
			SetTextColor( hDC, RGB(255, 0, 0) );
			ExtTextOut( hDC, x, y, ETO_CLIPPED, &rect, &ch, 1, NULL );
		}

		//tu src + dst
		m_fTexCoords[c - 32][0] = (float)( x + 0 - m_chrSpacing ) / (float)m_texWidth;
		m_fTexCoords[c - 32][2] = (float)( x + size.cx + m_chrSpacing ) / (float)m_texWidth;

		//tv src + dst
		m_fTexCoords[c - 32][1] = (float)( y + 0 + 0 ) / (float)m_texHeight;
		m_fTexCoords[c - 32][3] = (float)( y + size.cy + 0 ) / (float)m_texHeight;

		x += size.cx + ( 2 * m_chrSpacing );
	}

	D3DLOCKED_RECT	d3dlr;
	m_pD3Dtex->LockRect( 0, &d3dlr, 0, 0 );

	BYTE	*pDstRow = (BYTE *)d3dlr.pBits;
	WORD	*pDst16;

	for ( y = 0; y < m_texHeight; y++ )
	{
		pDst16 = (WORD *)pDstRow;

		for ( x = 0; x < m_texWidth; x++ )
		{
			DWORD	pixel = pBitmapBits[m_texWidth * y + x];
			BYTE	bAlpha = 15 - ( ((BYTE) (pixel >> 8)) >> 4 );	// green channel
			BYTE	bValue = ( (BYTE) (pixel >> 16) ) >> 4;			// red channel
			*pDst16 = ( WORD ) ( bAlpha << 12 ) | ( bValue << 8 ) | ( bValue << 4 ) | ( bValue );
			pDst16++;
		}

		pDstRow += d3dlr.Pitch;
	}

	m_pD3Dtex->UnlockRect( 0 );

	DeleteObject( hbmBitmap );
	DeleteDC( hDC );
	DeleteObject( hFont );

	m_isReady = true;

	return S_OK;
}


HRESULT CD3DFont::Print2(float x, float y, DWORD color, const char *szText, bool isShadow)
{
	if (!m_isReady)
		return E_FAIL;

	x -= (float)m_chrSpacing;

	if (FAILED(this->BeginRender()))
		return E_FAIL;

	DWORD	fvf;
	m_pD3Ddev->GetFVF(&fvf);
	m_pD3Ddev->SetFVF(D3DFVF_BITMAPFONT);
	m_pD3Ddev->SetTexture(0, m_pD3Dtex);
	m_pD3Ddev->SetStreamSource(0, m_pD3Dbuf, 0, sizeof(d3dvertex_s));

	if (szText && *szText)
	{
		UINT		usedTriangles = 0;
		d3dvertex_s *pVertex;

		if (FAILED(m_pD3Dbuf->Lock(0, 0, (void **)&pVertex, D3DLOCK_DISCARD)))
		{
			m_pD3Ddev->SetFVF(fvf);
			this->EndRender();
			return E_FAIL;
		}

		size_t len = strlen(szText);
		for (size_t cpos = 0; cpos < len && szText[cpos] != '\0'; cpos++)
		{
			int c = *(unsigned char *)(&szText[cpos]) - 32;
			if (!(c >= 0 && c < 224))
				continue;

			if (szText[cpos] == '{')
			{
				size_t npos = cpos + 7;
				if (npos < len && szText[npos] == '}')
				{
					if (!isShadow)
					{
						//		color = hex_to_color(&szText[cpos + 1], 6);
					}
					cpos = npos;
					continue;
				}
				else
				{
					npos += 2;
					if (npos < len && szText[npos] == '}')
					{
						if (!isShadow)
						{
							//		color = hex_to_color(&szText[cpos + 1], 8);
						}
						cpos = npos;
						continue;
					}
				}
			}

			float	tx1 = m_fTexCoords[c][0];
			float	tx2 = m_fTexCoords[c][2];
			float	ty1 = m_fTexCoords[c][1];
			float	ty2 = m_fTexCoords[c][3];
			float	w = (tx2 - tx1) * m_texWidth;
			float	h = (ty2 - ty1) * m_texHeight;

			*pVertex++ = Init2DVertex(x - 0.5f, y - 0.5f, color, tx1, ty1);			//topleft
			*pVertex++ = Init2DVertex(x + w - 0.5f, y - 0.5f, color, tx2, ty1);		//topright
			*pVertex++ = Init2DVertex(x - 0.5f, y + h - 0.5f, color, tx1, ty2);		//bottomleft
			*pVertex++ = Init2DVertex(x + w - 0.5f, y - 0.5f, color, tx2, ty1);		//topright
			*pVertex++ = Init2DVertex(x + w - 0.5f, y + h - 0.5f, color, tx2, ty2);	//bottomright
			*pVertex++ = Init2DVertex(x - 0.5f, y + h - 0.5f, color, tx1, ty2);		//bottomleft
			if (m_dwCreateFlags & FCR_BORDER)
				w -= 2.0f;

			x += w - (m_chrSpacing * 2);
			usedTriangles += 2;
			if (usedTriangles >= m_maxTriangles)
				break;
		}

		if (usedTriangles > 0)
		{
			m_pD3Dbuf->Unlock();
			m_pD3Ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, usedTriangles);
		}
	}

	m_pD3Ddev->SetFVF(fvf);
	this->EndRender();

	return S_OK;
}
HRESULT CD3DFont::Invalidate ()
{
	m_isReady = false;

	SAFE_RELEASE( m_pD3Dtex );
	SAFE_RELEASE( m_pD3Dbuf );

	//SAFE_RELEASE(m_pD3DstateDraw);
	//SAFE_RELEASE(m_pD3DstateNorm);
	m_pRender->Invalidate();

	//CD3DBaseRender::Invalidate();
	return S_OK;
}


struct stColorTag
{
	D3DCOLOR _color;
	bool _alpha;
	bool _valid;
};

stColorTag GetColorTag( const char *text, size_t maxLen )
{
	stColorTag color = { 0, false, false };
	const int minLen = 8; // { + XXXXXX + } = 8

	if ( text == nullptr || *text != '{' || maxLen < minLen )
		return color;
	
	if ( text[7] == '}' )
	{
		color._alpha = false;
		color._valid = true;
	}
	else if ( minLen + 2 <= maxLen && text[9] == '}' )
	{
		color._alpha = true;
		color._valid = true;
	}
	if ( color._valid )
	{
		if ( hex_is_valid( std::string( text ).substr( 1, color._alpha ? 8 : 6 ) ) )
			color._color = strtol( &text[1], nullptr, 16 );
		else
			color._valid = false;
	}
	return color;
}

HRESULT CD3DFont::Print( const char *text, D3DCOLOR color, float x, float y, bool skipColorTags, bool noColorFormat )
{
	if ( !m_isReady || text == nullptr || *text == '\0' )
		return E_FAIL;

	float xp = x, yp = y;
	D3DCOLOR clr = color;
	xp = x -= ( float ) m_chrSpacing;

	if ( FAILED( this->BeginRender() ) )
		return E_FAIL;

	DWORD fvf;
	m_pD3Ddev->GetFVF( &fvf );
	m_pD3Ddev->SetFVF( D3DFVF_BITMAPFONT );
	m_pD3Ddev->SetTexture( 0, m_pD3Dtex );
	m_pD3Ddev->SetStreamSource( 0, m_pD3Dbuf, 0, sizeof(d3dvertex_s) );

	UINT		usedTriangles = 0;
	d3dvertex_s *pVertex;

	if ( FAILED( m_pD3Dbuf->Lock( 0, 0, ( void ** ) &pVertex, D3DLOCK_DISCARD ) ) )
	{
		m_pD3Ddev->SetFVF( fvf );
		this->EndRender();
		return E_FAIL;
	}

	size_t len = strlen( text );
	for ( size_t cpos = 0; cpos < len; cpos++ )
	{
		if ( text[cpos] == '\n' )
		{
			xp = x;
			yp += DrawHeight();
			continue;
		}
		int c = ( byte ) ( text[cpos] ) - 32;
		if ( !( c >= 0 && c < 224 ) )
			continue;

		if ( text[cpos] == '{' && !noColorFormat )
		{
			stColorTag tag = GetColorTag( &text[cpos], len - cpos );
			if ( tag._valid )
			{
				if ( !skipColorTags )
				{
					clr = tag._color;
					if ( !tag._alpha )
						clr |= 0xFF000000;
				}
				cpos += tag._alpha ? 9 : 7;
				continue;
			}
		}

		float	tx1 = m_fTexCoords[c][0];
		float	tx2 = m_fTexCoords[c][2];
		float	ty1 = m_fTexCoords[c][1];
		float	ty2 = m_fTexCoords[c][3];
		float	w = ( tx2 - tx1 ) * m_texWidth;
		float	h = ( ty2 - ty1 ) * m_texHeight;

		*pVertex++ = Init2DVertex( xp - 0.5f, yp - 0.5f, clr, tx1, ty1 );			//topleft
		*pVertex++ = Init2DVertex( xp + w - 0.5f, yp - 0.5f, clr, tx2, ty1 );		//topright
		*pVertex++ = Init2DVertex( xp - 0.5f, yp + h - 0.5f, clr, tx1, ty2 );		//bottomleft
		*pVertex++ = Init2DVertex( xp + w - 0.5f, yp - 0.5f, clr, tx2, ty1 );		//topright
		*pVertex++ = Init2DVertex( xp + w - 0.5f, yp + h - 0.5f, clr, tx2, ty2 );	//bottomright
		*pVertex++ = Init2DVertex( xp - 0.5f, yp + h - 0.5f, clr, tx1, ty2 );		//bottomleft
		if ( m_dwCreateFlags & FCR_BORDER )
			w -= 2.0f;

		xp += w - ( m_chrSpacing * 2 );
		usedTriangles += 2;
		if ( usedTriangles >= m_maxTriangles )
			break;
	}
	m_pD3Dbuf->Unlock();
	if ( usedTriangles > 0 )
	{
		m_pD3Ddev->DrawPrimitive( D3DPT_TRIANGLELIST, 0, usedTriangles );
	}
	m_pD3Ddev->SetFVF( fvf );
	this->EndRender();

	return S_OK;
}

HRESULT CD3DFont::PrintShadow ( float x, float y, DWORD color, const char *szText )
{
	if (set.render_text_shadows)
		Print(szText, D3DCOLOR_ARGB( ( byte ) HIBYTE( HIWORD( color ) ), 0, 0, 0 ), x + 1, y + 1, true, false);
	return Print(szText, color, x, y, false, false);
}

float CD3DFont::DrawLength ( const char *szText, bool noColorFormat ) const
{
	float	len = 0.0f;
	float	sub = ( m_dwCreateFlags & FCR_BORDER ) ? 2.0f : 0.0f;

	size_t strl = strlen( szText );
	for ( size_t cpos = 0; cpos < strl && szText[cpos] != '\0'; cpos++ )
	{
		int c = ( byte ) ( szText[cpos] ) - 32;
		if ( !( c >= 0 && c < 224 ) )
			continue;

		if ( szText[cpos] == '{' && !noColorFormat )
		{
			stColorTag tag = GetColorTag( &szText[cpos], strl - cpos );
			if ( tag._valid )
			{
				cpos += tag._alpha ? 9 : 7;
				continue;
			}
		}

		len += ( (m_fTexCoords[c][2] - m_fTexCoords[c][0]) * m_texWidth - sub ) - m_chrSpacing * 2;
	}
	return len;
}

size_t CD3DFont::GetCharPos( const char *text, float x, bool noColorFormat ) const
{
	size_t pos = 0;
	float	len = 0.0f;
	float	sub = ( m_dwCreateFlags & FCR_BORDER ) ? 2.0f : 0.0f;

	size_t strl = strlen( text );
	for ( size_t cpos = 0; cpos < strl && text[cpos] != '\0'; cpos++, pos++ )
	{
		int c = ( byte ) ( text[cpos] ) - 32;
		if ( !( c >= 0 && c < 224 ) )
			continue;

		if ( text[cpos] == '{' && !noColorFormat )
		{
			stColorTag tag = GetColorTag( &text[cpos], strl - cpos );
			if ( tag._valid )
			{
				cpos += tag._alpha ? 9 : 7;
				continue;
			}
		}
		len += ( (m_fTexCoords[c][2] - m_fTexCoords[c][0]) * m_texWidth - sub ) - m_chrSpacing * 2;
		if ( len >= x )
			break;
	}
	return pos;
}

CD3DRender::CD3DRender ( int numVertices )
{
	m_canRender = false;

	m_pD3Dbuf = NULL;
	m_pVertex = NULL;

	m_color = 0;
	m_tu = 0.0f;
	m_tv = 0.0f;
	m_texture = NULL;

	m_maxVertex = numVertices;
	m_curVertex = 0;
}

CD3DRender::~CD3DRender ()
{
	Invalidate();
}

HRESULT CD3DRender::Initialize ( IDirect3DDevice9 *pD3Ddev )
{
	if ( !m_canRender )
	{
		if ( FAILED(CD3DBaseRender::Initialize(pD3Ddev)) )
			return E_FAIL;
		if ( FAILED(m_pD3Ddev->CreateVertexBuffer(m_maxVertex * sizeof(d3dvertex_s),
					 D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &m_pD3Dbuf, NULL)) )
			return E_FAIL;

		m_canRender = true;
	}

	return S_OK;
}

HRESULT CD3DRender::Invalidate ()
{
	SAFE_RELEASE( m_pD3Dbuf );
	SAFE_RELEASE( m_texture );
	m_pVertex = NULL;

	//SAFE_RELEASE(m_pD3DstateDraw);
	//SAFE_RELEASE(m_pD3DstateNorm);
	CD3DBaseRender::Invalidate();
	m_canRender = false;

	return S_OK;
}
void CD3DRender::D3D_Double_Label_Menu(int x, int y, int w, int h, D3DCOLOR color, D3DCOLOR color2)
{
	//pD3DFont_Footer

	//D3D_OL_Rounded(x, y, pD3DFontChat->DrawLength(text) + pD3DFontChat->DrawHeight() / 2.0f, pD3DFontChat->DrawHeight() + 2.0f, color);

	render->D3DBox(x, y, w + 2.0f, h, color);

	//pD3DGoCFontSmall->Print(w, textcolor, x + 3.0f, y - 1.0f, true, true);
	//pD3DGoCFontSmall->PrintShadow(x + 3.0f, (float)(pPresentParam.BackBufferHeight) - pD3DGoCFontSmall->DrawHeight() + y - 1, textcolor, text);
	//(x) += pD3DGoCFontSmall->DrawLength(text);
	render->D3DBox(x, y, 3.0f, h, color2);
	render->D3DBox(x + w + 2.0f, y, 3.0f, h, color2);
}

HRESULT CD3DRender::Begin ( D3DPRIMITIVETYPE primType )
{
	if ( !m_canRender )
		return E_FAIL;

	if ( m_pVertex != NULL )
		return E_FAIL;

	if ( FAILED(m_pD3Dbuf->Lock(0, 0, (void **) &m_pVertex, D3DLOCK_DISCARD)) )
		return E_FAIL;

	m_primType = primType;

	return S_OK;
}

HRESULT CD3DRender::End ()
{
	int numPrims;

	m_pVertex = NULL;

	if ( !m_canRender )
	{
		m_curVertex = 0;
		return E_FAIL;
	}

	if ( FAILED(CD3DBaseRender::BeginRender()) )
		return E_FAIL;

	switch ( m_primType )
	{
	case D3DPT_POINTLIST:
		numPrims = m_curVertex;
		break;

	case D3DPT_LINELIST:
		numPrims = m_curVertex / 2;
		break;

	case D3DPT_LINESTRIP:
		numPrims = m_curVertex - 1;
		break;

	case D3DPT_TRIANGLELIST:
		numPrims = m_curVertex / 3;
		break;

	case D3DPT_TRIANGLESTRIP:
	case D3DPT_TRIANGLEFAN:
		numPrims = m_curVertex - 2;
		break;

	default:
		numPrims = 0;
		break;
	}

	m_curVertex = 0;

	if ( numPrims > 0 )
	{
		m_pD3Dbuf->Unlock();

		DWORD	fvf;
		m_pD3Ddev->GetFVF( &fvf );

		if ( m_texture == NULL )
		{
			m_pD3Ddev->SetFVF( D3DFVF_PRIMITIVES );
			m_pD3Ddev->SetTexture( 0, NULL );
		}
		else
		{
			m_pD3Ddev->SetFVF( D3DFVF_BITMAPFONT );
			m_pD3Ddev->SetTexture( 0, m_texture );
		}

		m_pD3Ddev->SetStreamSource( 0, m_pD3Dbuf, 0, sizeof(d3dvertex_s) );

		m_pD3Ddev->DrawPrimitive( m_primType, 0, numPrims );

		m_pD3Ddev->SetFVF( fvf );
	}

	CD3DBaseRender::EndRender();

	return S_OK;
}

HRESULT CD3DRender::D3DColor ( DWORD color )
{
	m_color = color;
	return m_canRender ? S_OK : E_FAIL;
	return S_OK;
}

void CD3DRender::D3DBindTexture ( IDirect3DTexture9 *texture )
{
	m_texture = texture;
}

void CD3DRender::D3DTexCoord2f ( float u, float v )
{
	m_tu = u;
	m_tv = v;
}

HRESULT CD3DRender::D3DVertex2f ( float x, float y )
{
	if ( m_canRender && m_pVertex && ++m_curVertex < m_maxVertex )
		*m_pVertex++ = Init2DVertex( x, y, m_color, m_tu, m_tv );
	else
		return E_FAIL;

	return S_OK;
}

void CD3DRender::D3DTexQuad ( float sx, float sy, float ex, float ey, float su, float sv, float eu, float ev )
{
	if ( SUCCEEDED(Begin(D3DPT_TRIANGLELIST)) )
	{
		D3DColor( D3DCOLOR_XRGB(255, 255, 255) );
		D3DTexCoord2f( su, sv );
		D3DVertex2f( sx, sy );
		D3DTexCoord2f( eu, sv );
		D3DVertex2f( ex, sy );
		D3DTexCoord2f( su, ev );
		D3DVertex2f( sx, ey );

		D3DTexCoord2f( su, ev );
		D3DVertex2f( sx, ey );
		D3DTexCoord2f( eu, sv );
		D3DVertex2f( ex, sy );
		D3DTexCoord2f( eu, ev );
		D3DVertex2f( ex, ey );
		End();
	}
}

void CD3DRender::D3DBox ( float x, float y, float w, float h, D3DCOLOR color )
{
	if ( SUCCEEDED(Begin(D3DPT_TRIANGLELIST)) )
	{
		D3DColor( color );
		D3DVertex2f( x, y );
		D3DVertex2f( x + w, y );
		D3DVertex2f( x, y + h );
		D3DVertex2f( x, y + h );
		D3DVertex2f( x + w, y );
		D3DVertex2f( x + w, y + h );
		End();
	}
}

void CD3DRender::D3DBoxi ( int x, int y, int w, int h, D3DCOLOR color, int maxW )
{
	if ( maxW )
	{
		if ( w >= maxW )
			( w = maxW );
		D3DBox( (float)x, (float)y, (float)w, (float)h, color );
	}
	else
	{
		D3DBox( (float)x, (float)y, (float)w, (float)h, color );
	}
}

void CD3DRender::D3DBoxBorder ( float x, float y, float w, float h, D3DCOLOR border_color, D3DCOLOR color )
{
	D3DBox( x, y, w - 1.0f, 1.0f, border_color );
	D3DBox( x + w - 1.0f, y, 1.0f, h - 1.0f, border_color );
	D3DBox( x + 1.0f, y + h - 1.0f, w - 1.0f, 1.0f, border_color );
	D3DBox( x, y + 1.0f, 1.0f, h - 1.0f, border_color );
	D3DBox( x + 1.0f, y + 1.0f, w - 2.0f, h - 2.0f, color );
}

void CD3DRender::D3DBoxBorderi ( int x, int y, int w, int h, D3DCOLOR border_color, D3DCOLOR color )
{
	D3DBoxBorder( (float)x, (float)y, (float)w, (float)h, border_color, color );
}

void CD3DRender::D3DLine(int x, int y, int x2, int y2, D3DCOLOR color)
{
	if (SUCCEEDED(Begin(D3DPT_LINELIST)))
	{
		D3DColor(color);
		D3DVertex2f(x, y);
		D3DVertex2f(x2, y2);
		End();
	}
}

bool CD3DRender::DrawLine ( const D3DXVECTOR3 &a, const D3DXVECTOR3 &b, DWORD dwColor )
{
	if ( FAILED(CD3DBaseRender::BeginRender()) )
		return false;

	////////////////////////////////////////////////////
	// Make sure we have a valid vertex buffer.
	if ( m_pD3Dbuf == NULL )
	{
		return false;
	}

	m_pD3Ddev->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG2 );
	m_pD3Ddev->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2 );
	//m_pD3Ddev->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	//m_pD3Ddev->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );

	m_pD3Ddev->SetRenderState( D3DRS_CLIPPING, false );
	m_pD3Ddev->SetRenderState ( D3DRS_ZENABLE, false );
	//m_pD3Ddev->SetRenderState ( D3DRS_LIGHTING, false );
	D3DLVERTEX	lineList[2];

	//////////////////////////////////////////////////
	// Lock the vertex buffer and copy in the verts.
	m_pD3Dbuf->Lock( 0, 0, (void **) &lineList, D3DLOCK_DISCARD | D3DLOCK_NOSYSLOCK ); // flogs: D3DLOCK_NOSYSLOCK, D3DLOCK_DISCARD
	{
		lineList[0].x = a.x;
		lineList[0].y = a.y;
		lineList[0].z = a.z;
		lineList[0].color = dwColor;
		lineList[0].specular = dwColor;

		lineList[1].x = b.x;
		lineList[1].y = b.y;
		lineList[1].z = b.z;
		lineList[1].color = dwColor;
		lineList[1].specular = dwColor;
	}

	m_pD3Dbuf->Unlock();

	// store FVF to restore original at the end of this function
	DWORD		fvf;
	m_pD3Ddev->GetFVF( &fvf );
	m_pD3Ddev->SetFVF( D3DFVF_LVERTEX );
	//m_pD3Ddev->SetFVF( D3DFVF_PRIMITIVES );

	////////////////////////////////////////////////////
	// Draw!
	m_pD3Ddev->DrawPrimitiveUP( D3DPT_LINESTRIP, 1, lineList, sizeof(lineList) / 2 );

	// reset states
	m_pD3Ddev->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
	m_pD3Ddev->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	m_pD3Ddev->SetRenderState ( D3DRS_ZENABLE, true );
	m_pD3Ddev->SetRenderState( D3DRS_CLIPPING, true );

	// restore FVF
	m_pD3Ddev->SetFVF( fvf );

	CD3DBaseRender::EndRender();

	return true;
}

void CD3DRender::D3DBoxBorderNewModSa(float x, float y, float w, float h, D3DCOLOR color)
{
	DWORD color1 = D3DCOLOR_ARGB(255, 0, 0, 153);
	DWORD color2 = D3DCOLOR_ARGB(255, 0, 153, 153);
	float border_weight = 4.0f;
	float border_height = 12.0f;
	D3DBox(x, y - border_weight / 2 - 1.0f, w, border_weight, color2);//top
	D3DBox(x + w - 1.0f, y - border_weight / 2 - 1.0f, border_weight, border_height, color2);//top/right
	D3DBox(x - border_weight / 2 - 1.0f, y - border_weight / 2 - 1.0f, border_weight, border_height, color2);//top/left
	D3DBox(x, y + h - 1.0f, w, border_weight, color1);//bottom
	D3DBox(x + w - 1.0f, y + h - border_weight * 2 - 1.0f, border_weight, border_height, color1);//bottom/right
	D3DBox(x - border_weight / 2 - 1.0f, y + h - border_weight * 2 - 1.0f, border_weight, border_height, color1);//bottom/left
	D3DBox(x + 1.0f, y + 1.0f, w - 2.0f, h - 2.0f, color);//box
}

void CD3DRender::D3D_OL_Parallelogram(float x, float y, float w, float h, D3DCOLOR color)
{
	if (SUCCEEDED(Begin(D3DPT_TRIANGLELIST)))
	{
		D3DColor(color);
		//first triangle
		D3DVertex2f(x, y);//top left
		D3DVertex2f(x + w, y);//top right
		D3DVertex2f(x - h, y + h);//bottom left
		//second triangle
		D3DVertex2f(x - h, y + h);//top right
		D3DVertex2f(x + w, y);//top left
		D3DVertex2f(x + w - h, y + h);//bottom right
		End();
	}
}

void CD3DRender::D3D_OL_Double_Parallelogram(float x, float y, float w, float h, D3DCOLOR color, D3DCOLOR color2)
{
	D3D_OL_Trapezium(x, y, w, h / 2, color);
	D3D_OL_Trapezium(x, y + h / 2, w - h / 2, h / 2, color);
}



//void CD3DRender::D3D_OL_Trapezium(float x, float y, float w, float h, D3DCOLOR color)
//{
//
//	if (SUCCEEDED(Begin(D3DPT_TRIANGLESTRIP)))
//	{
//		D3DColor(color);
//		//first triangle
//		D3DVertex2f(x, y);//top left
//		D3DVertex2f(x + w, y);//top right
//		D3DVertex2f(x, y + h);//bottom left
//		//second triangle
//		D3DVertex2f(x + w - h, y + h);//bottom right
//		End();
//	}
//
//}



void CD3DRender::D3D_OL_Circle(float x, float y, float d, float fStart, float fEnd, D3DCOLOR color)
{
	float r = ceilf(d / 2.0f);
	y -= 1.0f;
	if (SUCCEEDED(Begin(D3DPT_TRIANGLEFAN)))
	{
		float fStep = abs(((fEnd < 0.0f) ? (2 * M_PI + fEnd) : fEnd) - ((fStart < 0.0f) ? (2 * M_PI + fStart) : fStart)) / r,
			i;
		D3DColor(color);
		D3DVertex2f(x, y + (r));

		for (i = fStart; i < fEnd; i += fStep)
			D3DVertex2f(x + r * cosf(i), y + r * sinf(i) + r);
		i = fEnd;

		D3DVertex2f(x + r * cosf(i), y + r * sinf(i) + r);
		End();
	}
}

//was for test
void CD3DRender::D3D_OL_Circle2(float x, float y, float d, float fStart, float fEnd, D3DCOLOR color)
{
	float r = ceilf(d / 2.0f);
	y -= 1.0f;
	if (SUCCEEDED(Begin(D3DPT_TRIANGLEFAN)))
	{
		float fStep = (fEnd) / (d - 1.0f), i;
		D3DColor(color);
		D3DVertex2f(x, y + r);

		for (i = fStart; i < fEnd; i += fStep)
			D3DVertex2f(x + r * cosf(i), y + (r)* sinf(i) + r);
		i = fEnd;
		r -= 1.0f;
		D3DVertex2f(x + r * cosf(i), y + r * sinf(i) + r);
		End();
	}
}

void CD3DRender::D3D_OL_BoxRounded(float x, float y, float w, float h, float r, D3DCOLOR color)
{

	D3DBox(x + r, y, w - r, h - 1.0f, color);

	D3D_OL_Circle(x + r, y, r * 4.0f, M_PI, 3.0f * M_PI / 2.0f, color);//top left
	D3DBox(x - r + 1.0f, y + r * 2.0f - 1.0f, r * 2.0f - 1.0f, h - r * 4.0f, color);
	D3D_OL_Circle2(x + r, y + h - r * 4.0f, r * 4.0f, M_PI / 2.0f, M_PI, color);//bottom left

	D3D_OL_Circle(x + w, y, r * 4.0f, 3.0f * M_PI / 2.0f, 2.0f * M_PI, color);//top right
	D3DBox(x + w, y + r * 2.0f - 1.0f, r * 2.0f, h - r * 4.0f, color);
	D3D_OL_Circle(x + w, y + h - r * 4.0f, r * 4.0f, 0, M_PI / 2.0f, color);//bottom right
	//D3D_OL_Circle(x + w, y, h, -M_PI / 2.0f, M_PI / 2.0f, color);

}

void CD3DRender::D3D_OL_Label(const char* text, float x, float y, D3DCOLOR color, D3DCOLOR color2, D3DCOLOR textcolor)
{
	//pD3DFont_Footer

	//D3D_OL_Rounded(x, y, pD3DFontChat->DrawLength(text) + pD3DFontChat->DrawHeight() / 2.0f, pD3DFontChat->DrawHeight() + 2.0f, color);
	D3DBox(x, y, pD3DFont->DrawLength(text), pD3DFont->DrawHeight(), color);
	pD3DFont->Print(text, textcolor, x, y, true, true);
	D3DBox(x, y + pD3DFont->DrawHeight(), pD3DFont->DrawLength(text), 3.0f, color2);
}


void CD3DRender::D3D_OL_Label_Top(const char* text, float x, float y, D3DCOLOR color, D3DCOLOR color2, D3DCOLOR textcolor)
{
	//pD3DFont_Footer

	//D3D_OL_Rounded(x, y, pD3DFontChat->DrawLength(text) + pD3DFontChat->DrawHeight() / 2.0f, pD3DFontChat->DrawHeight() + 2.0f, color);
	D3DBox(x, y, pD3DFontChat->DrawLength(text), 3.0f, color2);
	D3DBox(x, y + 3.0f, pD3DFontChat->DrawLength(text), pD3DFontChat->DrawHeight(), color);
	pD3DFontChat->Print(text, textcolor, x, y + 3.0f - 1.0f, true, true);

}


void CD3DRender::D3D_OL_Label_Right(const char* text, float x, float y, D3DCOLOR color, D3DCOLOR color2, D3DCOLOR textcolor)
{
	//pD3DFont_Footer

	//D3D_OL_Rounded(x, y, pD3DFontChat->DrawLength(text) + pD3DFontChat->DrawHeight() / 2.0f, pD3DFontChat->DrawHeight() + 2.0f, color);
	float fLenght = pD3DFontChat->DrawLength(text), fHeight = pD3DFontChat->DrawHeight();
	D3DBox(x - fLenght, y, fLenght, fHeight, color);
	pD3DFontChat->Print(text, textcolor, x - fLenght - 3.0f, y - 1.0f, true, true);
	D3DBox(x - 3.0f, y, 3.0f, fHeight, color2);
}

void CD3DRender::D3D_OL_Label_Left(const char* text, float x, float y, D3DCOLOR color, D3DCOLOR color2, D3DCOLOR textcolor)
{
	//pD3DFont_Footer

	//D3D_OL_Rounded(x, y, pD3DFontChat->DrawLength(text) + pD3DFontChat->DrawHeight() / 2.0f, pD3DFontChat->DrawHeight() + 2.0f, color);
	float fLenght = pD3DFontChat->DrawLength(text), fHeight = pD3DFontChat->DrawHeight();
	D3DBox(x + 3.0f, y, fLenght, fHeight, color);
	pD3DFontChat->Print(text, textcolor, x + 3.0f, y - 1.0f, true, true);
	D3DBox(x, y, 3.0f, fHeight, color2);
}

void CD3DRender::D3D_OL_LabelRounded(const char* text, float x, float y, D3DCOLOR color, D3DCOLOR textcolor)
{
	//pD3DFontChat

	D3D_OL_Rounded(x, y, pD3DFontChat->DrawLength(text) + pD3DFontChat->DrawHeight() / 2.0f, pD3DFontChat->DrawHeight() + 2.0f, color);
	pD3DFontChat->Print(text, textcolor, x + pD3DFontChat->DrawHeight() / 4.0f, y, true, true);
}

void CD3DRender::D3D_OL_Rounded(float x, float y, float w, float h, D3DCOLOR color)
{
	w -= h;
	x += h / 2.0f;

	D3DBox(x, y, w, h, color);

	D3D_OL_Circle2(x, y, h, M_PI / 2.0f, 3.0f * M_PI / 2.0f, color);

	//damn this side
	D3D_OL_Circle(x + w, y, h, -M_PI / 2.0f, M_PI / 2.0f, color);

}

void CD3DRender::D3D_OL_Trapezium_Inverted(float x, float y, float w, float h, D3DCOLOR color)
{
	if (SUCCEEDED(Begin(D3DPT_TRIANGLESTRIP)))
	{
		D3DColor(color);
		//first triangle
		D3DVertex2f(x - h, y);//top left
		D3DVertex2f(x + w, y);//top right
		D3DVertex2f(x, y + h);//bottom left
		//second triangle
		D3DVertex2f(x + w, y + h);//bottom right
		End();
	}
}


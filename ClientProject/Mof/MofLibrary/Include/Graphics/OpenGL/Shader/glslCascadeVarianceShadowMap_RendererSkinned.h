#ifdef SHADER_INCLUDE

const char* g_CascadeVarianceShadowMap_RendererSkinned_VS =
"#version 130\n"
"attribute vec4 pos;\n"
"attribute vec3 normal;\n"
"attribute vec4 weight;\n"
"attribute vec4 bindex;\n"
"attribute vec2 Tex;\n"
"attribute vec4 color;\n"
"varying vec2 OUV;\n"
"varying vec3 ONORMAL;\n"
"varying vec3 OEYE;\n"
"varying vec4 OVCOL;\n"
"varying vec4 OTEXSHADOW;\n"
"uniform vec4 mtxWorld[3 * 128];\n"
"uniform mat4 mtxView;\n"
"uniform mat4 mtxProj;\n"
"uniform vec4 vecViewPos;\n"
"uniform vec4 colRevise;\n"
"uniform vec4 CoordsRevise;\n"
"uniform mat4 m_mShadow;\n"
"void main(){\n"
	"vec4 tPos = vec4(0.0, 0.0, 0.0, 1.0);\n"
	"vec3 norm = vec3(0.0, 0.0, 0.0);\n"
	"int idx;\n"
	"idx = int(bindex[0]) * 3;\n"
	"tPos.x += dot( pos, mtxWorld[idx + 0] ) * weight[0];\n"
	"tPos.y += dot( pos, mtxWorld[idx + 1] ) * weight[0];\n"
	"tPos.z += dot( pos, mtxWorld[idx + 2] ) * weight[0];\n"
	"norm.x += dot( normal, mtxWorld[idx + 0].xyz ) * weight[0];\n"
	"norm.y += dot( normal, mtxWorld[idx + 1].xyz ) * weight[0];\n"
	"norm.z += dot( normal, mtxWorld[idx + 2].xyz ) * weight[0];\n"
	"idx = int(bindex[1]) * 3;\n"
	"tPos.x += dot( pos, mtxWorld[idx + 0] ) * weight[1];\n"
	"tPos.y += dot( pos, mtxWorld[idx + 1] ) * weight[1];\n"
	"tPos.z += dot( pos, mtxWorld[idx + 2] ) * weight[1];\n"
	"norm.x += dot( normal, mtxWorld[idx + 0].xyz ) * weight[1];\n"
	"norm.y += dot( normal, mtxWorld[idx + 1].xyz ) * weight[1];\n"
	"norm.z += dot( normal, mtxWorld[idx + 2].xyz ) * weight[1];\n"
	"idx = int(bindex[2]) * 3;\n"
	"tPos.x += dot( pos, mtxWorld[idx + 0] ) * weight[2];\n"
	"tPos.y += dot( pos, mtxWorld[idx + 1] ) * weight[2];\n"
	"tPos.z += dot( pos, mtxWorld[idx + 2] ) * weight[2];\n"
	"norm.x += dot( normal, mtxWorld[idx + 0].xyz ) * weight[2];\n"
	"norm.y += dot( normal, mtxWorld[idx + 1].xyz ) * weight[2];\n"
	"norm.z += dot( normal, mtxWorld[idx + 2].xyz ) * weight[2];\n"
	"idx = int(bindex[3]) * 3;\n"
	"tPos.x += dot( pos, mtxWorld[idx + 0] ) * weight[3];\n"
	"tPos.y += dot( pos, mtxWorld[idx + 1] ) * weight[3];\n"
	"tPos.z += dot( pos, mtxWorld[idx + 2] ) * weight[3];\n"
	"norm.x += dot( normal, mtxWorld[idx + 0].xyz ) * weight[3];\n"
	"norm.y += dot( normal, mtxWorld[idx + 1].xyz ) * weight[3];\n"
	"norm.z += dot( normal, mtxWorld[idx + 2].xyz ) * weight[3];\n"
	"mat4 mtxVP = mtxView * mtxProj;\n"
	"gl_Position = tPos * mtxVP;\n"
	"ONORMAL = normalize( norm );\n"
	"OEYE = normalize( tPos.xyz - vecViewPos.xyz );\n"
	"OVCOL = color * colRevise;\n"
	"OUV = Tex + CoordsRevise.xy;\n"
	"OTEXSHADOW = tPos * m_mShadow;\n"
"}\n";

const char* g_CascadeVarianceShadowMap_RendererSkinned_PS =
"#version 130\n"
"precision mediump float;\n"
"varying vec2 OUV;\n"
"varying vec3 ONORMAL;\n"
"varying vec3 OEYE;\n"
"varying vec4 OVCOL;\n"
"uniform vec4 matDiffuse;\n"
"uniform vec4 matAmbient;\n"
"uniform vec4 matSpeculer;\n"
"uniform vec4 matEmissive;\n"
"uniform float matPower;\n"
"uniform vec3 litDirection;\n"
"uniform vec4 litDiffuse;\n"
"uniform vec4 litAmbient;\n"
"uniform vec4 litSpeculer;\n"
"uniform sampler2D txDiffuse;\n"
#include "glslCascadeVarianceShadowMap.h"
"void main(){\n"
	"float fPercentLit = CalculateCascadeVarianceShadow(OTEXSHADOW);\n"
	"vec3 amb = litAmbient.xyz * matAmbient.xyz;\n"
	"float l = max( 0.0f, dot( ONORMAL, -litDirection ) );\n"
	"vec3 diff = l * litDiffuse.xyz * matDiffuse.xyz;\n"
	"vec4 LP = vec4( clamp( matEmissive.xyz + amb + diff * fPercentLit, 0.0, 1.0 ) , matDiffuse.w ) * OVCOL;\n"
	"vec4 ocol = LP * texture2D( txDiffuse, OUV);\n"
	"vec3 R = reflect( OEYE, ONORMAL );\n"
	"ocol.xyz += litSpeculer.xyz * matSpeculer.xyz * pow( abs( max( 0 , dot( R, -litDirection ) ) ) , matPower ) * fPercentLit;\n"
	
	/*
	"if(iCurrentCascadeIndex == 0){\n"
		"ocol.rgb *= vec3(1.0f,0.7f,0.7f);\n"
	"}else if(iCurrentCascadeIndex == 1){\n"
		"ocol.rgb *= vec3(0.7f,1.0f,0.7f);\n"
	"}else if(iCurrentCascadeIndex == 2){\n"
		"ocol.rgb *= vec3(0.7f,0.7f,1.0f);\n"
	"}\n"
	/*/
	
	"gl_FragColor = ocol;\n"
"}\n";


#else
extern const char* g_CascadeVarianceShadowMap_RendererSkinned_VS;
extern const char* g_CascadeVarianceShadowMap_RendererSkinned_PS;
#endif

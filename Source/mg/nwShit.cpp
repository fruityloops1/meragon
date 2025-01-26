#pragma once

#include "hk/Types.h"
#include "hk/debug/Log.h"
#include "hk/hook/BranchHook.h"

struct FloatColor {
    float r, g, b, a;
};

struct U32Color {
    u8 r : 8, g : 8, b : 8, a : 8;
};

struct MaterialColorData {
    u8 _0[36];
    FloatColor emission;
    FloatColor ambientVertexScale;
    FloatColor diffuse;
    FloatColor specular0, specular1;
    FloatColor constant0, constant1, constant2, constant3, constant4, constant5;
    U32Color emissionColor;
    U32Color ambientColor;
    U32Color diffuseColor;
    U32Color specular0Color, specular1Color;
    U32Color constant0Color, constant1Color, constant2Color, constant3Color, constant4Color, constant5Color;
};

u32 setupHook(MaterialColorData** dataPtr, void* a, void* b, void* c)
{
    MaterialColorData* data = *dataPtr;
    if (data) {
        /*data->emission = { 0, 0, 0, 1 };
        data->diffuse = { 0, 0, 0, 1 };
        data->specular0 = { 0, 0, 0, 1 };
        data->specular1 = { 0, 0, 0, 1 };
        data->constant0 = { 0, 0, 0, 1 };
        data->constant1 = { 0, 0, 0, 1 };
        data->constant2 = { 0, 0, 0, 1 };
        data->constant3 = { 0, 0, 0, 1 };
        data->constant4 = { 0, 0, 0, 1 };
        data->constant5 = { 0, 0, 0, 1 };*/

        U32Color color = { 255, 0, 0, 255 };

        // data->specular0Color = { 0, 0, 0, 255 };
        // data->specular1Color = { 0, 0, 0, 255 };
        data->emissionColor = { 255, 0, 0, 255 };

        hk::dbg::Log("emission %f %f %f %f", data->emission.r, data->emission.g, data->emission.b, data->emission.a);
        hk::dbg::Log("ambientVertexScale %f %f %f %f", data->ambientVertexScale.r, data->ambientVertexScale.g, data->ambientVertexScale.b, data->ambientVertexScale.a);
        hk::dbg::Log("diffuse %f %f %f %f", data->diffuse.r, data->diffuse.g, data->diffuse.b, data->diffuse.a);
        hk::dbg::Log("specular0 %f %f %f %f", data->specular0.r, data->specular0.g, data->specular0.b, data->specular0.a);
        hk::dbg::Log("specular1 %f %f %f %f", data->specular1.r, data->specular1.g, data->specular1.b, data->specular1.a);
        hk::dbg::Log("constant0 %f %f %f %f", data->constant0.r, data->constant0.g, data->constant0.b, data->constant0.a);
        hk::dbg::Log("constant1 %f %f %f %f", data->constant1.r, data->constant1.g, data->constant1.b, data->constant1.a);
        hk::dbg::Log("constant2 %f %f %f %f", data->constant2.r, data->constant2.g, data->constant2.b, data->constant2.a);
        hk::dbg::Log("constant3 %f %f %f %f", data->constant3.r, data->constant3.g, data->constant3.b, data->constant3.a);
        hk::dbg::Log("constant4 %f %f %f %f", data->constant4.r, data->constant4.g, data->constant4.b, data->constant4.a);
        hk::dbg::Log("constant5 %f %f %f %f", data->constant5.r, data->constant5.g, data->constant5.b, data->constant5.a);

        hk::dbg::Log("emissionColor %d %d %d %d", data->emissionColor.r, data->emissionColor.g, data->emissionColor.b, data->emissionColor.a);
        hk::dbg::Log("ambientColor %d %d %d %d", data->ambientColor.r, data->ambientColor.g, data->ambientColor.b, data->ambientColor.a);
        hk::dbg::Log("diffuseColor %d %d %d %d", data->diffuseColor.r, data->diffuseColor.g, data->diffuseColor.b, data->diffuseColor.a);
        hk::dbg::Log("specular0Color %d %d %d %d", data->specular0Color.r, data->specular0Color.g, data->specular0Color.b, data->specular0Color.a);
        hk::dbg::Log("specular1Color %d %d %d %d", data->specular1Color.r, data->specular1Color.g, data->specular1Color.b, data->specular1Color.a);
        hk::dbg::Log("constant0Color %d %d %d %d", data->constant0Color.r, data->constant0Color.g, data->constant0Color.b, data->constant0Color.a);
        hk::dbg::Log("constant1Color %d %d %d %d", data->constant1Color.r, data->constant1Color.g, data->constant1Color.b, data->constant1Color.a);
        hk::dbg::Log("constant2Color %d %d %d %d", data->constant2Color.r, data->constant2Color.g, data->constant2Color.b, data->constant2Color.a);
        hk::dbg::Log("constant3Color %d %d %d %d", data->constant3Color.r, data->constant3Color.g, data->constant3Color.b, data->constant3Color.a);
        hk::dbg::Log("constant4Color %d %d %d %d", data->constant4Color.r, data->constant4Color.g, data->constant4Color.b, data->constant4Color.a);
        hk::dbg::Log("constant5Color %d %d %d %d", data->constant5Color.r, data->constant5Color.g, data->constant5Color.b, data->constant5Color.a);
    }
    return ((u32(*)(MaterialColorData**, void*, void*, void*))(0x002a9ba0))(dataPtr, a, b, c);
}

struct FragLightData {
    u8 _0[204];
    FloatColor ambient;
    FloatColor diffuse;
    FloatColor specular0, specular1;
    U32Color ambientColor;
    U32Color diffuseColor;
    U32Color specular0Color, specular1Color;
};

FragLightData* ballsHook(void* allocator, const char* thing)
{
    FragLightData* data = ((FragLightData * (*)(void*, const char*))(0x0029c5c4))(allocator, thing);
    if (data) {
        data->specular0Color = { 255, 0, 0, 255 };
        data->specular1Color = { 255, 0, 0, 255 };
        data->ambientColor = { 255, 0, 0, 255 };
        data->diffuseColor = { 255, 0, 0, 255 };
    }
    return data;
}

struct Combiner {
    u32 constant;

    u32 source;
    u32 header;
    u32 operand;
    u32 combine;
    u32 constantAction;
    u32 scale;
};

// HK_BL_HOOK(ShitHook, 0x002add10, setupHook);
//  HK_BL_HOOK(Shit2Hook, 0x0029c240, ballsHook);

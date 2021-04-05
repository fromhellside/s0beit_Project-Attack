#include "main.h"
ImU32 ColorConvertFloat4ToU32(const ImVec4& in);

ImU32 ColorConvertFloat4ToU32(const ImVec4& in)
{
	ImU32 out;
	out = ((ImU32)IM_F32_TO_INT8_SAT(in.x)) << IM_COL32_R_SHIFT;
	out |= ((ImU32)IM_F32_TO_INT8_SAT(in.y)) << IM_COL32_G_SHIFT;
	out |= ((ImU32)IM_F32_TO_INT8_SAT(in.z)) << IM_COL32_B_SHIFT;
	out |= ((ImU32)IM_F32_TO_INT8_SAT(in.w)) << IM_COL32_A_SHIFT;
	return out;
}
void ColorConvertRGBtoHSV(float r, float g, float b, float& out_h, float& out_s, float& out_v)
{
	float K = 0.f;
	if (g < b)
	{
		ImSwap(g, b);
		K = -1.f;
	}
	if (r < g)
	{
		ImSwap(r, g);
		K = -2.f / 6.f - K;
	}

	const float chroma = r - (g < b ? g : b);
	out_h = ImFabs(K + (g - b) / (6.f * chroma + 1e-20f));
	out_s = chroma / (r + 1e-20f);
	out_v = r;
}
//Convert hsv floats([0 - 1], [0 - 1], [0 - 1]) to rgb floats([0 - 1], [0 - 1], [0 - 1]), from Foley& van Dam p593
// also http://en.wikipedia.org/wiki/HSL_and_HSV
void ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b)
{
	if (s == 0.0f)
	{
		// gray
		out_r = out_g = out_b = v;
		return;
	}

	h = ImFmod(h, 1.0f) / (60.0f / 360.0f);
	int   i = (int)h;
	float f = h - (float)i;
	float p = v * (1.0f - s);
	float q = v * (1.0f - s * f);
	float t = v * (1.0f - s * (1.0f - f));

	switch (i)
	{
	case 0: out_r = v; out_g = t; out_b = p; break;
	case 1: out_r = q; out_g = v; out_b = p; break;
	case 2: out_r = p; out_g = v; out_b = t; break;
	case 3: out_r = p; out_g = q; out_b = v; break;
	case 4: out_r = t; out_g = p; out_b = v; break;
	case 5: default: out_r = v; out_g = p; out_b = q; break;
	}
}

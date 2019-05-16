#ifndef H_CRYTEK_SPONZA_H
#define H_CRYTEK_SPONZA_H

#include "common.h"
#include "scene.h"

class CrytekSponzaScene : public Scene{
public:
	CrytekSponzaScene(){
		width = 768;
		height = 576;
	}

	virtual void Init(){
		bakeData.Init("crytek_sponza/bakedata0.exr");

		Mesh m0;
		m0.Load("crytek_sponza/geometry/mesh_0.dae", 0.05);
		Material m0_material;
		m0_material.emission = vec3(0.f);
		m0_material.diffuse = vec3(0.0, 0, 0);
		m0_material.Init("crytek_sponza/texture/Sponza_Bricks_a_Albedo.png");
		m0.material = m0_material;
		meshes.push_back(m0);

		Mesh m1;
		m1.Load("crytek_sponza/geometry/mesh_1.dae", 0.05);
		Material m1_material;
		m1_material.emission = vec3(0.f);
		m1_material.diffuse = vec3(0.047059, 0.047059, 0.047059);
		m1_material.Init("crytek_sponza/texture/Sponza_Roof_diffuse.png");
		m1.material = m1_material;
		meshes.push_back(m1);

		Mesh m2;
		m2.Load("crytek_sponza/geometry/mesh_2.dae", 0.05);
		Material m2_material;
		m2_material.emission = vec3(0.f);
		m2_material.diffuse = vec3(0.047059, 0.047059, 0.047059);
		m2_material.Init("crytek_sponza/texture/Lion_Albedo.png");
		m2.material = m2_material;
		meshes.push_back(m2);

		Mesh m3;
		m3.Load("crytek_sponza/geometry/mesh_3.dae", 0.05);
		Material m3_material;
		m3_material.emission = vec3(0.f);
		m3_material.diffuse = vec3(0.098039, 0.098039, 0.098039);
		m3_material.Init("crytek_sponza/texture/Background_Albedo.png");
		m3.material = m3_material;
		meshes.push_back(m3);

		Mesh m4;
		m4.Load("crytek_sponza/geometry/mesh_4.dae", 0.05);
		Material m4_material;
		m4_material.emission = vec3(0.f);
		m4_material.diffuse = vec3(0.461538, 0.461538, 0.461538);
		m4_material.Init("crytek_sponza/texture/Vase_diffuse.png");
		m4.material = m4_material;
		meshes.push_back(m4);

		Mesh m5;
		m5.Load("crytek_sponza/geometry/mesh_5.dae", 0.05);
		Material m5_material;
		m5_material.emission = vec3(0.f);
		m5_material.diffuse = vec3(0.625767, 0.625767, 0.625767);
		m5_material.Init("crytek_sponza/texture/VasePlant_diffuse.png");
		m5.material = m5_material;
		meshes.push_back(m5);

		Mesh m6;
		m6.Load("crytek_sponza/geometry/mesh_6.dae", 0.05);
		Material m6_material;
		m6_material.emission = vec3(0.f);
		m6_material.diffuse = vec3(0.600000, 0.600000, 0.600000);
		m6_material.Init("crytek_sponza/texture/VaseRound_diffuse.png");
		m6.material = m6_material;
		meshes.push_back(m6);

		Mesh m7;
		m7.Load("crytek_sponza/geometry/mesh_7.dae", 0.05);
		Material m7_material;
		m7_material.emission = vec3(0.f);
		m7_material.diffuse = vec3(0.047059, 0.047059, 0.047059);
		m7_material.Init("crytek_sponza/texture/VaseHanging_diffuse.png");
		m7.material = m7_material;
		meshes.push_back(m7);

		Mesh m8;
		m8.Load("crytek_sponza/geometry/mesh_8.dae", 0.05);
		Material m8_material;
		m8_material.emission = vec3(0.f);
		m8_material.diffuse = vec3(0.047059, 0.047059, 0.047059);
		m8_material.Init("crytek_sponza/texture/ChainTexture_Albedo.png");
		m8.material = m8_material;
		meshes.push_back(m8);

		Mesh m9;
		m9.Load("crytek_sponza/geometry/mesh_9.dae", 0.05);
		Material m9_material;
		m9_material.emission = vec3(0.f);
		m9_material.diffuse = vec3(0.478431, 0.239216, 0.117647);
		m9_material.Init("crytek_sponza/texture/Sponza_FlagPole_diffuse.png");
		m9.material = m9_material;
		meshes.push_back(m9);

		Mesh m009;
		m009.Load("crytek_sponza/geometry/mesh_10.dae", 0.05);
		Material m009_material;
		m009_material.emission = vec3(0.f);
		m009_material.diffuse = vec3(0.478431, 0.239216, 0.117647);
		m009_material.Init("crytek_sponza/texture/Sponza_Thorn_diffuse.png");
		m009.material = m009_material;
		meshes.push_back(m009);

		Mesh m003;
		m003.Load("crytek_sponza/geometry/mesh_11.dae", 0.05);
		Material m003_material;
		m003_material.emission = vec3(0.f);
		m003_material.diffuse = vec3(0.4, 0.4, 0.4);
		m003_material.Init("");
		m003.material = m003_material;
		meshes.push_back(m003);

		Mesh m002;
		m002.Load("crytek_sponza/geometry/mesh_12.dae", 0.05);
		Material m002_material;
		m002_material.emission = vec3(0.f);
		m002_material.diffuse = vec3(0.461538, 0.461538, 0.461538);
		m002_material.Init("crytek_sponza/texture/Sponza_Column_b_diffuse.png");
		m002.material = m002_material;
		meshes.push_back(m002);

		Mesh m001;
		m001.Load("crytek_sponza/geometry/mesh_13.dae", 0.05);
		Material m001_material;
		m001_material.emission = vec3(0.f);
		m001_material.diffuse = vec3(0.764977, 0.138249, 0.132104);
		m001_material.Init("crytek_sponza/texture/Sponza_Arch_diffuse.png");
		m001.material = m001_material;
		meshes.push_back(m001);

		Mesh m000;
		m000.Load("crytek_sponza/geometry/mesh_14.dae", 0.05);
		Material m000_material;
		m000_material.emission = vec3(0.f);
		m000_material.diffuse = vec3(0.058824, 0.058824, 0.058824);
		m000_material.Init("crytek_sponza/texture/Sponza_Column_a_diffuse.png");
		m000.material = m000_material;
		meshes.push_back(m000);

		Mesh m15;
		m15.Load("crytek_sponza/geometry/mesh_15.dae", 0.05);
		m000_material.emission = vec3(0.f);
		m000_material.diffuse = vec3(0.769231, 0.769231, 0.769231);
		m000_material.Init("crytek_sponza/texture/Sponza_Floor_diffuse.png");
		m15.material = m000_material;
		meshes.push_back(m15);

		Mesh m16;
		m16.Load("crytek_sponza/geometry/mesh_16.dae", 0.05);
		m000_material.emission = vec3(0.f);
		m000_material.diffuse = vec3(0.639216, 0.439216, 0.317647);
		m000_material.Init("crytek_sponza/texture/Sponza_Column_c_diffuse.png");
		m16.material = m000_material;
		meshes.push_back(m16);

		Mesh m17;
		m17.Load("crytek_sponza/geometry/mesh_17.dae", 0.05);
		m000_material.emission = vec3(0.f);
		m000_material.diffuse = vec3(0.461538, 0.461538, 0.461538);
		m000_material.Init("crytek_sponza/texture/Sponza_Details_diffuse.png");
		m17.material = m000_material;
		meshes.push_back(m17);

		Mesh m18;
		m18.Load("crytek_sponza/geometry/mesh_18.dae", 0.05);
		m000_material.emission = vec3(0.f);
		m000_material.diffuse = vec3(0.784314, 0.784314, 0.784314);
		m000_material.Init("crytek_sponza/texture/Sponza_Ceiling_diffuse.png");
		m18.material = m000_material;
		meshes.push_back(m18);

		Mesh m19;
		m19.Load("crytek_sponza/geometry/mesh_19.dae", 0.05);
		m000_material.emission = vec3(0.f);
		m000_material.diffuse = vec3(0.732049, 0.077058, 0.059545);
		m000_material.Init("crytek_sponza/texture/Sponza_Curtain_Blue_diffuse.png");
		m19.material = m000_material;
		meshes.push_back(m19);

		Mesh m20;
		m20.Load("crytek_sponza/geometry/mesh_20.dae", 0.05);
		m000_material.emission = vec3(0.f);
		m000_material.diffuse = vec3(0.078431, 0.078431, 0.078431);
		m000_material.Init("crytek_sponza/texture/Sponza_Curtain_Red_diffuse.png");
		m20.material = m000_material;
		meshes.push_back(m20);

		Mesh m21;
		m21.Load("crytek_sponza/geometry/mesh_21.dae", 0.05);
		m000_material.emission = vec3(0.f);
		m000_material.diffuse = vec3(0.286275, 0.149020, 0.129412);
		m000_material.Init("crytek_sponza/texture/Sponza_Curtain_Green_diffuse.png");
		m21.material = m000_material;
		meshes.push_back(m21);

		Mesh m22;
		m22.Load("crytek_sponza/geometry/mesh_22.dae", 0.05);
		m000_material.emission = vec3(0.f);
		m000_material.diffuse = vec3(0.733913, 0.619130, 0.379130);
		m000_material.Init("crytek_sponza/texture/Sponza_Curtain_Green_diffuse.png");
		m22.material = m000_material;
		meshes.push_back(m22);

		Mesh m23;
		m23.Load("crytek_sponza/geometry/mesh_23.dae", 0.05);
		m000_material.emission = vec3(0.f);
		m000_material.diffuse = vec3(0.745424, 0.608985, 0.489185);
		m000_material.Init("crytek_sponza/texture/Sponza_Curtain_Red_diffuse.png");
		m23.material = m000_material;
		meshes.push_back(m23);

		camera.Init(vec3(40.f, 35.f, 5.f), vec3(1.f, 0.f, 0.f), vec3(0.f, 1.f, 0.f),
			vec3(0.f, 0.f, 1.f), 45.f, vec2(width, height));
		camera.Lookat(vec3(40.f, 35.f, 5.f), vec3(0, 35.f, 0), vec3(0, 1, 0));
	}
};

#endif
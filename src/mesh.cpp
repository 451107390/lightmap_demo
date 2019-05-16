#include "mesh.h"
#include "bbox.h"
#include "shaders.h"
#include "camera.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Mesh::Mesh(){
	program.SetSource(EVertexShader, standard_vs);
	program.SetSource(EFragShader, standard_fs);
	program.Init();
}

Mesh::~Mesh(){

}

bool Mesh::Load(const char* file, float scale){
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(file, aiProcess_Triangulate | aiProcess_GenSmoothNormals);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
		fprintf(stderr, "Error when improt model: %s\n", importer.GetErrorString());
		return false;
	}

	processNode(scene->mRootNode, scene);
	if (!hasUV2)
		generateLightMapUV();

	fprintf(stderr, "Load [%s] successfully\n", file);

	vector<float> vertex;
	for (int i = 0; i < vertices.size(); ++i){
		vec3 p = vertices[i].pos;
		vec3 n = vertices[i].nor;
		vertex.push_back(p.x * scale);
		vertex.push_back(p.y * scale);
		vertex.push_back(p.z * scale);
		vertex.push_back(n.x);
		vertex.push_back(n.y);
		vertex.push_back(n.z);
		vertex.push_back(vertices[i].uv.x);
		vertex.push_back(vertices[i].uv.y);
		vertex.push_back(vertices[i].uv2.x);
		vertex.push_back(vertices[i].uv2.y);
	}

	//将模型装入VBO
	glGenBuffers(1, &vertexVbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
	glBufferData(GL_ARRAY_BUFFER, vertex.size()*sizeof(float), &vertex[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexVbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
}

void Mesh::Draw(Camera& camera, Texture& bakeData, bool showDiffuse, bool showLightmap){
	program.Bind();
	program.SetMat4("WVP", camera.GetProjection()*camera.GetView());
	program.SetMat4("World", mat4());
	program.SetVec3("cameraPos", camera.position);
	bakeData.Bind(0);
	program.SetInt("texBake", 0);
	material.Bind(program);
	program.SetBool("showDiffuse", showDiffuse);
	program.SetBool("showLightmap", showLightmap);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 40, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 40, (GLvoid*)12);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 40, (GLvoid*)24);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 40, (GLvoid*)32);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVbo);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	program.UnBind();
}


void Mesh::processMesh(aiMesh* aimesh, const aiScene* scene){
	for (int i = 0; i < aimesh->mNumVertices; ++i){
		Vertex vertex;
		vertex.pos = vec3(aimesh->mVertices[i].x, aimesh->mVertices[i].y, aimesh->mVertices[i].z);
		vertex.nor = vec3(aimesh->mNormals[i].x, aimesh->mNormals[i].y, aimesh->mNormals[i].z);
		if (aimesh->mTextureCoords[0]) {
			vertex.uv = vec2(aimesh->mTextureCoords[0][i].x, aimesh->mTextureCoords[0][i].y);
		}
		if (aimesh->mTextureCoords[1]){
			hasUV2 = true;
			float uvx = aimesh->mTextureCoords[1][i].x;
			float uvy = aimesh->mTextureCoords[1][i].y;
			vertex.uv2 = vec2(uvx, uvy);
		}

		vertices.push_back(vertex);
	}


	for (int i = 0; i < aimesh->mNumFaces; ++i){
		aiFace face = aimesh->mFaces[i];

		int idx1 = face.mIndices[0];
		int idx2 = face.mIndices[1];
		int idx3 = face.mIndices[2];
		indices.push_back(idx1);
		indices.push_back(idx2);
		indices.push_back(idx3);
	}
}


void Mesh::processNode(aiNode* node, const aiScene* scene){
	for (int i = 0; i < node->mNumMeshes; ++i){
		aiMesh* aimesh = scene->mMeshes[node->mMeshes[i]];
		processMesh(aimesh, scene);
	}

	for (int i = 0; i < node->mNumChildren; ++i){
		processNode(node->mChildren[i], scene);
	}
}

void Mesh::generateLightMapUV(){
	int widthPerTriangle = 32;
	int heightPerTriangle = 32;
	int space = 3;
	int totalSize = indices.size()/3;
	int len = ceil(sqrtf(totalSize));
	int width = (widthPerTriangle + space)*len;

	auto Clamp = [widthPerTriangle, heightPerTriangle](vec2 uv)->vec2{
		uv.x = clamp(uv.x, 1.f, 31.f);
		uv.y = clamp(uv.y, 1.f, 31.f);
		return uv;
	};

	auto Barycentric = [](vec2 v1, vec2 v2, vec2 v3)->vec2{
		return (v1 + v2 + v3) / 3.f;
	};

	int idx = 0;
	for (int i = 0; i < len; ++i){
		for (int j = 0; j < len; ++j){
			int idx1 = indices[3 * idx + 0];
			int idx2 = indices[3 * idx + 1];
			int idx3 = indices[3 * idx + 2];
			vec3 v1 = vertices[idx1].pos;
			vec3 v2 = vertices[idx2].pos;
			vec3 v3 = vertices[idx3].pos;
			vec3 normal = normalize(cross(v2 - v1, v3 - v1));
			int axis = (fabs(normal.x)>fabs(normal.y) && fabs(normal.x) > fabs(normal.z)) ?
				1 : (fabs(normal.y) > fabs(normal.z)) ? 2 : 3;
			float scale = 2.5f;
			switch (axis){
			case 1:{
				float xmin = (v1.z > v2.z) && (v1.z > v3.z) ? v1.z : (v2.z > v3.z) ? v2.z : v3.z;
				float xmax = (v1.z < v2.z) && (v1.z < v3.z) ? v1.z : (v2.z < v3.z) ? v2.z : v3.z;
				float ymin = (v1.y < v2.y) && (v1.y < v3.y) ? v1.y : (v2.y < v3.y) ? v2.y : v3.y;
				float ymax = (v1.y > v2.y) && (v1.y > v3.y) ? v1.y : (v2.y > v3.y) ? v2.y : v3.y;
				float deltaX = xmax - xmin;
				float deltaY = ymax - ymin;
				vec2 v1uv = vec2(j, i)*vec2(widthPerTriangle + space, heightPerTriangle + space) + Clamp(vec2((v1.z - xmin) / deltaX, (v1.y - ymin) / deltaY) * vec2(widthPerTriangle, heightPerTriangle));
				vec2 v2uv = vec2(j, i)*vec2(widthPerTriangle + space, heightPerTriangle + space) + Clamp(vec2((v2.z - xmin) / deltaX, (v2.y - ymin) / deltaY) * vec2(widthPerTriangle, heightPerTriangle));
				vec2 v3uv = vec2(j, i)*vec2(widthPerTriangle + space, heightPerTriangle + space) + Clamp(vec2((v3.z - xmin) / deltaX, (v3.y - ymin) / deltaY) * vec2(widthPerTriangle, heightPerTriangle));
				vec2 bary = Barycentric(v1uv, v2uv, v3uv);
				vec2 d1 = bary - v1uv, d2 = bary - v2uv, d3 = bary - v3uv;
				if (d1.x > d1.y){
					v1uv.x += d1.x / fabs(d1.y) * scale;
					v1uv.y += d1.y / fabs(d1.y) * scale;
				}
				else{
					v1uv.x += d1.x / fabs(d1.x) * scale;;
					v1uv.y += d1.y / fabs(d1.x) * scale;;
				}
				if (d2.x > d2.y){
					v2uv.x += d2.x / fabs(d2.y) * scale;;
					v2uv.y += d2.y / fabs(d2.y) * scale;;
				}
				else{
					v2uv.x += d2.x / fabs(d2.x) * scale;;
					v2uv.y += d2.y / fabs(d2.x) * scale;;
				}
				if (d3.x > d3.y){
					v3uv.x += d3.x / fabs(d3.y) * scale;;
					v3uv.y += d3.y / fabs(d3.y) * scale;;
				}
				else{
					v3uv.x += d3.x / fabs(d3.x) * scale;;
					v3uv.y += d3.y / fabs(d3.x) * scale;;
				}

				vertices[idx1].uv2 = vec2(v1uv / vec2(width, width));
				vertices[idx2].uv2 = vec2(v2uv / vec2(width, width));
				vertices[idx3].uv2 = vec2(v3uv / vec2(width, width));
				break;
			}
			case 2:{
				float xmin = (v1.x < v2.x) && (v1.x < v3.x) ? v1.x : (v2.x < v3.x) ? v2.x : v3.x;
				float xmax = (v1.x > v2.x) && (v1.x > v3.x) ? v1.x : (v2.x > v3.x) ? v2.x : v3.x;
				float ymin = (v1.z > v2.z) && (v1.z > v3.z) ? v1.z : (v2.z > v3.z) ? v2.z : v3.z;
				float ymax = (v1.z < v2.z) && (v1.z < v3.z) ? v1.z : (v2.z < v3.z) ? v2.z : v3.z;
				float deltaX = xmax - xmin;
				float deltaY = ymax - ymin;
				vec2 v1uv = vec2(j, i)*vec2(widthPerTriangle + space, heightPerTriangle + space) + Clamp(vec2((v1.x - xmin) / deltaX, (v1.z - ymin) / deltaY) * vec2(widthPerTriangle, heightPerTriangle));
				vec2 v2uv = vec2(j, i)*vec2(widthPerTriangle + space, heightPerTriangle + space) + Clamp(vec2((v2.x - xmin) / deltaX, (v2.z - ymin) / deltaY) * vec2(widthPerTriangle, heightPerTriangle));
				vec2 v3uv = vec2(j, i)*vec2(widthPerTriangle + space, heightPerTriangle + space) + Clamp(vec2((v3.x - xmin) / deltaX, (v3.z - ymin) / deltaY) * vec2(widthPerTriangle, heightPerTriangle));
				vec2 bary = Barycentric(v1uv, v2uv, v3uv);
				vec2 d1 = bary - v1uv, d2 = bary - v2uv, d3 = bary - v3uv;
				if (d1.x > d1.y){
					v1uv.x += d1.x / fabs(d1.y) * scale;;
					v1uv.y += d1.y / fabs(d1.y) * scale;;
				}
				else{
					v1uv.x += d1.x / fabs(d1.x) * scale;;
					v1uv.y += d1.y / fabs(d1.x) * scale;;
				}
				if (d2.x > d2.y){
					v2uv.x += d2.x / fabs(d2.y) * scale;;
					v2uv.y += d2.y / fabs(d2.y) * scale;;
				}
				else{
					v2uv.x += d2.x / fabs(d2.x) * scale;;
					v2uv.y += d2.y / fabs(d2.x) * scale;;
				}
				if (d3.x > d3.y){
					v3uv.x += d3.x / fabs(d3.y) * scale;;
					v3uv.y += d3.y / fabs(d3.y) * scale;;
				}
				else{
					v3uv.x += d3.x / fabs(d3.x) * scale;;
					v3uv.y += d3.y / fabs(d3.x) * scale;;
				}

				vertices[idx1].uv2 = vec2(v1uv / vec2(width, width));
				vertices[idx2].uv2 = vec2(v2uv / vec2(width, width));
				vertices[idx3].uv2 = vec2(v3uv / vec2(width, width));
				break;
			}
			case 3:{
				float xmin = (v1.x < v2.x) && (v1.x < v3.x) ? v1.x : (v2.x < v3.x) ? v2.x : v3.x;
				float xmax = (v1.x > v2.x) && (v1.x > v3.x) ? v1.x : (v2.x > v3.x) ? v2.x : v3.x;
				float ymin = (v1.y < v2.y) && (v1.y < v3.y) ? v1.y : (v2.y < v3.y) ? v2.y : v3.y;
				float ymax = (v1.y > v2.y) && (v1.y > v3.y) ? v1.y : (v2.y > v3.y) ? v2.y : v3.y;
				float deltaX = xmax - xmin;
				float deltaY = ymax - ymin;
				vec2 v1uv = vec2(j, i)*vec2(widthPerTriangle + space, heightPerTriangle + space) + Clamp(vec2((v1.x - xmin) / deltaX, (v1.y - ymin) / deltaY) * vec2(widthPerTriangle, heightPerTriangle));
				vec2 v2uv = vec2(j, i)*vec2(widthPerTriangle + space, heightPerTriangle + space) + Clamp(vec2((v2.x - xmin) / deltaX, (v2.y - ymin) / deltaY) * vec2(widthPerTriangle, heightPerTriangle));
				vec2 v3uv = vec2(j, i)*vec2(widthPerTriangle + space, heightPerTriangle + space) + Clamp(vec2((v3.x - xmin) / deltaX, (v3.y - ymin) / deltaY) * vec2(widthPerTriangle, heightPerTriangle));
				vec2 bary = Barycentric(v1uv, v2uv, v3uv);
				vec2 d1 = bary - v1uv, d2 = bary - v2uv, d3 = bary - v3uv;
				if (d1.x > d1.y){
					v1uv.x += d1.x / fabs(d1.y) * scale;;
					v1uv.y += d1.y / fabs(d1.y) * scale;;
				}
				else{
					v1uv.x += d1.x / fabs(d1.x) * scale;;
					v1uv.y += d1.y / fabs(d1.x) * scale;;
				}
				if (d2.x > d2.y){
					v2uv.x += d2.x / fabs(d2.y) * scale;;
					v2uv.y += d2.y / fabs(d2.y) * scale;;
				}
				else{
					v2uv.x += d2.x / fabs(d2.x) * scale;;
					v2uv.y += d2.y / fabs(d2.x) * scale;;
				}
				if (d3.x > d3.y){
					v3uv.x += d3.x / fabs(d3.y) * scale;;
					v3uv.y += d3.y / fabs(d3.y) * scale;;
				}
				else{
					v3uv.x += d3.x / fabs(d3.x) * scale;;
					v3uv.y += d3.y / fabs(d3.x) * scale;;
				}

				vertices[idx1].uv2 = vec2(v1uv / vec2(width, width));
				vertices[idx2].uv2 = vec2(v2uv / vec2(width, width));
				vertices[idx3].uv2 = vec2(v3uv / vec2(width, width));
				break;
			}
			}

			idx++;
			if (idx >= indices.size()/3)
				goto complete;
		}
	}

complete:
	return;
}
